#!/usr/bin/env python3
# Monitor compiler
import sys, os, time
import uvwBuilder, subprocess, parser, math
import pareto_enumerator, copy, tempfile, shutil


# Global parameters
PRINTDEBUGINFO = False
RUN_CADICAL = False

# Location of the script & Debugging options
scriptPath = os.path.dirname(sys.argv[0])

# ==========================================
# FullMod32 function - Returns values between (including) 1 and 32, except for values <= 0.
# Used for buffer index calculation
# ==========================================
def fullmod32(inVal):
    if inVal<=0:
        return inVal
    return ((inVal-1) % 32)+1

# ==========================================
# BDD to CNF functions
# ==========================================
def bddToDNF(bdd,mgr,careSet,bddVariables,propositions):

    result = []
    bddLB = bdd & careSet
    bddUB = bdd | ~careSet
    while bddLB!=mgr.false:
        # print("BDD:",bddLB.to_expr())
        # print("BDDUB:", bddUB.to_expr())
        
        # Find concrete assignment
        assignment = []
        assignmentSoFar = mgr.true
        while len(assignment)!=len(bddVariables):
            test = assignmentSoFar & bddVariables[len(assignment)]
            if (test & bddLB) == mgr.false:
                assignmentSoFar = assignmentSoFar & ~bddVariables[len(assignment)]
                assignment.append(False)
            else:
                assignmentSoFar = assignmentSoFar & bddVariables[len(assignment)]
                assignment.append(True)
        # print("IMA:",assignment,assignmentSoFar.to_expr())
        assert assignmentSoFar
        # Don't care...
        for i in range(0,len(assignment)):
            if (mgr.exist([propositions[i]],assignmentSoFar) & ~bddUB) == mgr.false:
                assignment[i] = None
                assignmentSoFar = mgr.exist([propositions[i]],assignmentSoFar)
        # Done!
        result.append(assignment)
        bddLB = bddLB & ~assignmentSoFar


    # print("RED:",result)
    return result

def testBDDToCNF(ddMgr,propositions):

    propA = ddMgr.add_expr(propositions[0])
    propB = ddMgr.add_expr(propositions[1])
    propC = ddMgr.add_expr(propositions[2])
    bddVariables = [propA,propB,propC]

    test1 = (propA | propB) & (~propB | ~propC)
    dnf = bddToDNF(test1,ddMgr,ddMgr.true,bddVariables,propositions)
    
    print("DNF: ",dnf)



# ==========================================
# Compute deterministic monitoring automaton
# ==========================================
class DFA:
    def __init__(self,states,transitions,initial,accepting):
        self.states = states
        self.transitions = transitions
        self.initial = initial
        self.accepting = accepting

def determiniseUVWForMonitoring(baseUVW):

    # Allocate elements
    statesDFA = []
    transitionsDFA = []
    initialDFA = 0 # By definition
    acceptingDFA = []
    
    # Get initial state
    initialStateEncoding = []
    for i in range(0,len(baseUVW.stateNames)):
        initialStateEncoding.append(i in baseUVW.initialStates)
    statesDFA.append(tuple(initialStateEncoding))
    transitionsDFA.append([])
    acceptingDFA.append(False)
    
    # Enumerate states and transitions until no more reachable state has not been explored
    todo = [0]
    done = set([0])
    while len(todo)!=0:
        thisOne = todo[0]
        todo = todo[1:]
        
        # List all relevant UVW transitions from this DFA state
        relevantTransitions = [] # Element format: from,to,BDD
        for uvwState in range(0,len(baseUVW.stateNames)):
            if statesDFA[thisOne][uvwState]:
                for (a,b) in baseUVW.transitions[uvwState]:
                    relevantTransitions.append((uvwState,a,b))
        
        # Enumerate all possible transitions
        theseTransitions = []
        transitionsDFA[thisOne] = theseTransitions
        
        def recurseRelevantTransitions(prefix,conjunct):
            # Base cases
            if conjunct==baseUVW.ddMgr.false:
                return
            if len(prefix)==len(relevantTransitions):
                nextState = [False for state in baseUVW.stateNames]
                for i,v in enumerate(prefix):
                    if v:
                        nextState[relevantTransitions[i][1]] = True
                nextState = tuple(nextState)
                if nextState in statesDFA:
                    nextStateNumber = statesDFA.index(nextState)
                else:
                    nextStateNumber = len(statesDFA)
                    statesDFA.append(nextState)
                    transitionsDFA.append([])
                    acceptingDFA.append(False)
                    todo.append(nextStateNumber)
                theseTransitions.append((nextStateNumber,conjunct,[a for (i,a) in enumerate(relevantTransitions) if prefix[i]]))
            else:
                # Try recurse
                recurseRelevantTransitions(prefix+[False],conjunct & ~(relevantTransitions[len(prefix)][2]))
                recurseRelevantTransitions(prefix+[True],conjunct & (relevantTransitions[len(prefix)][2]))
           
        # Run recursion           
        recurseRelevantTransitions([],baseUVW.ddMgr.true)
    
    
    # =======================================================
    # Identify rejecting states -- Generalized Buchi analysis
    # =======================================================
    acceptingDFA = set([])
    lastSizeAcceptingDFA = -1
    
    # Greatest fixed point over DFA states
    while len(acceptingDFA)!=lastSizeAcceptingDFA:
        lastSizeAcceptingDFA = len(acceptingDFA)
    
        # Big disjunction over rejecting UVW states
        for uvwStateNum in range(len(baseUVW.stateNames)):
            if baseUVW.rejecting[uvwStateNum]:
                # initialize Reachable
                reachable = set([dfaState for dfaState in range(len(statesDFA)) if not statesDFA[dfaState][uvwStateNum]])
                # Reachability fixed point
                oldSizeReachable = -1
                while len(reachable)!=oldSizeReachable:
                    oldSizeReachable = len(reachable)
                    for dfaState in range(len(statesDFA)):
                        # print("CHECKING",dfaState)
                        if not dfaState in reachable:
                            for (to,label,toTrans) in transitionsDFA[dfaState]:
                                # print("TARNSCHECK",to,label,toTrans)
                                # print("CURRENT",reachable)
                                if not to in acceptingDFA:
                                    if to in reachable:
                                        reachable.add(dfaState)
                                    else:
                                        # Analysis -- Leaving this state?
                                        foundSelfLoop = False
                                        for (a,b,c) in toTrans:
                                            if a==uvwStateNum and b==uvwStateNum:
                                                # Self loop
                                                if (label & c)==label:
                                                    foundSelfLoop = True
                                        if not foundSelfLoop:
                                            reachable.add(dfaState)
               
                # Clean non-reachable sets into acceptingDFA:
                for dfaState in range(len(statesDFA)):
                    if not dfaState in reachable:
                        # print("Not safe because UVW State "+str(uvwStateNum)+": "+str(dfaState))
                        acceptingDFA.add(dfaState)
                    
    if PRINTDEBUGINFO:     
    
        # Which DFA states are accepting?    
        print("Accepting states in DFA: ", acceptingDFA)
    
        # Print DFA
        print("Monitoring DFA with "+str(len(statesDFA)))
        for stateNum in range(len(statesDFA)):
            print("State "+str(stateNum)+": "+str(statesDFA[stateNum]))
            for (a,b,c) in transitionsDFA[stateNum]:
                print("- "+str(a)+" for "+b.to_expr())
            
            
        # Print graphviz
        print("digraph {")
        boolStrMapping = {False: "0", True: "1"}
        stateNames = [",".join([boolStrMapping[a] for a in b]) for b in statesDFA]
        # overwrite rejecting states with "rejecting"
        for i in range(0,len(statesDFA)):
            if statesDFA[i][0]:
                stateNames[i] = "reject"
        for a in stateNames:
            print(" \""+a+"\";")
        transitionsAlreadyDotted = set([])
        for stateNum in range(len(statesDFA)):
            for (a,b,c) in transitionsDFA[stateNum]:
                if not (stateNames[stateNum],stateNames[a]) in transitionsAlreadyDotted:
                    print(" \""+stateNames[stateNum]+"\" -> \""+stateNames[a]+"\";")
                    transitionsAlreadyDotted.add((stateNames[stateNum],stateNames[a]))
        print("}")
        
        
        # Print Graphviz
        print("\\begin{tikzpicture}")
        reverseLookup = {}
        for i in range(0,len(statesDFA)):
            reverseLookup[stateNames[i]] = i
        for i in range(0,len(statesDFA)):
            if reverseLookup[stateNames[i]] == i:
                print("\\node[shape=rectangle,minimum width=0.8cm,minimum height=0.3cm,inner sep=0pt,thick] (s"+str(i)+") at ("+str(i)+",0) {"+stateNames[i]+"};")
        transitionsAlreadyDotted = set([])
        for stateNum in range(len(statesDFA)):
            if reverseLookup[stateNames[stateNum]] == stateNum:
                for (a,b,c) in transitionsDFA[stateNum]:
                    if not (stateNames[stateNum],stateNames[a]) in transitionsAlreadyDotted:
                        print("\\draw[->,thick] (s"+str(stateNum)+") -- (s"+str(reverseLookup[stateNames[a]])+");")
                        transitionsAlreadyDotted.add((stateNames[stateNum],stateNames[a]))
        print("\\end{tikzpicture}")
        
        
        # Count transitions from non-rejecting states
        nofTransitionsFromNonRejectingStates = 0
        for i in range(0,len(statesDFA)):
            if i in acceptingDFA:
                pass
            else:
                for m in transitionsDFA[i]:
                    nofTransitionsFromNonRejectingStates += 1
        print("Number of DFA transitions from non-rejecting states:",nofTransitionsFromNonRejectingStates)
        
    # Return result
    return DFA(statesDFA,transitionsDFA,initialDFA,acceptingDFA)

# ==================================
# Write monitor code
# ==================================
def bitListToCCodeNumber(case,invert):

    mask = 0
    val = 0
    for i in range(0,32):
        if len(case)>i:
            local = case[i]
            if local==None:
                if invert:
                    mask += (1<<i)
                    val += (1<<i)
            else:
                if invert:
                    if local:
                        mask += (1<<i)
                else:
                    mask += (1<<i)
                    if local:
                        val += (1<<i)*local

    def convertToCNum(a):
        if a<32:
            return str(a)
        else:
            return hex(a)
    
    # print("CONVERT: ",mask,val,case,invert)
    return (convertToCNum(mask),convertToCNum(val))




#============================================================================
# Code Generation
#============================================================================
def generateMonitorCode(dfa,baseUVW,propositions,livenessMonitoring,outFile,generationAlgorithm,nofLUTS,nofInputsPerLUT):
    if generationAlgorithm=="deterministic":
        generateMonitorCodeDeterministic(dfa, baseUVW, propositions, livenessMonitoring, outFile)
    elif generationAlgorithm=="nondeterministic":
        generateMonitorCodeNondeterministic(dfa, baseUVW, propositions, livenessMonitoring, outFile)
    elif generationAlgorithm== "aig":
        generateMonitorCodeAIGBased(dfa, baseUVW, propositions, livenessMonitoring, outFile,nofLUTS,nofInputsPerLUT)
    else:
        raise Exception("Unknown monitor generation algorithm.")


