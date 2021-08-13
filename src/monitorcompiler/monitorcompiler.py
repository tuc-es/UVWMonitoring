#!/usr/bin/env python3
# Monitor compiler
import sys, os
import uvwBuilder, subprocess, parser, math
import pareto_enumerator, copy


# Global parameters
PRINTDEBUGINFO = False


# ==========================================
# BDD to CNF functions
# ==========================================
def bddToDNF(bdd,mgr,careSet,bddVariables,propositions):

    result = []
    bddLB = bdd & careSet
    bddUB = bdd | ~careSet
    while bddLB!=mgr.false:
        print("BDD:",bddLB.to_expr())
        print("BDDUB:", bddUB.to_expr())
        
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


    print("RED:",result)
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
def generateMonitorCode(dfa,baseUVW,propositions,livenessMonitoring,outFile,generationAlgorithm):
    if generationAlgorithm=="deterministic":
        generateMonitorCodeDeterministic(dfa, baseUVW, propositions, livenessMonitoring, outFile)
    elif generationAlgorithm=="nondeterministic":
        generateMonitorCodeNondeterministic(dfa, baseUVW, propositions, livenessMonitoring, outFile)


def pickCNFOrDNFWhateverIsShorter(cnfLabel,dnfLabel,outFile, varNames):
    # Try DNF Conversion
    textDNF = ""
    if len(dnfLabel)==0:
        textDNF = "0"
    for i, case in enumerate(dnfLabel):
        if i > 0:
            textDNF += " || "
        if not False in case and not True in case:
            textDNF += "1"
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
    if len(textDNF) < len(textCNF):
        print(textDNF, end="", file=outFile)
    else:
        print(textCNF, end="", file=outFile)