def pickCNFOrDNFWhateverIsShorter(cnfLabel,dnfLabel,outFile, varNames):
    
    # Try DNF Conversion
    textDNF = ""
    if len(dnfLabel)==0:
        textDNF = "1" # 'cause is negated
    for i, case in enumerate(dnfLabel):
        if i > 0:
            textDNF += " || "
        if not False in case and not True in case:
            textDNF += "0"
        else:
            first = True
            textDNF += "("
            for j,element in enumerate(case):
                if not element is None:
                    if not first:
                        textDNF += " && "
                    first = False
                    if element:
                        textDNF += varNames[j]
                    else:
                        textDNF += "!"+varNames[j]
            textDNF += ")"

    # Try CNF Conversion
    # print("// CNF LABEL: "+str(cnfLabel))
    textCNF = ""
    if len(cnfLabel) == 0:
        textCNF = "1"
    for i, case in enumerate(cnfLabel):
        if i > 0:
            textCNF += " && "
        if not False in case and not True in case:
            textCNF += "0"
        else:
            first = True
            textCNF += "("
            for j, element in enumerate(case):
                if not element is None:
                    if not first:
                        textCNF += "||"
                    first = False
                    if element:
                        textCNF += "!" + varNames[j]
                    else:
                        textCNF += varNames[j]
            textCNF += ")"

    # Choose between CNF and DNF
    if len(textDNF) <= len(textCNF):
        print(textDNF, end="", file=outFile)
    else:
        print(textCNF, end="", file=outFile)


def generateMonitorCodeNondeterministic(dfa,baseUVW,propositions,livenessMonitoring,outFile):

    # Prepare BDD variables and their compiled names
    baseUVW_string_rep = str(baseUVW)
    allBDDVarNames = list(propositions)
    bddVariables = [baseUVW.ddMgr.add_expr(a) for a in propositions]
    for stateNum in range(len(baseUVW.stateNames)):
        baseUVW.ddMgr.declare("uvwState" + str(stateNum))
        bddVariables.append(baseUVW.ddMgr.add_expr("uvwState"+str(stateNum)))
        allBDDVarNames.append("uvwState"+str(stateNum))

    # Compute number of Bits for each state buffer - Recursively
    bufferSizesInBits = [-1 for state in baseUVW.stateNames]
    incomingTransitionsUVWExceptForSelfLoops = [[] for state in baseUVW.stateNames]
    for s in range(len(baseUVW.stateNames)):
        for (a, b) in baseUVW.transitions[s]:
            if (a != s):
                incomingTransitionsUVWExceptForSelfLoops[a].append((s, b))
    nofBitsIncomingTransitions = []
    for s in range(len(baseUVW.stateNames)):
        # Count non-self-looping transitions
        cnt = 0
        for (a, b) in incomingTransitionsUVWExceptForSelfLoops[s]:
            if (a != s):
                cnt += 1
        if cnt > 0:
            nofBitsIncomingTransitions.append(math.ceil(math.log(cnt) / math.log(2)))
        else:
            nofBitsIncomingTransitions.append(0)

    def recurseComputerBufferSizes(uvwState):
        if bufferSizesInBits[uvwState] != -1:
            return
        maxBufferSize = 0
        for (a, b) in incomingTransitionsUVWExceptForSelfLoops[uvwState]:
            recurseComputerBufferSizes(a)
            maxBufferSize = max(maxBufferSize,
                                bufferSizesInBits[a] + len(propositions) + nofBitsIncomingTransitions[uvwState])
        bufferSizesInBits[uvwState] = maxBufferSize

    for s in range(len(baseUVW.stateNames)):
        recurseComputerBufferSizes(s)

    # Compute buffer sizes in #32-bit uints
    bufferSizesInWords = [int(math.ceil(a / 32.0)) for a in bufferSizesInBits]

    # print("Buffer sizes:",bufferSizesInBits)
    # print(nofBitsIncomingTransitions)

    # Sanity check -- at most 32 bits added per trace element
    # (the sanity check fails slightly unnecessarily if there are no transitions in the UVW)
    maxNofBitsTransitions = max(1, max([len(a) for a in incomingTransitionsUVWExceptForSelfLoops]))
    assert math.ceil(math.log(maxNofBitsTransitions) / math.log(2)) + len(propositions) <= 32

    # Declare variables in Monitor code
    print("#include \"UVWMonitor.h\"", file=outFile)
    print("#include <stdbool.h>", file=outFile)
    print("/* Declare variables for monitoring */", file=outFile)

    for uvwState in range(len(baseUVW.stateNames)):
        if uvwState in baseUVW.initialStates:
            print("bool uvwState" + str(uvwState) + " = 1;", file=outFile)
        else:
            print("bool uvwState"+str(uvwState)+" = 0;",file=outFile)

    print("struct bufType {", file=outFile)
    bufferVarNames = {}
    initParts = []
    print("XXXX",bufferSizesInWords,bufferSizesInBits)
    for i, a in enumerate(bufferSizesInWords):
        for j in range(a):
            bufferVarNames[(i, j)] = "buf.b" + str(i) + "p" + str(j);
            print("  uint32_t b" + str(i) + "p" + str(j) + ";", file=outFile)
            initParts.append("0")
    print("} buf = {" + ",".join(initParts) + "};", file=outFile)
    for i, a in enumerate(bufferSizesInWords):
        if bufferSizesInBits[i] == 0:
            bufferVarNames[(i, 0)] = "b" + str(i) + "p" + str(0);
            print("const uint32_t b" + str(i) + "p0 = 0;", file=outFile)
    for i, a in enumerate(bufferSizesInWords):
        if livenessMonitoring and baseUVW.rejecting[i] and i > 0:  # No counter for the FASLE
            print("uint32_t cnt" + str(i) + " = 0;", file=outFile)

    # Main monitoring function
    print("\nvoid monitorUpdate(uint32_t apValues) {", file=outFile)

    # Copy the bit values to individual variables
    for i, a in enumerate(baseUVW.propositions):
        print("  bool " + a + " = apValues & (1 << " + str(i) + ");", file=outFile)
        print("  (void)("+a+"); // Avoid symbol ununsed warning.", file=outFile)
    print("")
    
    careSet = baseUVW.ddMgr.true

    for stateNum in range(len(baseUVW.stateNames)):

        print("  bool nextUVW"+str(stateNum)+" = 0;",file=outFile)
       
        # Not already in the state or self-loop inactive?
        print("  if (uvwState"+str(stateNum)+" && (",file=outFile,end="")

        # Enumerate all self-loops transitions
        incoming = baseUVW.ddMgr.false
        for (toState, condition) in baseUVW.transitions[stateNum]:
            if toState == stateNum:
                incoming = incoming | condition
                assert not condition == baseUVW.ddMgr.false 
                assert not incoming == baseUVW.ddMgr.false
        assert not (stateNum==0 and incoming==baseUVW.ddMgr.false)
        dnfLabel = bddToDNF(~incoming, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
        cnfLabel = bddToDNF(incoming, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
        pickCNFOrDNFWhateverIsShorter(cnfLabel, dnfLabel, outFile, allBDDVarNames)
        print(")) {", file = outFile)
        print("    nextUVW"+str(stateNum)+" = 1;",file=outFile)
        if livenessMonitoring:
            if not (stateNum == 0) and baseUVW.rejecting[stateNum]:
                print("    cnt" + str(stateNum) + "=1;",file=outFile)
                print("    if ((cnt" + str(stateNum) + " & FREQUENCY_MASK_STARVATION_LOGGING)==0) {", file=outFile)
                print("      logLivenessStarvation(" + str(stateNum) + ",cnt" + str(stateNum) + ", &buf.b" + str(
                    stateNum) + "p0," + str(bufferSizesInWords[stateNum]) + ");", file=outFile)
                print("    }", file=outFile)
        print("  }", file = outFile)

        # Incoming transitions - copy buffer information
        for fromUVW in range(len(baseUVW.stateNames)):
            for (toUVW,condition) in baseUVW.transitions[fromUVW]:
                if toUVW==stateNum and fromUVW!=toUVW:
                    print("  else ", file=outFile, end="")
                    transitionCond = condition # bddVariables[len(propositions)+fromUVW] & condition
                    print("if (uvwState"+str(fromUVW)+" && (", file=outFile, end="")
                    dnfLabel = bddToDNF(transitionCond, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
                    cnfLabel = bddToDNF(~transitionCond, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
                    pickCNFOrDNFWhateverIsShorter(cnfLabel, dnfLabel, outFile, allBDDVarNames)
                    print(")) {", file=outFile)
                    print("    nextUVW"+str(stateNum)+" = 1;",file=outFile)

                    # print("Mux: ",baseUVW.transitions[fromUVW])
                    indexIncomingTransition = -1
                    for transitionIndex, (ls, ll) in enumerate(
                            incomingTransitionsUVWExceptForSelfLoops[toUVW]):
                        print("ENUM:",ls,ll,fromUVW,toUVW)
                        if (ls, ll) == (fromUVW, condition):
                            indexIncomingTransition = transitionIndex
                    assert indexIncomingTransition != -1

                    # Low bits
                    for index in range(0, bufferSizesInBits[fromUVW] // 32):
                        print("        " + bufferVarNames[(toUVW, index)] + " = " + bufferVarNames[
                            (fromUVW, index)] + +";", file=outFile)
                    
                    if fullmod32(bufferSizesInBits[fromUVW]) < fullmod32(bufferSizesInBits[toUVW]):
                        # Simple case: appending all to the same part
                        wordIndex = bufferSizesInBits[fromUVW] // 32
                        assert len(propositions)>0
                        # Copy part
                        # TODO: This fails for large specs. Index computations do not seem to be correct.
                        print("    " + bufferVarNames[(toUVW, wordIndex)] + " = " +
                              bufferVarNames[(fromUVW, wordIndex)], end="", file=outFile)
                        # Add proposition values
                        print(" | (apValues << " + str(
                            fullmod32(bufferSizesInBits[toUVW]) - nofBitsIncomingTransitions[
                                toUVW] - len(propositions)) + ")", end="", file=outFile)

                        # Add source
                        if nofBitsIncomingTransitions[toUVW] > 0:
                            print(" | (" + str(indexIncomingTransition) + " << " + str(
                                fullmod32(bufferSizesInBits[toUVW]) - nofBitsIncomingTransitions[
                                    toUVW]) + ")", end="", file=outFile)
                        print(";", file=outFile)
                    else:
                        wordIndexFrom = bufferSizesInBits[fromUVW] // 32
                        print("        uint32_t addedInformation = "+str(indexIncomingTransition)+" + (apValues << "+str(nofBitsIncomingTransitions[toUVW])+");", file=outFile)
                        nofAddedBits = len(propositions)+nofBitsIncomingTransitions[toUVW]
                        assert(nofAddedBits<=32) # Otherwise spec is too big. 
                        
                        print("        " + bufferVarNames[(toUVW, wordIndexFrom)] + " = " +
                              bufferVarNames[(fromUVW, wordIndexFrom)], end="", file=outFile)
                        print(" | (addedInformation << " + str(
                            32+(bufferSizesInBits[toUVW] % 32)- nofBitsIncomingTransitions[
                                toUVW] - len(propositions))+")", end=";\n", file=outFile)
                            
                        # Start next buffer content
                        remainingBits = bufferSizesInBits[toUVW] % 32
                        print("        " + bufferVarNames[(toUVW, wordIndexFrom+1)] + " = addedInformation >> "+str(len(propostions)+nofBitsIncomingTransitions[toUVW] - remainingBits)+";", end="\n", file=outFile)
                        outFile.flush()
                    
                        raise Exception("This case is currently untested.")

                    if toUVW==0:
                        print("    logViolationExplanation(0,&(buf.b0p0)," + str(bufferSizesInWords[0] * 4) + ");", file=outFile)

                    print("  }", file=outFile)





    for i, a in enumerate(baseUVW.stateNames):
        print("  uvwState"+str(i) + " = nextUVW"+str(i)+";", file=outFile)
    print("")
    print("}\n", file=outFile)

    # Add decoding information for the buffers:
    print("/* Decoding information for the buffers:", file=outFile)
    print("   -------------------------------------\n", file=outFile)
    for i in range(0, len(baseUVW.stateNames)):
        print(" - UVW state " + str(i) + " with LTL subformula (Polish notation):", file=outFile)
        if bufferSizesInBits[i] == 0:
            print("    Initial state only", file=outFile)
        else:
            if (bufferSizesInBits[i] - nofBitsIncomingTransitions[i] - len(propositions)) > 0:
                print("    Bits 0 to " + str(bufferSizesInBits[i] - nofBitsIncomingTransitions[i] - len(
                    propositions) - 1) + ": previous buffer", file=outFile)
            print("    Bits " + str(
                bufferSizesInBits[i] - nofBitsIncomingTransitions[i] - len(propositions)) + " to " + str(
                bufferSizesInBits[i] - nofBitsIncomingTransitions[i] - 1) + ": propositions", file=outFile)
            if nofBitsIncomingTransitions[i] > 0:
                print("    Bits " + str(bufferSizesInBits[i] - nofBitsIncomingTransitions[i]) + " to " + str(
                    bufferSizesInBits[i] - 1) + ": incoming transition", file=outFile)
                for transitionIndex, (ls, ll) in enumerate(incomingTransitionsUVWExceptForSelfLoops[i]):
                    print("       -> Value " + str(transitionIndex) + " for transition from UVW state " + str(ls),
                          file=outFile)

    print("\n", file=outFile)
    print("UVW on which the monitor is based:\n", baseUVW_string_rep, file=outFile)

    print("*/", file=outFile)




def generateMonitorCodeAIGBased(dfa,baseUVW,propositions,livenessMonitoring,outFile,nofLUTs,nofInputsPerLUT):

    # Prepare BDD variables and their compiled names
    baseUVW_string_rep = str(baseUVW)
    allBDDVarNames = list(propositions)
    bddVariables = [baseUVW.ddMgr.add_expr(a) for a in propositions]
    for stateNum in range(len(baseUVW.stateNames)):
        baseUVW.ddMgr.declare("uvwState" + str(stateNum))
        bddVariables.append(baseUVW.ddMgr.add_expr("uvwState"+str(stateNum)))
        allBDDVarNames.append("uvwState"+str(stateNum))

    # =======================================
    # Compute reachable states in the monitor
    # =======================================
    for stateNum in range(len(baseUVW.stateNames)):
        baseUVW.ddMgr.declare("uvwState" + str(stateNum)+"post")
    trans = baseUVW.ddMgr.true
    for s in range(len(baseUVW.stateNames)):
        postBDD = baseUVW.ddMgr.false
        for fromState in range(len(baseUVW.stateNames)):
            for (a, b) in baseUVW.transitions[fromState]:
               if a==s:
                   postBDD = postBDD | (baseUVW.ddMgr.add_expr("uvwState"+str(fromState)) & b)
        # print("POST ",s,":",baseUVW.ddMgr.to_expr(postBDD))
        trans = trans & baseUVW.ddMgr.add_expr("uvwState"+str(s)+"post").equiv(postBDD)
        # print("POST uvwState"+str(s)+":"+postBDD.to_expr())

    reachable = baseUVW.ddMgr.true
    for i, s in enumerate(baseUVW.stateNames):
        if i in baseUVW.initialStates:
            reachable = reachable & baseUVW.ddMgr.add_expr("uvwState" + str(i))
        else:
            reachable = reachable & ~baseUVW.ddMgr.add_expr("uvwState" + str(i))
    # saturate
    # print("REACH:", baseUVW.ddMgr.to_expr(reachable))
    oldReachable = baseUVW.ddMgr.false
    while oldReachable != reachable:
        oldReachable = reachable
        reachable = reachable & trans
        # print("REACHX:", baseUVW.ddMgr.to_expr(reachable))
        for a in propositions:
            reachable = baseUVW.ddMgr.exist([a], reachable)
        for stateNum in range(len(baseUVW.stateNames)):
            reachable = baseUVW.ddMgr.exist(["uvwState"+str(stateNum)], reachable)
        replaceDict = {"uvwState"+str(a)+"post" : "uvwState"+str(a) for a in range(0,len(baseUVW.stateNames))}
        
        # ...remove error states, though
        reachable = baseUVW.ddMgr.let(replaceDict,reachable) & ~baseUVW.ddMgr.add_expr("uvwState0") | oldReachable

    # debug
    # print("REACH:", baseUVW.ddMgr.to_expr(reachable))
    allReach = bddToDNF(reachable, baseUVW.ddMgr, baseUVW.ddMgr.true, bddVariables[len(propositions):], allBDDVarNames[len(propositions):])
    # print("allReach: ",allReach)



    # Compute number of Bits for each state buffer - Recursively
    bufferSizesInBits = [-1 for state in baseUVW.stateNames]
    incomingTransitionsUVWExceptForSelfLoops = [[] for state in baseUVW.stateNames]
    incomingTransitionsUVWIncludingSelfLoops = [[] for state in baseUVW.stateNames]
    for s in range(len(baseUVW.stateNames)):
        for (a, b) in baseUVW.transitions[s]:
            if (a != s):
                incomingTransitionsUVWExceptForSelfLoops[a].append((s, b))
            incomingTransitionsUVWIncludingSelfLoops[a].append((s, b))

    # Reorder incomingTransitions So That Self Loops are in the front!
    # This is important for code generation so that buffer contents
    # are only overwritten when needed.
    for s in range(0,len(incomingTransitionsUVWIncludingSelfLoops)):
        theseTrans = incomingTransitionsUVWIncludingSelfLoops[s]
        newTrans = [(a,b) for (a,b) in theseTrans if a==s]
        newTrans += [(a, b) for (a, b) in theseTrans if a != s]
        incomingTransitionsUVWIncludingSelfLoops[s] = theseTrans

    nofBitsIncomingTransitions = []
    for s in range(len(baseUVW.stateNames)):
        # Count non-self-looping transitions
        cnt = 0
        for (a, b) in incomingTransitionsUVWExceptForSelfLoops[s]:
            if (a != s):
                cnt += 1
        if cnt > 0:
            nofBitsIncomingTransitions.append(math.ceil(math.log(cnt) / math.log(2)))
        else:
            nofBitsIncomingTransitions.append(0)

    def recurseComputerBufferSizes(uvwState):
        if bufferSizesInBits[uvwState] != -1:
            return
        maxBufferSize = 0
        for (a, b) in incomingTransitionsUVWExceptForSelfLoops[uvwState]:
            recurseComputerBufferSizes(a)
            maxBufferSize = max(maxBufferSize,
                                bufferSizesInBits[a] + len(propositions) + nofBitsIncomingTransitions[uvwState])
        bufferSizesInBits[uvwState] = maxBufferSize

    for s in range(len(baseUVW.stateNames)):
        recurseComputerBufferSizes(s)

    # Compute buffer sizes in #32-bit uints
    bufferSizesInWords = [int(math.ceil(a / 32.0)) for a in bufferSizesInBits]

    # print("Buffer sizes:",bufferSizesInBits)
    # print(nofBitsIncomingTransitions)

    # Sanity check -- at most 32 bits added per trace element
    # (the sanity check fails slightly unnecessarily if there are no transitions in the UVW)
    maxNofBitsTransitions = max(1, max([len(a) for a in incomingTransitionsUVWExceptForSelfLoops]))
    assert math.ceil(math.log(maxNofBitsTransitions) / math.log(2)) + len(propositions) <= 32


    # Compute AIG for all if conditions
    conditionBits = {}
    for toState in range(len(baseUVW.stateNames)):

        # Enumerate all incoming transitions
        parts = []
        for transitionIndex,(fromState, condition) in enumerate(incomingTransitionsUVWIncludingSelfLoops[toState]):

            # Compute DNF of the condition
            dnfLabel = bddToDNF(condition, baseUVW.ddMgr, baseUVW.ddMgr.true, bddVariables, allBDDVarNames)
            allDisjuncts = []
            for label in dnfLabel:
                allConjuncts = []
                for i,value in enumerate(label):
                    if value!=None:
                        if value:
                            allConjuncts.append(allBDDVarNames[i])
                        else:
                            allConjuncts.append(("!",allBDDVarNames[i]))
                allDisjuncts.append(("&",tuple(allConjuncts)))
            parts.append(("&",(("|",tuple(allDisjuncts)),"uvwState"+str(fromState))))
            # if not fromState==toState:
            conditionBits["uvwState"+str(toState)+"incoming"+str(transitionIndex)] = parts[-1]

        conditionBits["uvwState" + str(toState) + "Next"] = ("|", tuple(parts))

    # Temp Path
    tempDir = tempfile.mkdtemp()
    assert not " " in tempDir

    try:

        # Write AIG to (BLIF) file
        with open(os.path.join(tempDir,"test.blif"),"w") as blifFile:

            blifFile.write(".model monitorBlif\n")
            blifFile.write(".inputs")
            for a in allBDDVarNames:
                blifFile.write(" "+a)
            blifFile.write("\n.outputs")
            for (a,b) in conditionBits.items():
                blifFile.write(" " + a)
            blifFile.write("\n")

            elementDictionary = {}

            def recurseEncode(outName,element):
                # Cache lookup
                if outName is None and element in elementDictionary:
                    return elementDictionary[element]

                if isinstance(element,str):
                    return element
                elif element[0]=="!":
                    # Negation
                    assert len(element)==2
                    subPart = recurseEncode(None,element[1])
                    if outName is None:
                        outName = "internal"+str(len(elementDictionary))
                    blifFile.write(".names "+subPart+" "+outName+"\n")
                    blifFile.write("0 1\n")
                    elementDictionary[element] = outName
                    return outName
                elif element[0]=="|":
                    # Negation
                    assert len(element) == 2
                    subParts = [recurseEncode(None, u) for u in element[1]]
                    if outName is None:
                        outName = "internald" + str(len(elementDictionary))
                    if len(subParts) == 0:
                        blifFile.write(".names " + outName + "\n")
                        elementDictionary[element] = outName
                        return outName
                    else:
                        blifFile.write(".names " + " ".join(subParts) + " " + outName + "\n")
                        for i in range(0,len(subParts)):
                            blifFile.write("-"*i+"1"+"-"*(len(subParts)-i-1)+" 1\n")
                        elementDictionary[element] = outName
                        return outName
                elif element[0]=="&":
                    # Negation
                    assert len(element) == 2
                    subParts = [recurseEncode(None, u) for u in element[1]]
                    if outName is None:
                        outName = "internalc" + str(len(elementDictionary))
                    if len(subParts)==0:
                        blifFile.write(".names " + outName + "\n")
                        blifFile.write(" 1\n")
                        elementDictionary[element] = outName
                        return outName
                    else:
                        blifFile.write(".names " + " ".join(subParts) + " " + outName + "\n")
                        blifFile.write("1"*len(subParts)+" 1\n")
                        elementDictionary[element] = outName
                        return outName
                else:
                    raise Exception("Unknown BLIF Encoding type: ",element[0])

            for (a,b) in conditionBits.items():
                recurseEncode(a,b)

            blifFile.write(".end\n")

        # Encode EXDC
        with open(os.path.join(tempDir,"testDC.blif"),"w") as blifFile:
            blifFile.write(".model monitorEXDC\n")
            blifFile.write(".inputs "+" ".join(allBDDVarNames))
            blifFile.write("\n.outputs exdc")
            blifFile.write("\n.names "+" ".join(allBDDVarNames)+" exdc\n")
            for case in allReach:
                blifFile.write("-"*len(propositions))
                for a in case:
                    if a is None:
                        blifFile.write("-")
                    elif a == False:
                        blifFile.write("0")
                    elif a == True:
                        blifFile.write("1")
                blifFile.write(" ")
                # blifFile.write("1"*len(baseUVW.stateNames))
                blifFile.write("0")
                blifFile.write("\n")

            blifFile.write(".end\n")


        # Optimize using ABC or Mockturtle
        # ABC: with subprocess.Popen("./abc -c \"read "+os.path.join(tempDir,"test.blif")+"; resyn3; resyn2; resyn3; resyn2; resyn3; write "+os.path.join(tempDir,"testOPT.blif\""),shell=True) as abcProcess:

        # Mockturtle preparation - Convert to an AIG using ABC
        #shutil.copyfile(os.path.join(scriptPath,"../../lib/abc/abc.rc"),os.path.join(tempDir,"abc.rc"))
        #shutil.copyfile(os.path.join(scriptPath,"../../lib/abc/abc"),os.path.join(tempDir,"abc"))
        #shutil.copymode(os.path.join(scriptPath,"../../lib/abc/abc"),os.path.join(tempDir,"abc"))
        #assert os.system("cd "+str(tempDir)+"; ./abc -c \"read test.blif; resyn2; write test.blif; read testDC.blif; resyn2; write testDC.blif\"")==0

        # Mockturtle
        shutil.copyfile(os.path.join(scriptPath,"../../lib/mockturtle/build/examples/exdc"),os.path.join(tempDir,"exdc"))
        shutil.copymode(os.path.join(scriptPath,"../../lib/mockturtle/build/examples/exdc"),os.path.join(tempDir,"exdc"))
        
        with subprocess.Popen("cd "+tempDir+"; ./exdc",shell=True) as abcProcess:
            assert abcProcess.wait() == 0

        # Read back BLIF file
        aigDefinitions = {}
        orderAIGNodes = []
        with open(os.path.join(tempDir,"testOPT.blif"),"r") as blifInFile:
            currentAIGDefinition = None
            overlay = None
            for line in blifInFile.readlines():
                if not overlay is None:
                    line = overlay + line.strip()
                if line.strip().endswith("\\"):
                    line = line.strip()
                    overlay = line[0:len(line)-1]
                else:
                    overlay = None
                    if line.startswith("#"):
                        pass
                    elif line.startswith("."):
                        # special
                        if line.startswith(".model"):
                            pass
                        elif line.startswith(".inputs"):
                            inputAPsRead = line[8:].strip().split(" ")
                            if not inputAPsRead==allBDDVarNames:
                                raise Exception("Not the same inputs: \n"+str(inputAPsRead)+"\n"+str(allBDDVarNames))
                        elif line.startswith(".outputs"):
                            outputAPsRead = line[8:].strip().split(" ")
                            if outputAPsRead!=[a for (a,b) in conditionBits.items()]:
                                raise Exception("Not the same outputs: \n"+str(outputAPsRead)+"\n"+str(conditionBits))
                        elif line.startswith(".end"):
                            pass
                        elif line.startswith(".names"):
                            aps = line[7:].strip().split(" ")
                            aps = [a for a in aps if not a==""] # Filter spurious empty names
                            assert not aps[-1] in aigDefinitions
                            aigDefinitions[aps[-1]] = [aps[0:len(aps)-1],[]]
                            currentAIGDefinition = aps[-1]
                            orderAIGNodes.append(aps[-1])
                    else:
                        aigDefinitions[currentAIGDefinition][1].append(line.strip())


        # =============================================================================
        # Encode optimization problem for multi-output LUT generation as PySAT instance
        # =============================================================================
        from pysat.formula import CNF, IDPool
        from pysat.solvers import Cadical
        from pysat.card import CardEnc, EncType

        # Define solution variables
        nofVarsSoFar = 0
        formula = CNF()
        varsLUTInputSelection = []
        varsLUTSignalDefinition = []
        for lut in range(nofLUTs):

            # LUT Inputs
            thisOne = {}
            varsLUTInputSelection.append(thisOne)
            for a in allBDDVarNames:
                nofVarsSoFar += 1
                thisOne[a] = nofVarsSoFar
                print("Input Def",lut,a+": ",nofVarsSoFar)
            for a in aigDefinitions:
                nofVarsSoFar += 1
                thisOne[a] = nofVarsSoFar
                print("Input Def",lut,a + ": ", nofVarsSoFar)

            # LUT Outputs
            thisOne = {}
            varsLUTSignalDefinition.append(thisOne)
            for a in aigDefinitions:
                nofVarsSoFar += 1
                thisOne[a] = nofVarsSoFar
                print("Output Def",lut,a + ": ", nofVarsSoFar)

        # Encode: Every output signal must be defined at least once
        for a in aigDefinitions:
            formula.append([varsLUTSignalDefinition[j][a] for j in range(nofLUTs)])

        # Encode: Every LUT can only define the outputs that it has the input to
        for lut in range(nofLUTs):
            for (aigNodeName,aigDef) in aigDefinitions.items():
                inputSignals = aigDef[0]
                print("Input signals of "+str(aigNodeName)+": "+str(inputSignals),"for lut",lut)
                for insig in inputSignals:
                    if insig in aigDefinitions:
                        # Inner signal
                        prevDefinitions = [varsLUTSignalDefinition[lutm][insig] for lutm in range(0,lut)]
                        formula.append([-1*varsLUTSignalDefinition[lut][aigNodeName],varsLUTSignalDefinition[lut][insig]]+prevDefinitions)
                        formula.append([-1 * varsLUTSignalDefinition[lut][aigNodeName],varsLUTSignalDefinition[lut][insig],varsLUTInputSelection[lut][insig]])
                    else:
                        # Input signal - has to come from here.
                        formula.append([-1 * varsLUTSignalDefinition[lut][aigNodeName], varsLUTInputSelection[lut][insig]])
                        

        # Encode: at most nofInputsPerLUT selected per level
        vpool = IDPool(start_from=nofVarsSoFar+1)
        for lut in range(nofLUTs):
            am1 = CardEnc.atmost([b for (a,b) in varsLUTInputSelection[lut].items()],nofInputsPerLUT,vpool=vpool, encoding=EncType.totalizer)
            formula.extend(am1)

        formula.to_file(os.path.join(tempDir,"test.cnf"))
        
        print("Wrote CNF file to:",os.path.join(tempDir,"test.cnf"))
        sys.stdout.flush()
        
        if RUN_CADICAL:
            with Cadical(bootstrap_with=formula.clauses) as l:
                if l.solve() == False:
                    raise Exception("No solution.")
                else:
                    # Get solution
                    solution = set(l.get_model())
            print("Execution finished.")

        else:        
            # Run Kissat
            kissatProcess = subprocess.Popen(scriptPath+"/../../lib/kissat/build/kissat "+os.path.join(tempDir,"test.cnf"),stdout=subprocess.PIPE,encoding="utf-8",shell=True)
            isSAT = None
            solution = set([])
            for inputLine in kissatProcess.stdout.readlines():
                if inputLine=="s SATISFIABLE\n":
                    isSAT = True
                elif inputLine=="s UNSATISFIABLE\n":
                    isSAT = False
                if inputLine.startswith("v "):
                    line = inputLine.split(" ")
                    for a in line[1:]:
                        if a!=0:
                            solution.add(int(a))
            if isSAT is None:
                raise Exception("Did not find Kissat result. Was the process terminated? Does the Kissat executable exist?")
            if not isSAT:
                raise Exception("Error: No solution found. Cannot compute monitor.")
            kissatProcess.wait()
        

        # Compute representation of LUTs
        # Compute LUTs
        locations = {}
        locationsMask = {}
        for i, p in enumerate(propositions):
            locations[p] = "(apValues & " + str(1 << i) + ")"
            locationsMask[p] = ("apValues", i)
        for i, p in enumerate(baseUVW.stateNames):
            locations["uvwState" + str(i)] = "uvwState" + str(i)
            locationsMask["uvwState" + str(i)] = ("uvwState" + str(i),0)
        LUTLocalIO = []
        for lut in range(0, nofLUTs):

            # LUT input
            localInputs = []
            for i, a in enumerate(varsLUTInputSelection[lut]):
                if varsLUTInputSelection[lut][a] in solution:
                    localInputs.append(a)
                    #print("LOCAL INPUT TO LUT "+str(lut)+" : ",a,varsLUTInputSelection[lut][a])

            # LUT output
            localOutputs = []
            for i, a in enumerate(aigDefinitions):
                if varsLUTSignalDefinition[lut][a] in solution:
                    localOutputs.append(a)
                    #print("LOCAL OUTPUT TO LUT "+str(lut)+" : ",a,varsLUTSignalDefinition[lut][a])

            LUTLocalIO.append((localInputs, localOutputs))

        # Clean the LUTs by input not actually needed
        print("Preopt A:", LUTLocalIO)
        for lut in range(0, nofLUTs):
            inputsNeeded = set([])

            # ---> (a) input is not needed for the chosen output
            for output in LUTLocalIO[lut][1]:
                for b in aigDefinitions[output][0]:
                    inputsNeeded.add(b)

            # ---> (b) input than cannot be derived from other input
            finalInputNeeded = set([])
            for localIn in inputsNeeded:
            
                if not localIn in aigDefinitions:
                    finalInputNeeded.add(localIn)
                else:
                    foundAll = True
                    for b in aigDefinitions[localIn][0]:
                        if not b in inputsNeeded:
                            foundAll = False
                    if not foundAll:
                        finalInputNeeded.add(localIn)
                
            LUTLocalIO[lut] = ([a for a in LUTLocalIO[lut][0] if a in finalInputNeeded],LUTLocalIO[lut][1])
        
        

        # Clean the LUTs by output not actually needed
        print("Preopt B:",LUTLocalIO)
        outputsDefined = set([])
        for lut in range(0, nofLUTs):
            newOutput = []
            for output in LUTLocalIO[lut][1]:
                usedElsewhere = False
                # Used in other LUT?
                for otherLUT in range(lut+1,nofLUTs):
                    if output in LUTLocalIO[otherLUT][0]:
                        usedElsewhere = True
                # Primary output=
                if output.startswith("uvwState"):
                    usedElsewhere = True
                if usedElsewhere:
                    if not output in outputsDefined: # Already defined
                        newOutput.append(output)
                        outputsDefined.add(output)

            LUTLocalIO[lut] = (LUTLocalIO[lut][0],newOutput)


        # print("Locations:")
        # for (a,b) in locations.items():
        #     print("- ",a,":",b)

        # Support check
        for (a,b) in LUTLocalIO:
            if len(b)>32:
                raise Exception("Too many LUT outputs. Currently unsupported.")


        # Rearrange input and output so that few inline ORs are necessary in the LUT lookup
        # 1. Start with the input propositions
        fixedInputs = set([])
        for lut,(a,b) in enumerate(LUTLocalIO):
            for j,ap in enumerate(propositions):
                if ap in a:
                    if j<len(a):
                        oldPos = a.index(ap)
                        if oldPos!=j:
                            tmp1 = a[oldPos]
                            tmp2 = a[j]
                            a[j] = tmp1
                            a[oldPos] = tmp2
                        fixedInputs.add((lut,j))
        # 2. Fix others
        for lut,(a,b) in enumerate(LUTLocalIO):
            newOutputOrder = [None for i in LUTLocalIO[lut][1]]
            for j,output in enumerate(LUTLocalIO[lut][1]):
                possibleLocations = [0 for tmp in LUTLocalIO[lut][1]]
                for otherlut,(a2,b2) in enumerate(LUTLocalIO):
                    if otherlut>lut:
                        if output in a2:
                            for pos in range(len(LUTLocalIO[lut][1])):
                                if not (otherlut,pos) in fixedInputs:
                                    possibleLocations[pos] += 1
                # Search for best sos
                bestPos = -1
                bestPosValue = -1
                for i in range(len(LUTLocalIO[lut][1])):
                    if newOutputOrder[i]==None:
                        if possibleLocations[i]>bestPosValue:
                            bestPos = i
                            bestPosValue = possibleLocations[i]
                newOutputOrder[bestPos] = output
                
                # Fix others
                for otherlut,(a2,b2) in enumerate(LUTLocalIO):
                    if otherlut>lut:
                        if output in a2:
                            if not (otherlut,bestPos) in fixedInputs:
                                if bestPos<len(a2):
                                    # Swap
                                    tmp1 = a2[a2.index(output)]
                                    tmp2 = a2[bestPos]
                                    a2[a2.index(output)] = tmp2
                                    a2[bestPos] = tmp1
                                    fixedInputs.add((otherlut,bestPos))

            assert not None in newOutputOrder
            LUTLocalIO[lut] = (LUTLocalIO[lut][0],newOutputOrder)


        print("Lookup-Table contents:")
        for lut in range(0,nofLUTs):
            print("- LUT "+str(lut)+" has:")
            print("  -> Inputs "+" ".join([a for a in varsLUTInputSelection[lut] if varsLUTInputSelection[lut][a] in solution]))
            print("  -> Inputs Cleaned: "+" ".join(LUTLocalIO[lut][0]))
            print("  -> Outputs " + " ".join([a for a in aigDefinitions if varsLUTSignalDefinition[lut][a] in solution]))
            print("  -> Outputs Cleaned: " + " ".join(LUTLocalIO[lut][1]))                

        # Define locations
        print("Preopt B:",LUTLocalIO)
        for lut in range(0, nofLUTs):
            for j,output in enumerate(LUTLocalIO[lut][1]):
                if not output in locations: # Already defined
                    locations[output] = "(lut" + str(lut) + "output & " + str(1 << j) + ")"
                    locationsMask[output] = ("lut" + str(lut) + "output",j)


        # Declare variables in Monitor code
        print("#include \"UVWMonitor.h\"", file=outFile)
        print("#include <stdbool.h>", file=outFile)
        print("/* Declare variables for monitoring */", file=outFile)

        for uvwState in range(len(baseUVW.stateNames)):
            if uvwState in baseUVW.initialStates:
                print("bool uvwState" + str(uvwState) + " = 1;", file=outFile)
            else:
                print("bool uvwState"+str(uvwState)+" = 0;",file=outFile)

        print("struct bufType {", file=outFile)
        bufferVarNames = {}
        initParts = []
        for i, a in enumerate(bufferSizesInWords):
            for j in range(a):
                bufferVarNames[(i, j)] = "buf.b" + str(i) + "p" + str(j);
                print("  uint32_t b" + str(i) + "p" + str(j) + ";", file=outFile)
                initParts.append("0")
        print("} buf = {" + ",".join(initParts) + "};", file=outFile)
        for i, a in enumerate(bufferSizesInWords):
            if bufferSizesInBits[i] == 0:
                bufferVarNames[(i, 0)] = "b" + str(i) + "p" + str(0);
                print("const uint32_t b" + str(i) + "p0 = 0;", file=outFile)
        for i, a in enumerate(bufferSizesInWords):
            if livenessMonitoring and baseUVW.rejecting[i] and i > 0:  # No counter for the FASLE
                print("uint32_t cnt" + str(i) + " = 0;", file=outFile)

        # LUT TableslocalOutputs
        print("", file=outFile)
        for lut in range(nofLUTs):
            (localInputs,localOutputs) = LUTLocalIO[lut]

            # Build LUT table
            if len(localOutputs)<=8:
                print("const uint8_t ",file=outFile,end="")
            elif len(localOutputs)<=16:
                print("const uint16_t ", file=outFile, end="")
            else:
                print("const uint32_t ", file=outFile, end="")
            print("lut"+str(lut)+"["+str(1 << len(localInputs))+"] = {", file=outFile,end="")
            for lutInput in range(1 << len(localInputs)):
                # print("LUT:",lut,lutInput)
                assignments = {}
                for i,a in enumerate(localInputs):
                    assignments[a] = (lutInput & (1 << i))>0
                # Populate assignments
                for aigNode in orderAIGNodes:
                    theseInputs = aigDefinitions[aigNode][0]
                    valueLines = aigDefinitions[aigNode][1]
                    allInputsSet = True
                    inputVector = ""
                    for a in theseInputs:
                        if not a in assignments:
                            allInputsSet = False
                        else:
                            if assignments[a]:
                                inputVector = inputVector + "1"
                            else:
                                inputVector = inputVector + "0"
                    match = None
                    # print("INPUT:", inputVector,aigNode)
                    if allInputsSet:
                        for line in valueLines:
                            thisMatch = True
                            for j,b in enumerate(inputVector):
                                if line[j]!=inputVector[j] and line[j]!='-':
                                    thisMatch = False
                            if thisMatch:
                                if line[-1]=='1':
                                    match = True
                                elif line[-1]=='0':
                                    match = False
                                else:
                                    raise Exception("Can't parse BLIF line.")
                        if match is None:
                            # Default
                            if valueLines[0][-1] == '1':
                                match = False
                            else:
                                match = True
                        assignments[aigNode] = match
                # Ok, now compile the output
                # print("Asign:",assignments)
                overallValue = 0
                for j,out in enumerate(localOutputs):
                    assert not assignments[out] is None # If this fails, then in the input BLIF file, the AIG nodes are not in topological order - all gates must only use inputs already defined.
                    if assignments[out]:
                        overallValue += (1 << j)

                # Printing
                if (lutInput % 8)==0 and lutInput>0:
                    print("\n    ",end="",file=outFile)
                print(hex(overallValue),end="",file=outFile)
                if lutInput < (1 << len(localInputs))-1:
                    print(",",end="",file=outFile)
            print("};",file=outFile)

        # Main monitoring function
        print("\nvoid monitorUpdate(uint32_t apValues) {", file=outFile)

        # Compute LUTs
        for lut in range(0,nofLUTs):

            # LUT input
            # -> Use the trick to pass through bits that are already at the right location.
            print("  uint32_t lut"+str(lut)+"input = ", file=outFile,end="")
            passThrough = {}
            allParts = []
            for i,a in enumerate(LUTLocalIO[lut][0]):

                maskLocation = locationsMask[a]
                if i==maskLocation[1]:
                    if not maskLocation[0] in passThrough:
                        passThrough[maskLocation[0]] = 1 << maskLocation[1]
                    else:
                        passThrough[maskLocation[0]] |= 1 << maskLocation[1]
                else:
                    allParts.append("("+locations[a]+">0?"+str(1<<i)+":0)")
            
            # Passthrough
            for (a,b) in passThrough.items():
                allParts.append("("+a+" & "+str(b)+")")

            # Join them all
            print(" | ".join(allParts),file=outFile,end="")

            if len(allParts)==0:
                print("0",file=outFile,end="") # Special case - LUT not actually used.
            print(";",file=outFile)

            # LUT output
            print("  uint32_t lut" + str(lut) + "output = lut"+str(lut)+"[lut"+str(lut)+"input];", file=outFile)


        for stateNum in range(len(baseUVW.stateNames)):

            # Incoming transitions - copy buffer information
            first = True
            for i,(fromState,condition) in enumerate(incomingTransitionsUVWIncludingSelfLoops[stateNum]):
                if first:
                    print("  ", file=outFile,end="")
                if not first:
                    print(" else ", file=outFile, end="")
                first = False
                transitionCond = locations["uvwState"+str(stateNum)+"incoming"+str(i)]
                print("if ("+transitionCond, file=outFile, end="")
                print(") {", file=outFile)

                if fromState!=stateNum:
                    # print("Mux: ",baseUVW.transitions[fromState])
                    indexIncomingTransition = -1
                    for transitionIndex, (ls, ll) in enumerate(
                            incomingTransitionsUVWExceptForSelfLoops[stateNum]):
                        # print("ENUM:",ls,ll,fromState,fromState)
                        if (ls, ll) == (fromState, condition):
                            indexIncomingTransition = transitionIndex
                    assert indexIncomingTransition != -1

                    # Low bits
                    fromUVW = fromState
                    toUVW = stateNum
                    for index in range(0, bufferSizesInBits[fromUVW] // 32):
                        print("        " + bufferVarNames[(toUVW, index)] + " = " + bufferVarNames[
                            (fromUVW, index)] + +";", file=outFile)
                    
                    if fullmod32(bufferSizesInBits[fromUVW]) < fullmod32(bufferSizesInBits[toUVW]):
                        # Simple case: appending all to the same part
                        wordIndex = bufferSizesInBits[fromUVW] // 32
                        assert len(propositions)>0
                        # Copy part
                        # TODO: This fails for large specs. Index computations do not seem to be correct.
                        print("        " + bufferVarNames[(toUVW, wordIndex)] + " = " +
                              bufferVarNames[(fromUVW, wordIndex)], end="", file=outFile)
                        # Add proposition values
                        print(" | (apValues << " + str(
                            fullmod32(bufferSizesInBits[toUVW]) - nofBitsIncomingTransitions[
                                toUVW] - len(propositions)) + ")", end="", file=outFile)

                        # Add source
                        if nofBitsIncomingTransitions[toUVW] > 0:
                            print(" | (" + str(indexIncomingTransition) + " << " + str(
                                fullmod32(bufferSizesInBits[toUVW]) - nofBitsIncomingTransitions[
                                    toUVW]) + ")", end="", file=outFile)
                        print(";", file=outFile)
                    else:
                        wordIndexFrom = bufferSizesInBits[fromUVW] // 32
                        print("        uint32_t addedInformation = "+str(indexIncomingTransition)+" + (apValues << "+str(nofBitsIncomingTransitions[toUVW])+");", file=outFile)
                        nofAddedBits = len(propositions)+nofBitsIncomingTransitions[toUVW]
                        assert(nofAddedBits<=32) # Otherwise spec is too big. 
                        
                        print("        " + bufferVarNames[(toUVW, wordIndexFrom)] + " = " +
                              bufferVarNames[(fromUVW, wordIndexFrom)], end="", file=outFile)
                        print(" | (addedInformation << " + str(
                            32+(bufferSizesInBits[toUVW] % 32)- nofBitsIncomingTransitions[
                                toUVW] - len(propositions))+")", end=";\n", file=outFile)
                            
                        # Start next buffer content
                        remainingBits = bufferSizesInBits[toUVW] % 32
                        print("        " + bufferVarNames[(toUVW, wordIndexFrom+1)] + " = addedInformation >> "+str(len(propostions)+nofBitsIncomingTransitions[toUVW] - remainingBits)+";", end="\n", file=outFile)
                        outFile.flush()
                    
                        raise Exception("This case is currently untested.")

                else:
                    # Counter increase
                    if livenessMonitoring:
                        if not (stateNum == 0) and baseUVW.rejecting[stateNum]:
                            print("    cnt" + str(stateNum) + "++;", file=outFile)
                            print("    if ((cnt" + str(stateNum) + " & FREQUENCY_MASK_STARVATION_LOGGING)==0) {",
                                  file=outFile)
                            print("      logLivenessStarvation(" + str(stateNum) + ",cnt" + str(
                                stateNum) + ", &buf.b" + str(
                                stateNum) + "p0," + str(bufferSizesInWords[stateNum]) + ");", file=outFile)
                            print("    }", file=outFile)

                if stateNum==0:
                    print("    logViolationExplanation(0,&(buf.b0p0)," + str(bufferSizesInWords[0] * 4) + ");", file=outFile)

                print("  }", file=outFile,end="")
            print("", file=outFile)

        # Next states
        for i, a in enumerate(baseUVW.stateNames):
            # Old, slightly larger code print("  uvwState"+str(i) + " = ("+ locations["uvwState"+str(i)+"Next"]+")>0?1:0;", file=outFile)
            print("  uvwState"+str(i) + " = "+ locations["uvwState"+str(i)+"Next"]+";", file=outFile)
        print("")
        print("}\n", file=outFile)

        # Add decoding information for the buffers:
        print("/* Decoding information for the buffers:", file=outFile)
        print("   -------------------------------------\n", file=outFile)
        for i in range(0, len(baseUVW.stateNames)):
            print(" - UVW state " + str(i) + " with LTL subformula (Polish notation):", file=outFile)
            if bufferSizesInBits[i] == 0:
                print("    Initial state only", file=outFile)
            else:
                if (bufferSizesInBits[i] - nofBitsIncomingTransitions[i] - len(propositions)) > 0:
                    print("    Bits 0 to " + str(bufferSizesInBits[i] - nofBitsIncomingTransitions[i] - len(
                        propositions) - 1) + ": previous buffer", file=outFile)
                print("    Bits " + str(
                    bufferSizesInBits[i] - nofBitsIncomingTransitions[i] - len(propositions)) + " to " + str(
                    bufferSizesInBits[i] - nofBitsIncomingTransitions[i] - 1) + ": propositions", file=outFile)
                if nofBitsIncomingTransitions[i] > 0:
                    print("    Bits " + str(bufferSizesInBits[i] - nofBitsIncomingTransitions[i]) + " to " + str(
                        bufferSizesInBits[i] - 1) + ": incoming transition", file=outFile)
                    for transitionIndex, (ls, ll) in enumerate(incomingTransitionsUVWExceptForSelfLoops[i]):
                        print("       -> Value " + str(transitionIndex) + " for transition from UVW state " + str(ls),
                              file=outFile)

        print("\n", file=outFile)
        print("UVW on which the monitor is based:\n", baseUVW_string_rep, file=outFile)

        print("*/", file=outFile)

        # Print LUT information
        print("\n/* Lookup-Table contents:", file=outFile)
        for lut in range(0,nofLUTs):
            print("- LUT "+str(lut)+" has:", file=outFile)
            print("  -> Inputs "+" ".join(LUTLocalIO[lut][0]), file=outFile)
            print("  -> Outputs " + " ".join(LUTLocalIO[lut][1]), file=outFile)
        print("*/",file=outFile)
    finally:
        # Clean up temp directory
        if not PRINTDEBUGINFO:
            shutil.rmtree(tempDir)

def generateMonitorCodeDeterministic(dfa,baseUVW,propositions,livenessMonitoring,outFile):

    # Prepare BDD variables
    bddVariables = [baseUVW.ddMgr.add_expr(a) for a in propositions]
    
    # Compute number of Bits for each state buffer - Recursively
    bufferSizesInBits = [-1 for state in baseUVW.stateNames]
    incomingTransitionsUVWExceptForSelfLoops = [[] for state in baseUVW.stateNames]
    for s in range(len(baseUVW.stateNames)):
        for (a,b) in baseUVW.transitions[s]:
            if (a!=s):
                incomingTransitionsUVWExceptForSelfLoops[a].append((s,b))
    nofBitsIncomingTransitions = []
    for s in range(len(baseUVW.stateNames)):
        # Count non-self-looping transitions
        cnt = 0
        for (a,b) in incomingTransitionsUVWExceptForSelfLoops[s]:
            if (a!=s):
                cnt += 1
        if cnt>0:
            nofBitsIncomingTransitions.append(math.ceil(math.log(cnt)/math.log(2)))
        else:
            nofBitsIncomingTransitions.append(0)
    
    def recurseComputerBufferSizes(uvwState):
        if bufferSizesInBits[uvwState]!=-1:
            return
        maxBufferSize = 0    
        for (a,b) in incomingTransitionsUVWExceptForSelfLoops[uvwState]:
            recurseComputerBufferSizes(a)
            maxBufferSize = max(maxBufferSize,bufferSizesInBits[a]+len(propositions) + nofBitsIncomingTransitions[uvwState])
        bufferSizesInBits[uvwState] = maxBufferSize

    for s in range(len(baseUVW.stateNames)):
        recurseComputerBufferSizes(s)
    
    # Compute buffer sizes in #32-bit uints
    bufferSizesInWords = [int(math.ceil(a/32.0)) for a in bufferSizesInBits]

    # print("Buffer sizes:",bufferSizesInBits)
    # print(nofBitsIncomingTransitions)
    
    
    # Sanity check -- at most 32 bits added per trace element
    # (the sanity check fails slightly unnecessarily if there are no transitions in the UVW)
    maxNofBitsTransitions = max(1,max([len(a) for a in incomingTransitionsUVWExceptForSelfLoops]))
    assert math.ceil(math.log(maxNofBitsTransitions)/math.log(2))+len(propositions) <= 32

    # Declare variables in Monitor code
    print("#include \"UVWMonitor.h\"",file=outFile)    
    print("/* Declare variables for monitoring */",file=outFile)
    print("uint32_t currentState = 0;",file=outFile)
    print("struct bufType {",file=outFile)
    bufferVarNames = {}
    initParts = []
    for i,a in enumerate(bufferSizesInWords):
        for j in range(a):
            bufferVarNames[(i,j)] = "buf.b"+str(i)+"p"+str(j);
            print("  uint32_t b"+str(i)+"p"+str(j)+";",file=outFile)
            initParts.append("0")
    print("} buf = {"+",".join(initParts)+"};",file=outFile)
    for i,a in enumerate(bufferSizesInWords):
        if bufferSizesInBits[i]==0:
            bufferVarNames[(i,0)] = "b"+str(i)+"p"+str(0);
            print("const uint32_t b"+str(i)+"p0 = 0;",file=outFile)            
    for i,a in enumerate(bufferSizesInWords):
        if livenessMonitoring and baseUVW.rejecting[i] and i>0: # No counter for the FASLE
            print("uint32_t cnt"+str(i)+" = 0;",file=outFile)
    
    # Liveness monitoring function
    if livenessMonitoring:
        print("\nvoid livenessMonitoring(uint32_t mask) {",file=outFile)
        # Check if we have a rejecting state
        index = 0
        for uvwStateNum in range(0,len(baseUVW.stateNames)):
        
            # Only copy buffers if not safety violating *or* for buffer 0
            if not (uvwStateNum==0) and baseUVW.rejecting[uvwStateNum]:
                print("  if (mask & "+str(1 << index)+") {",file=outFile)         
                print("    if ((cnt"+str(uvwStateNum)+" & FREQUENCY_MASK_STARVATION_LOGGING)==0) {",file=outFile)
                print("      logLivenessStarvation("+str(uvwStateNum)+",cnt"+str(uvwStateNum)+", &buf.b"+str(uvwStateNum)+"p0,"+str(bufferSizesInWords[uvwStateNum])+");",file=outFile)
                print("    }",file=outFile)
                print("  }",file=outFile)
                index += 1
        print("}\n",file=outFile)
    
    
    # Main monitoring function
    print("\nvoid monitorUpdate(uint32_t v) {",file=outFile)
    print("  switch (currentState) {",file=outFile)
    for s in range(len(dfa.states)):
        if not s in dfa.accepting:
            print("    case "+str(s)+":",file=outFile)
            print("      /* UVW states: "+" ".join([str(i) for i in range(len(baseUVW.stateNames)) if dfa.states[s][i]])+" */",file=outFile)
            # Iterate over the transitions and perform transitions
            careSet = baseUVW.ddMgr.true
            for transNo,(toDFA,label,uvwTrans) in enumerate(dfa.transitions[s]):
                # Try CNF and DNF for the transition condition
                # print("Cond Label: ",label.to_expr())
                dnfLabel = bddToDNF(label,baseUVW.ddMgr,careSet,bddVariables,propositions)
                cnfLabel = bddToDNF(~label,baseUVW.ddMgr,careSet,bddVariables,propositions)
                careSet &= ~label
                if transNo==0:
                    print("      if (",end="",file=outFile)
                else:
                    print("      } else if (",end="",file=outFile)


                # Try DNF Conversion
                textDNF = ""
                for i,case in enumerate(dnfLabel):
                    if i>0:
                        textDNF += " || "
                    if not False in case and not True in case:
                        textDNF += "1"
                    else:
                        (convertNumMask,convertNumVal) = bitListToCCodeNumber(case,False)
                        textDNF += "((v & "+convertNumMask+") == "+convertNumVal+")"
            
                # Try CNF Conversion
                # print("// CNF LABEL: "+str(cnfLabel))
                textCNF = ""
                if len(cnfLabel)==0:
                    textCNF = "1"
                else:
                    # Sum up CNF cases whenever possible                
                    for i,case in enumerate(cnfLabel):
                        if i>0:
                            textCNF += " && "
                        (convertNumMask,convertNumVal) = bitListToCCodeNumber(case,True)
                        textCNF += "((v | "+convertNumVal+") != "+convertNumMask+")"
            
                # Choose between CNF and DNF
                if len(textDNF)<len(textCNF):
                    print(textDNF,end="",file=outFile)
                else:
                    print(textCNF,end="",file=outFile)
                print(") {",file=outFile)
                if (toDFA==s):   
                    print("        /* Stay in the same DFA state */",file=outFile)
                else:
                    print("        currentState = "+str(toDFA)+";",file=outFile)
                
                # Update buffers
                # -> Determine which parts are new.
                newStates = []
                fromWhere = []
                for uvwStateNum in range(0,len(baseUVW.stateNames)):
                
                    # Only copy buffers if not safety violating *or* for buffer 0
                    if (not toDFA in dfa.accepting) or (uvwStateNum==0) or (not 0 in dfa.states[toDFA]):
                        
                        # Check if uvwStateNum is left along this transition -- then copying is necessary!
                        stayInUVWState = False
                        for uvwTransNo,(fromUVW,toUVW,label) in enumerate(uvwTrans):
                            if (fromUVW==toUVW) and (toUVW==uvwStateNum):
                                stayInUVWState = True

                        # Increase counter
                        if stayInUVWState and dfa.states[toDFA][uvwStateNum] and livenessMonitoring and baseUVW.rejecting[uvwStateNum]:
                            print("        cnt"+str(uvwStateNum)+"++;",file=outFile)

                        # If state is newly entered copy buffer information
                        if dfa.states[toDFA][uvwStateNum] and not stayInUVWState:
                            # Ok, this one is new. Search for transition
                            foundUVWTransition = False
                            for uvwTransNo,(fromUVW,toUVW,label) in enumerate(uvwTrans):
                                if not foundUVWTransition:
                                    if (toUVW==uvwStateNum):
                                        foundUVWTransition = True
                                        # Perform copy
                                        indexIncomingTransition = -1
                                        # print("NOF INCOMING: ",incomingTransitionsUVWExceptForSelfLoops[toUVW])
                                        for transitionIndex,(ls,ll) in enumerate(incomingTransitionsUVWExceptForSelfLoops[toUVW]):
                                            if (ls,ll)==(fromUVW,label):
                                                indexIncomingTransition = transitionIndex
                                        assert indexIncomingTransition!=-1
                                        
                                        if livenessMonitoring and baseUVW.rejecting[toUVW] and not toUVW==0:
                                            print("        cnt"+str(toUVW)+" = 0;",file=outFile)
                                        
                                        # Low bits
                                        for index in range(0,bufferSizesInBits[toUVW]//32-bufferSizesInBits[uvwStateNum]//32):
                                            print("        "+bufferVarNames[(toUVW,index)]+" = "+bufferVarNames[(fromUVW,index)]++";",file=outFile)
                                        # Cases
                                        if ((bufferSizesInBits[fromUVW]%32) < (bufferSizesInBits[toUVW]%32)) or ((bufferSizesInBits[toUVW] % 32) == 0):
                                            # Simple case: appending all to the same part
                                            wordIndex = bufferSizesInBits[fromUVW]//32
                                            # Copy part
                                            # TODO: This fails for large specs. Index computations do not seem to be correct.
                                            print("        "+bufferVarNames[(toUVW,wordIndex)]+" = "+bufferVarNames[(fromUVW,wordIndex)],end="",file=outFile)
                                            # Add proposition values
                                            print(" | (v << "+str((bufferSizesInBits[toUVW]%32)-nofBitsIncomingTransitions[toUVW]-len(propositions))+")",end="",file=outFile)
                                            
                                            # Add source
                                            if (nofBitsIncomingTransitions[toUVW]>0):
                                                print(" | ("+str(indexIncomingTransition) + " << "+str((bufferSizesInBits[toUVW]%32)-nofBitsIncomingTransitions[toUVW])+")",end="",file=outFile)
                                            print(";",file=outFile)
                                        else:
                                            raise Exception("This case is currently unimplemented.")
                            assert foundUVWTransition                            
                
                # In case we do not have a violation, increase liveness counters
                if not toDFA in dfa.accepting and livenessMonitoring:
                    
                    # The liveness monitored states are numbered through so that a mask can be used
                    posLivenessMonitoredValue = 0
                    posLivenessMonitoredPos = 0
                    
                    # Check if we have a rejecting state
                    for uvwStateNum in range(0,len(baseUVW.stateNames)):
                    
                        # Only copy buffers if not safety violating *or* for buffer 0
                        if not (uvwStateNum==0) and baseUVW.rejecting[uvwStateNum]:
                            
                            # Check if uvwStateNum is left along this transition -- then copying is necessary!
                            stayInUVWState = False
                            for uvwTransNo,(fromUVW,toUVW,label) in enumerate(uvwTrans):
                                if (fromUVW==toUVW) and (toUVW==uvwStateNum):
                                    stayInUVWState = True
                            if stayInUVWState:
                                posLivenessMonitoredValue += (1 << posLivenessMonitoredPos)
                            posLivenessMonitoredPos += 1

                    if posLivenessMonitoredValue>0:
                        print("        livenessMonitoring("+str(posLivenessMonitoredValue)+");",file=outFile)
                
                            
                # In case we had a violation, log a violation
                if toDFA in dfa.accepting:
                    # Log violation!
                    # Case 1: Safety violation -- here, we use the fact that state 0 is always
                    # the state rejecting everything in the UVW library
                    if dfa.states[toDFA][0]:
                        print("        logViolationExplanation("+str(toDFA)+",&(buf.b0p0),"+ str(bufferSizesInWords[0]*4)+");",file=outFile)
                    else:
                        print("        logViolationExplanation("+str(toDFA)+",&buf,sizeof(buf));",file=outFile)
                    
            print("      }",file=outFile)
            print("      break;",file=outFile)
    print("    default:",file=outFile)
    for s in range(len(dfa.states)):
        if s in dfa.accepting:
            print("      /* DFA State "+str(s)+" has UVW states: "+" ".join([str(i) for i in range(len(baseUVW.stateNames)) if dfa.states[s][i]])+" */",file=outFile)
    print("      break;",file=outFile)
    print("  }\n}\n",file=outFile)    
    
    # Add decoding information for the buffers:
    print("/* Decoding information for the buffers:",file=outFile)
    print("   -------------------------------------\n",file=outFile)
    for i in range(0,len(baseUVW.stateNames)):
        print(" - UVW state "+str(i)+" with LTL subformula (Polish notation):",file=outFile)
        if bufferSizesInBits[i]==0:
            print("    Initial state only",file=outFile)
        else:
            if (bufferSizesInBits[i]%32)-nofBitsIncomingTransitions[i]-len(propositions)>0:
                print("    Bits 0 to "+str((bufferSizesInBits[i]%32)-nofBitsIncomingTransitions[i]-len(propositions)-1)+": previous buffer",file=outFile)
            print("    Bits "+str((bufferSizesInBits[i]%32)-nofBitsIncomingTransitions[i]-len(propositions))+" to "+str((bufferSizesInBits[i]%32)-nofBitsIncomingTransitions[i]-1)+": propositions",file=outFile)
            if nofBitsIncomingTransitions[i]>0:
                print("    Bits "+str((bufferSizesInBits[i]%32)-nofBitsIncomingTransitions[i])+" to "+str((bufferSizesInBits[i]%32)-1)+": incoming transition",file=outFile)
                for transitionIndex,(ls,ll) in enumerate(incomingTransitionsUVWExceptForSelfLoops[i]):
                    print("       -> Value "+str(transitionIndex)+" for transition from UVW state "+str(ls),file=outFile)
                
                
            
    print("\n",file=outFile)
    print("UVW on which the monitor is based:\n",baseUVW,file=outFile)
    print("*/",file=outFile)


# ==================================
# Translate
# ==================================



def generateMonitor(inputFile,scriptbasePath,livenessMonitoring,monitorGenerationAlgorithm):
    with open(inputFile,"r") as inFile:
        allInputLines = list(inFile.readlines())
    
    # Minimum are two lines
    if len(allInputLines)<2:
        raise Exception("Error: Input file too short")
    
    # Try to parse input line. First line must be the atomic propositions
    apLine = allInputLines[0]
    if not apLine.startswith("APs: "):
        raise Exception("Error: The input file does not start with an 'APs: ' line.")
    propositions = apLine[5:].strip().split(" ")
    # Check sanity of APs
    if len(set(propositions))!=len(propositions):
        raise Exception("Error: Proposition list contains duplicate entries")

    # Second line needs to be empty
    if allInputLines[1].strip()!="":
        raise Exception("Error: The second line needs to be empty.")
        
    # Now generate UVW
    baseUVW = uvwBuilder.UVW()
    for ap in propositions:
        baseUVW.getBDDFromPropositionName(ap) # Make sure that AP is in the BDD manager
    
    for line in allInputLines[2:]:
        line = line.strip()
        if line.startswith("#") or len(line)==0:
            pass # Comment
        else:
            originalLine = line
            # Is not yet in polish normal form
            if not line.startswith("LTL "):
                # Translate to Polish
                toPolishProcess = subprocess.Popen(scriptbasePath+"src/ltltopolish/ltl2polish",stdin=subprocess.PIPE,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
                toPolishProcess.stdin.write(line.encode("utf-8"))
                toPolishProcess.stdin.close()
                if toPolishProcess.wait()!=0:
                    raise Exception("Error running ltltopolish on specification line '"+line+"': "+"\n".join([a.decode("utf-8") for a in toPolishProcess.stdout.readlines()]))
                line = [a.decode("utf-8").strip() for a in toPolishProcess.stdout.readlines() if len(a.decode("utf-8").strip())!=0]
                if len(line)!=1:
                    raise Exception("Error running ltltopolish on specification line '"+originalLine+"': too many replies.")
                line = line[0]
            # Ok, is now in polish normal form
            if not line.startswith("LTL "):
                raise Exception("Error: Line '"+line+"' is not yet in polish normal form. Note that this may be the output of the ltltopolish tool.")
                
            # Try to parse and convert using ATVA 2018 construction
            formulaNode = parser.computeNNF(parser.simplifyTree(parser.elimImplies(parser.parse(line))))
            if not parser.isATreeAcceptedByANonTerminalOfOurUVWGrammar(formulaNode,"Phi"):
                raise Exception("Error: Input is not in the supported LTL fragment: "+originalLine)
            nextUVW = uvwBuilder.constructUVW(formulaNode,baseUVW.ddMgr)
            
            # Add to existing UVW
            nextUVW.removeUnreachableStates()
            nextUVW.removeStatesWithoutOutgoingTransitions()
            baseUVW.addUVWConjunctively(nextUVW)
            baseUVW.simulationBasedMinimization()
            baseUVW.mergeEquivalentlyReachableStates()
            baseUVW.removeForwardReachableBackwardSimulatingStates()
            baseUVW.removeUnreachableStates()

    # If no liveness monitoring is performed, remove states from which the all-rejecting state cannot be reached
    if not livenessMonitoring:
        # Make all states except for state 0 non-rejecting. Then minimize
        for i in range(1, len(baseUVW.stateNames)):
            baseUVW.rejecting[i] = False
        baseUVW.simulationBasedMinimization()
        baseUVW.mergeEquivalentlyReachableStates()
        baseUVW.removeForwardReachableBackwardSimulatingStates()
        baseUVW.removeUnreachableStates()

    # Check if the LTL properties used a proposition not declared previously
    if len(baseUVW.propositions)!=len(propositions):
        for a in baseUVW.propositions:
            if not a in propositions:
                raise Exception("Error: Some LTL property used the undeclared proposition "+a)
        raise Exception("Internal Error: Proposition numbers don't add up.")
    

    # ===============================================================================
    # Optimize certain UVW patterns that increase the size of the determinized automaton:
    # ===============================================================================
    # 1. (true self-loop)---a----(rejecting state with a self loop)
    for state in range(len(baseUVW.stateNames)):
        # Does it have a TRUE self-loop
        hasTrueSelfLoop = False
        for (a,b) in baseUVW.transitions[state]:
            if a==state and b==baseUVW.ddMgr.true:
                hasTrueSelfLoop = True
        if hasTrueSelfLoop:
            # Ok, go through the successors
            for i,(a,b) in enumerate(baseUVW.transitions[state]):
                if a!=state:
                    # Only self-loops on "b" on state "a"?
                    isCandidate = True
                    for(c,d) in baseUVW.transitions[a]:
                        if c!=a or d!=b:
                            isCandidate = False
                    if isCandidate:
                        # Ok, replace
                        baseUVW.transitions[state][i] = (a,baseUVW.ddMgr.true)


    print("Computed UVW: ",baseUVW)


    # Obtain DFA from UVW
    if monitorGenerationAlgorithm=="deterministic":
        dfa = determiniseUVWForMonitoring(baseUVW)
    else:
        dfa = None
    
    # Generate monitor automaton
    return (dfa,baseUVW,propositions,livenessMonitoring)


# ==================================
# Pareto optimization
# ==================================
def paretoOptimize(baseUVW,propositions,livenessMonitoring,paretoCompiler,paretoLimit,generationAlgorithm):

    outputFileC = "/tmp/paretoCheck"+str(os.getpid())+".c" # TODO: Make proper
    outputFileObj = "/tmp/paretoCheck"+str(os.getpid())+".o" # TODO: Make proper

    
    def oracle(point):
        print("Oracle called for point ",point)
        # print("Base UVW:",baseUVW)

        # Copy UVW, but leave out transitions of states not copied
        restrictedUVW = uvwBuilder.UVW(baseUVW.ddMgr)
        for i in range(1,len(baseUVW.stateNames)):
            restrictedUVW.stateNames.append(baseUVW.stateNames[i])
            restrictedUVW.rejecting.append(baseUVW.rejecting[i])
            if point[i]>0:
                # No copy
                restrictedUVW.transitions.append([])
            else:
                restrictedUVW.transitions.append([(a,b) for (a,b) in baseUVW.transitions[i]])
        restrictedUVW.initialStates = copy.copy(baseUVW.initialStates)
        restrictedUVW.propositions = copy.copy(baseUVW.propositions)   
        
        # print("Checking Pareto Point Pre:",restrictedUVW) 

        # Optimize UVW
        restrictedUVW.removeUnreachableStates()
        restrictedUVW.removeStatesWithoutOutgoingTransitions()
        restrictedUVW.simulationBasedMinimization()
        restrictedUVW.mergeEquivalentlyReachableStates()
        restrictedUVW.removeForwardReachableBackwardSimulatingStates()
        restrictedUVW.removeUnreachableStates()
        
        # print("Checking Pareto Point:",restrictedUVW)
        
        
        # Write monitor
        with open(outputFileC,"w") as outputFile:
            dfa = determiniseUVWForMonitoring(restrictedUVW)
            generateMonitorCode(dfa,restrictedUVW,propositions,livenessMonitoring,outputFile,generationAlgorithm)
        
        # Ok, call compiler script
        assert not ";" in paretoCompiler
        assert not "," in paretoCompiler
        assert not " " in paretoCompiler
        testSizeProcess = subprocess.Popen(paretoCompiler+" "+ outputFileC,shell=True,stdout=subprocess.PIPE)
        assert testSizeProcess.wait()==0
        returnedSize = int(("".join([a.decode("utf-8").strip() for a in testSizeProcess.stdout.readlines()])))
        
        print("Size of the binary: ",returnedSize)
        return returnedSize<=paretoLimit
        return True

    limits = [(0,0)]
    for i in range(0,len(baseUVW.stateNames)):
        limits.append((0,1))

    paretoFront = pareto_enumerator.computeParetoFront(oracle,limits)
    
    print("======================[Result]======================")
    print("We have the following UVW:")
    print(baseUVW)
    print("...and to hit the size limit of "+str(paretoLimit)+" we can remove any of the following sets of states:\n")
    for element in paretoFront:
        print("- ",end="")
        for i,a in enumerate(element):
            if a:
                print(str(i),end=" ")
        print("")
    print("")

# ==================================
# Main
# ==================================
if __name__ == '__main__':

    # Compute Base path
    
    scriptBasePath = sys.argv[0][0:sys.argv[0].rfind("monitorcompiler.py")]+"../../"

    args = sys.argv[1:]

    inputFile = None
    livenessMonitoring = False
    paretoCompiler = None
    paretoLimit = 10000
    outputFile = sys.stdout

    nextCompilerScript = False
    nextParetoLimit = False
    nextOutputFile = False
    nextNOFLuts = False
    nextInputsPerLUT = False

    monitorGenerationAlgorithm = "deterministic"
    nofLUTs = None
    nofInputsPerLUT = None

    for arg in args:
        if nextCompilerScript:
            paretoCompiler = arg
            nextCompilerScript = False
        elif nextParetoLimit:
            paretoLimit = int(arg)
            nextParetoLimit = False
        elif nextOutputFile:
            outputFile = open(arg,"w")
            nextOutputFile = False
        elif nextNOFLuts:
            nextNOFLuts = False
            nofLUTs = int(arg)
        elif nextInputsPerLUT:
            nextInputsPerLUT = False
            nofInputsPerLUT = int(arg)
        elif arg.startswith("-"):
            if arg == "--debug":
                PRINTDEBUGINFO = True
            elif arg == "--liveness":
                livenessMonitoring = True
            elif arg == "--paretoCompiler":
                nextCompilerScript = True
            elif arg == "--paretoLimit":
                nextParetoLimit = True
            elif arg == "--outFile":
                nextOutputFile = True
            elif arg == "--deterministic":
                monitorGenerationAlgorithm = "deterministic"
            elif arg == "--nondeterministic":
                monitorGenerationAlgorithm = "nondeterministic"
            elif arg == "--aigBased":
                monitorGenerationAlgorithm = "aig"
            elif arg == "--nofLUTs":
                nextNOFLuts = True
            elif arg == "--nofInputsPerLUT":
                nextInputsPerLUT = True
            else:
                print("Error: Did not understand parameter: "+arg, file=sys.stderr)
                sys.exit(1)
        else:
            if not inputFile is None:
                print("Error: Multiple input files given",file=sys.stderr)
                sys.exit(1)
            inputFile = arg
            
    if inputFile is None:
        print("Error: No input file is given",file=sys.stderr)
        sys.exit(1)
    if nextCompilerScript:
        print("Error: '--paretoCompiler' needs to be followed by compiler script link")
        sys.exit(1)
    if nextParetoLimit:
        print("Error: '--paretoLimit' needs to be followed by a Pareto limit")
        sys.exit(1)
    if nextOutputFile:
        print("Error: '--outputFile' needs to be followed by an output File")
        sys.exit(1)
    if nextNOFLuts or nextInputsPerLUT:
        print("Error: next parameter expected.")
        sys.exit(1)

    
    if paretoCompiler is None:
        (dfa,baseUVW,propositions,livenessMonitoring) = generateMonitor(inputFile,scriptBasePath,livenessMonitoring,monitorGenerationAlgorithm)
        generateMonitorCode(dfa,baseUVW,propositions,livenessMonitoring,outputFile,monitorGenerationAlgorithm,nofLUTs,nofInputsPerLUT)
    else:
        (dfa,baseUVW,propositions,livenessMonitoring) = generateMonitor(inputFile,scriptBasePath,livenessMonitoring)
        paretoOptimize(baseUVW,propositions,livenessMonitoring,paretoCompiler,paretoLimit,monitorGenerationAlgorithm)
    
    
    print("Done. Exiting....",file=sys.stderr)