def generateMonitorCodeNondeterministic(dfa,baseUVW,propositions,livenessMonitoring,outFile):

    # Prepare BDD variables and their compiled names
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

    for stateNum in range(len(baseUVW.stateNames)):

        # Enumerate all incoming transitions
        incoming = baseUVW.ddMgr.false
        for fromState in range(len(baseUVW.stateNames)):
            for (toState,condition) in baseUVW.transitions[fromState]:
                if toState==stateNum:
                    incoming = incoming | bddVariables[len(propositions)+fromState] & condition
        del fromState

        # print("incoming: ",incoming.to_expr())

        print("  bool nextUVW"+str(stateNum)+" = 0;",file=outFile)
        print("  if (",file=outFile,end="")
        careSet = baseUVW.ddMgr.true
        # print(allBDDVarNames,"thiathia")
        dnfLabel = bddToDNF(incoming, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
        cnfLabel = bddToDNF(~incoming, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
        pickCNFOrDNFWhateverIsShorter(cnfLabel, dnfLabel, outFile, allBDDVarNames)
        print(") {",file=outFile)
        print("    nextUVW" + str(stateNum) + " = 1;", file=outFile)

        # Not already in the state or self-loop inactive?
        print("    if (!uvwState"+str(stateNum)+" || (",file=outFile,end="")
        # Enumerate all self-loops transitions
        incoming = baseUVW.ddMgr.false
        for (toState, condition) in baseUVW.transitions[stateNum]:
            if toState == stateNum:
                incoming = incoming | condition
        dnfLabel = bddToDNF(~incoming, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
        cnfLabel = bddToDNF(incoming, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
        pickCNFOrDNFWhateverIsShorter(cnfLabel, dnfLabel, outFile, allBDDVarNames)
        print(")) {", file = outFile)
        print("      // Not previously here",file=outFile)
        if livenessMonitoring:
            if not (stateNum == 0) and baseUVW.rejecting[stateNum]:
                print("      cnt" + str(stateNum) + "=1;",file=outFile)
        first = True

        # Incoming transitions - copy buffer information
        for fromUVW in range(len(baseUVW.stateNames)):
            for (toUVW,condition) in baseUVW.transitions[fromUVW]:
                if toUVW==stateNum and fromUVW!=toUVW:
                    print("      ",file=outFile,end="")
                    if not first:
                        print("else ", file=outFile, end="")
                    first = False
                    transitionCond = bddVariables[len(propositions)+fromUVW] & condition
                    print("if (", file=outFile, end="")
                    dnfLabel = bddToDNF(transitionCond, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
                    cnfLabel = bddToDNF(~transitionCond, baseUVW.ddMgr, careSet, bddVariables, allBDDVarNames)
                    pickCNFOrDNFWhateverIsShorter(cnfLabel, dnfLabel, outFile, allBDDVarNames)
                    print(") {", file=outFile)

                    print("Mux: ",baseUVW.transitions[fromUVW])
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
                    # Cases
                    if ((bufferSizesInBits[fromUVW] % 32) < (bufferSizesInBits[toUVW] % 32)):
                        # Simple case: appending all to the same part
                        wordIndex = bufferSizesInBits[toUVW] // 32
                        # Copy part
                        # TODO: This fails for large specs. Index computations do not seem to be correct.
                        print("        " + bufferVarNames[(toUVW, wordIndex)] + " = " +
                              bufferVarNames[(fromUVW, wordIndex)], end="", file=outFile)
                        # Add proposition values
                        print(" | (apValues << " + str(
                            (bufferSizesInBits[toUVW] % 32) - nofBitsIncomingTransitions[
                                toUVW] - len(propositions)) + ")", end="", file=outFile)

                        # Add source
                        if nofBitsIncomingTransitions[toUVW] > 0:
                            print(" | (" + str(indexIncomingTransition) + " << " + str(
                                (bufferSizesInBits[toUVW] % 32) - nofBitsIncomingTransitions[
                                    toUVW]) + ")", end="", file=outFile)
                        print(";", file=outFile)
                    else:
                        raise Exception("This case is currently unimplemented.")

                    print("      }", file=outFile)

        if stateNum==0:
            print("      logViolationExplanation(0,&(buf.b0p0)," + str(bufferSizesInWords[0] * 4) + ");", file=outFile)

        # Counter increase
        if livenessMonitoring:
            if not (stateNum == 0) and baseUVW.rejecting[stateNum]:
                print("    } else {", file=outFile)
                print("      cnt" + str(stateNum) + "++;",file=outFile)
                print("      if ((cnt" + str(stateNum) + " & FREQUENCY_MASK_STARVATION_LOGGING)==0) {", file=outFile)
                print("        logLivenessStarvation(" + str(stateNum) + ",cnt" + str(stateNum) + ", &buf.b" + str(
                    stateNum) + "p0," + str(bufferSizesInWords[stateNum]) + ");", file=outFile)
                print("      }", file=outFile)

        print("    }", file=outFile)


        print("  }", file=outFile)


    for i, a in enumerate(baseUVW.stateNames):
        print("  uvwState"+str(i) + " = nextUVW"+str(i)+";", file=outFile)
    print("")
    print("}\n", file=outFile)

    if False:

        print("  switch (currentState) {", file=outFile)
        for s in range(len(dfa.states)):
            if not s in dfa.accepting:
                print("    case " + str(s) + ":", file=outFile)
                print("      /* UVW states: " + " ".join(
                    [str(i) for i in range(len(baseUVW.stateNames)) if dfa.states[s][i]]) + " */", file=outFile)
                # Iterate over the transitions and perform transitions
                careSet = baseUVW.ddMgr.true
                for transNo, (toDFA, label, uvwTrans) in enumerate(dfa.transitions[s]):
                    # Try CNF and DNF for the transition condition
                    # print("Cond Label: ",label.to_expr())
                    dnfLabel = bddToDNF(label, baseUVW.ddMgr, careSet, bddVariables, propositions)
                    cnfLabel = bddToDNF(~label, baseUVW.ddMgr, careSet, bddVariables, propositions)
                    careSet &= ~label
                    if transNo == 0:
                        print("      if (", end="", file=outFile)
                    else:
                        print("      } else if (", end="", file=outFile)


                    print(") {", file=outFile)
                    if (toDFA == s):
                        print("        /* Stay in the same DFA state */", file=outFile)
                    else:
                        print("        currentState = " + str(toDFA) + ";", file=outFile)

                    # Update buffers
                    # -> Determine which parts are new.
                    newStates = []
                    fromWhere = []
                    for uvwStateNum in range(0, len(baseUVW.stateNames)):

                        # Only copy buffers if not safety violating *or* for buffer 0
                        if (not toDFA in dfa.accepting) or (uvwStateNum == 0) or (not 0 in dfa.states[toDFA]):

                            # Check if uvwStateNum is left along this transition -- then copying is necessary!
                            stayInUVWState = False
                            for uvwTransNo, (fromUVW, toUVW, label) in enumerate(uvwTrans):
                                if (fromUVW == toUVW) and (toUVW == uvwStateNum):
                                    stayInUVWState = True

                            # Increase counter
                            if stayInUVWState and dfa.states[toDFA][uvwStateNum] and livenessMonitoring and \
                                    baseUVW.rejecting[uvwStateNum]:
                                print("        cnt" + str(uvwStateNum) + "++;", file=outFile)

                            # If state is newly entered copy buffer information
                            if dfa.states[toDFA][uvwStateNum] and not stayInUVWState:
                                # Ok, this one is new. Search for transition
                                foundUVWTransition = False
                                for uvwTransNo, (fromUVW, toUVW, label) in enumerate(uvwTrans):
                                    if not foundUVWTransition:
                                        if (toUVW == uvwStateNum):
                                            foundUVWTransition = True
                                            # Perform copy
                                            indexIncomingTransition = -1
                                            # print("NOF INCOMING: ",incomingTransitionsUVWExceptForSelfLoops[toUVW])
                                            for transitionIndex, (ls, ll) in enumerate(
                                                    incomingTransitionsUVWExceptForSelfLoops[toUVW]):
                                                if (ls, ll) == (fromUVW, label):
                                                    indexIncomingTransition = transitionIndex
                                            assert indexIncomingTransition != -1

                                            if livenessMonitoring and baseUVW.rejecting[toUVW] and not toUVW == 0:
                                                print("        cnt" + str(toUVW) + " = 0;", file=outFile)

                                            # Low bits
                                            for index in range(0, bufferSizesInBits[toUVW] // 32 - bufferSizesInBits[
                                                uvwStateNum] // 32):
                                                print("        " + bufferVarNames[(toUVW, index)] + " = " + bufferVarNames[
                                                    (fromUVW, index)] + +";", file=outFile)
                                            # Cases
                                            if ((bufferSizesInBits[fromUVW] % 32) < (bufferSizesInBits[toUVW] % 32)):
                                                # Simple case: appending all to the same part
                                                wordIndex = bufferSizesInBits[toUVW] // 32
                                                # Copy part
                                                # TODO: This fails for large specs. Index computations do not seem to be correct.
                                                print("        " + bufferVarNames[(toUVW, wordIndex)] + " = " +
                                                      bufferVarNames[(fromUVW, wordIndex)], end="", file=outFile)
                                                # Add proposition values
                                                print(" | (v << " + str(
                                                    (bufferSizesInBits[toUVW] % 32) - nofBitsIncomingTransitions[
                                                        toUVW] - len(propositions)) + ")", end="", file=outFile)

                                                # Add source
                                                if (nofBitsIncomingTransitions[toUVW] > 0):
                                                    print(" | (" + str(indexIncomingTransition) + " << " + str(
                                                        (bufferSizesInBits[toUVW] % 32) - nofBitsIncomingTransitions[
                                                            toUVW]) + ")", end="", file=outFile)
                                                print(";", file=outFile)
                                            else:
                                                raise Exception("This case is currently unimplemented.")
                                assert foundUVWTransition

                                # In case we do not have a violation, increase liveness counters
                    if not toDFA in dfa.accepting and livenessMonitoring:

                        # The liveness monitored states are numbered through so that a mask can be used
                        posLivenessMonitoredValue = 0
                        posLivenessMonitoredPos = 0

                        # Check if we have a rejecting state
                        for uvwStateNum in range(0, len(baseUVW.stateNames)):

                            # Only copy buffers if not safety violating *or* for buffer 0
                            if not (uvwStateNum == 0) and baseUVW.rejecting[uvwStateNum]:

                                # Check if uvwStateNum is left along this transition -- then copying is necessary!
                                stayInUVWState = False
                                for uvwTransNo, (fromUVW, toUVW, label) in enumerate(uvwTrans):
                                    if (fromUVW == toUVW) and (toUVW == uvwStateNum):
                                        stayInUVWState = True
                                if stayInUVWState:
                                    posLivenessMonitoredValue += (1 << posLivenessMonitoredPos)
                                posLivenessMonitoredPos += 1

                        if posLivenessMonitoredValue > 0:
                            print("        livenessMonitoring(" + str(posLivenessMonitoredValue) + ");", file=outFile)

                    # In case we had a violation, log a violation
                    if toDFA in dfa.accepting:
                        # Log violation!
                        # Case 1: Safety violation -- here, we use the fact that state 0 is always
                        # the state rejecting everything in the UVW library
                        if dfa.states[toDFA][0]:
                            print("        logViolationExplanation(" + str(toDFA) + ",&(buf.b0p0)," + str(
                                bufferSizesInWords[0] * 4) + ");", file=outFile)
                        else:
                            print("        logViolationExplanation(" + str(toDFA) + ",&buf,sizeof(buf));", file=outFile)

                print("      }", file=outFile)
                print("      break;", file=outFile)
        print("    default:", file=outFile)
        for s in range(len(dfa.states)):
            if s in dfa.accepting:
                print("      /* DFA State " + str(s) + " has UVW states: " + " ".join(
                    [str(i) for i in range(len(baseUVW.stateNames)) if dfa.states[s][i]]) + " */", file=outFile)
        print("      break;", file=outFile)


    # Add decoding information for the buffers:
    print("/* Decoding information for the buffers:", file=outFile)
    print("   -------------------------------------\n", file=outFile)
    for i in range(0, len(baseUVW.stateNames)):
        print(" - UVW state " + str(i) + " with LTL subformula (Polish notation):", file=outFile)
        if bufferSizesInBits[i] == 0:
            print("    Initial state only", file=outFile)
        else:
            if (bufferSizesInBits[i] % 32) - nofBitsIncomingTransitions[i] - len(propositions) > 0:
                print("    Bits 0 to " + str((bufferSizesInBits[i] % 32) - nofBitsIncomingTransitions[i] - len(
                    propositions) - 1) + ": previous buffer", file=outFile)
            print("    Bits " + str(
                (bufferSizesInBits[i] % 32) - nofBitsIncomingTransitions[i] - len(propositions)) + " to " + str(
                (bufferSizesInBits[i] % 32) - nofBitsIncomingTransitions[i] - 1) + ": propositions", file=outFile)
            if nofBitsIncomingTransitions[i] > 0:
                print("    Bits " + str((bufferSizesInBits[i] % 32) - nofBitsIncomingTransitions[i]) + " to " + str(
                    (bufferSizesInBits[i] % 32) - 1) + ": incoming transition", file=outFile)
                for transitionIndex, (ls, ll) in enumerate(incomingTransitionsUVWExceptForSelfLoops[i]):
                    print("       -> Value " + str(transitionIndex) + " for transition from UVW state " + str(ls),
                          file=outFile)

    print("\n", file=outFile)
    print("UVW on which the monitor is based:\n", baseUVW, file=outFile)

    print("*/", file=outFile)






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
                                        if ((bufferSizesInBits[fromUVW]%32) < (bufferSizesInBits[toUVW]%32)):
                                            # Simple case: appending all to the same part
                                            wordIndex = bufferSizesInBits[toUVW]//32
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



def generateMonitor(inputFile,scriptbasePath,livenessMonitoring):
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



    # Obtain DFA from UVW
    dfa = determiniseUVWForMonitoring(baseUVW)
    
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
    monitorGenerationAlgorithm = "deterministic"

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

    
    if paretoCompiler is None:
        (dfa,baseUVW,propositions,livenessMonitoring) = generateMonitor(inputFile,scriptBasePath,livenessMonitoring)
        generateMonitorCode(dfa,baseUVW,propositions,livenessMonitoring,outputFile,monitorGenerationAlgorithm)
    else:
        (dfa,baseUVW,propositions,livenessMonitoring) = generateMonitor(inputFile,scriptBasePath,livenessMonitoring)
        paretoOptimize(baseUVW,propositions,livenessMonitoring,paretoCompiler,paretoLimit,monitorGenerationAlgorithm)
    
    
    print("Done. Exiting....",file=sys.stderr)
