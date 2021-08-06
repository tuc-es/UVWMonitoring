#!/usr/bin/env python3
#
# Enumerates an UVW representing simple chains that are all accepted by a given
# transition-based Buchi automaton in HOA format, as produced by SPOT's ltl2tgba tool.
#
# Example command to produce a transition-based generalized Buchi automaton
# ./ltl2tgba -Ht -f "[] <> a"
#
# Requires an extended version of automata-lib. Can be installed with:
#   pip3 uninstall automata-lib
#   pip3 install git+https://github.com/progirep/automata
#
import sys, pysat, pysat.solvers, copy
import automata.fa.nfa, automata.fa.dfa
import subprocess, io, re
import pareto_enumerator

# =================================================================
# Helper Functions
# =================================================================
from networkx.algorithms import shortest_paths


def NFAToHumanReadable(nfa: automata.fa.nfa.NFA):
    result = "NFA(\n"
    result += "  states = "+str(nfa.states)+",\n"
    result += "  input_symbols = "+str(nfa.input_symbols)+",\n"
    result += "  transitions = "+str(nfa.transitions)+",\n"
    result += "  initial_state = "+str(nfa.initial_state)+",\n"
    result += "  final_states = "+str(nfa.final_states)+"\n)"
    return result

def nonOverlappingUnion(setA,setB):
    '''Builds a union between two sets. Throws an assertion violation if there are elements that are in both sets'''
    res = setA.union(setB)
    assert len(res)==len(setA)+len(setB)
    return res


# =================================================================
# Class representing a transition-based generalized Buchi automaton
# =================================================================
def doesParsedFormulaAcceptPropositionAssignment(transitionLabel,character):
    if isinstance(transitionLabel,tuple):
        if transitionLabel[0]=="|":
            return doesParsedFormulaAcceptPropositionAssignment(transitionLabel[1],character) | doesParsedFormulaAcceptPropositionAssignment(transitionLabel[2],character)
        elif transitionLabel[0]=="&":
            return doesParsedFormulaAcceptPropositionAssignment(transitionLabel[1],character) & doesParsedFormulaAcceptPropositionAssignment(transitionLabel[2],character)
        elif transitionLabel[0]=="!":
            return not doesParsedFormulaAcceptPropositionAssignment(transitionLabel[1],character)
        else:
            assert False
    else:
        if transitionLabel=="t":
            return True
        bitNum = int(transitionLabel)
        return (character & (1<<bitNum))>0


class TGBA:
    def __init__(self):
        self.propositions = None
        self.states = []
        self.initialStates = []
        self.name = None
        self.nofBuchiConditions = None
        self.transitions = []
        self.transitionsPerCharacter = None # Filled by the "computeTransitionsPerCharacter" function

    def computeTransitionsPerCharacter(self):
        # noinspection PyUnusedLocal
        self.transitionsPerCharacter = [[] for a in self.states]
        for sourceState in range(0,len(self.states)):
            for character in range(0,1 << len(self.propositions)):
                theseTransitions = set([])
                for (transitionLabel, toState, acc) in self.transitions[sourceState]:
                    if doesParsedFormulaAcceptPropositionAssignment(transitionLabel,character):
                        theseTransitions.add((toState,frozenset(acc)))
                self.transitionsPerCharacter[sourceState].append(theseTransitions)


# =================================================================
# Parsing HOA
# =================================================================
def readToken(inputString, pos):
    while pos < len(inputString) and (inputString[pos] == " " or inputString[pos] == "\t"):
        pos += 1
        if pos >= len(inputString):
            return pos, None
    ps = pos
    if inputString[pos] in "01234567890":
        while inputString[pos] in "01234567890":
            pos += 1
            if pos >= len(inputString):
                return pos, inputString[ps:pos]
        return pos, inputString[ps:pos]
    if inputString[pos] in "!&|()][t":
        return pos + 1, inputString[pos]
    raise Exception("Illegal string to be parsed: ", inputString, pos)


def parseTransitionLabel(inputString, pos):
    if inputString[pos] != "[":
        raise Exception("Condition does not start with a '['")
    pos += 1
    tokens = []
    nextToken = None
    while nextToken != "]":
        (pos, nextToken) = readToken(inputString, pos)
        if nextToken != "]":
            tokens.append(nextToken)
        else:
            pos = pos - 1  # Wind back

    def parseDisjunction(tokens, pos):
        (rest, pos) = parseConjunction(tokens, pos)
        parts = [rest]
        while (pos < len(tokens)) and tokens[pos] == "|":
            (rest2, pos) = parseConjunction(tokens, pos + 1)
            parts.append(rest2)
        if len(parts)>1:
            return ("|", *parts), pos
        else:
            return rest, pos

    def parseConjunction(tokens, pos):
        (rest, pos) = parseNegation(tokens, pos)
        parts = [rest]
        while (pos < len(tokens)) and tokens[pos] == "&":
            (rest2, pos) = parseNegation(tokens, pos + 1)
            parts.append(rest2)
        if len(parts) > 1:
            return ("&", *parts), pos
        else:
            return rest, pos

    def parseNegation(tokens, pos):
        if tokens[pos] == "!":
            (rest2, pos) = parseConstant(tokens, pos + 1)
            return (("!", rest2), pos)
        else:
            return parseConstant(tokens, pos)

    def parseConstant(tokens, pos):
        if tokens[pos] == "(":
            (rest, pos) = parseDisjunction(tokens, pos + 1)
            if tokens[pos] != ")":
                raise Exception("Brace not properly closed.")
            return (rest, pos + 1)
        # Atom
        return (tokens[pos], pos + 1)

    (result, pos2) = parseDisjunction(tokens, 0)
    if pos2 != len(tokens):
        print("TRANSERROR",result,pos2,tokens)
        raise Exception("Not all tokens in conditions needed")
    if inputString[pos] != "]":
        raise Exception("Condition does not end with a ']' properly")
    return (result, pos + 1)


def readHOA(sourceStream):
    tgba = TGBA()
    nofStates = None

    # Read Header
    firstLine = sourceStream.readline().strip()
    assert firstLine.startswith("HOA: v1")

    # Read lines
    readingMode = 0  # 0=headers, 1=body, 2=ended
    currentState = None
    nextLines = list(sourceStream.readlines())
    for line in nextLines:
        line = line.strip()

        if readingMode == 0:

            # Header lines
            if line.startswith("States: "):
                if not nofStates is None:
                    raise Exception("Multiple numbers of states given.")
                nofStates = int(line[8:].strip())
            elif line.startswith("Start: "):
                startingState = int(line[7:].strip())
                tgba.initialStates.append(startingState)
            elif line.startswith("name: "):
                if not tgba.name is None:
                    raise Exception("Multiple Names given.")
                tgba.name = line[6:].strip()
            elif line.startswith("tool: "):
                pass  # We don't care about the tool.
            elif line.startswith("Alias: "):
                raise Exception("Error: HOA format support does not include aliases.")
            elif line.startswith("AP: "):
                if not tgba.propositions is None:
                    raise Exception("Error: Multiple sets of APs given.")
                restLine = line[4:]
                allAPs = []
                if restLine.find(" ") != -1:
                    partA = restLine[0:restLine.find(" ")]
                    partB = restLine[restLine.find(" "):].strip()
                    nofAPs = int(partA)
                    # Poor man's direct parser
                    current = None
                    escaped = False
                    for character in partB:
                        if escaped:
                            if current is None:
                                raise Exception("Can't escape outside of AP: '" + partB + "'")
                            current += character
                            escaped = False
                        elif character == "\\":
                            escaped = True
                        elif character in " \t":
                            if not current is None:
                                current += " "
                        elif character == "\"":
                            if current is None:
                                current = ""
                            else:
                                allAPs.append(current)
                                current = None
                        else:
                            if current is None:
                                raise Exception("Unquoted character in: '" + partB + "'")
                            current += character
                    if escaped:
                        raise Exception("Escaping not terminated")
                    if not current is None:
                        raise Exception("String not terminated")
                    if len(allAPs) != nofAPs:
                        raise Exception("Nof declared APs is illegal: '" + line + "'")
                tgba.propositions = allAPs
            elif line.startswith("Acceptance: "):
                assert tgba.nofBuchiConditions is None
                if line.strip()=="Acceptance: 0 t":
                    tgba.nofBuchiConditions = 0
                else:
                    parts = re.split('\ |\&', line)
                    # parts = line.split(" &")
                    print("PARTS:",parts)
                    nofAcceptanceElements = int(parts[1])
                    # Only supports TGBA!
                    for i in range(0, nofAcceptanceElements):
                        assert parts[2 + i] == "Inf(" + str(i) + ")"
                    tgba.nofBuchiConditions = nofAcceptanceElements
            elif line.startswith("acc-name:"):
                pass  # Ignored.
            elif line.startswith("properties:"):
                pass  # Ignored.
            elif line == "--BODY--":
                readingMode = 1
            else:
                raise Exception("Did not unterstand line: '" + line + "'")

        elif readingMode == 1:
            # Body
            if line.startswith("--END--"):
                readingMode = 2
            elif line.startswith("State: "):
                # Read a new state
                restLine = line[7:] + " "
                if restLine[0] == "[":
                    raise Exception("State Labels not supported.")
                assert restLine.find(" ") != -1
                currentState = int(restLine[0:restLine.find(" ")])
                stateName = restLine[restLine.find(" ") + 1:]
                while len(tgba.states) <= currentState:
                    tgba.states = tgba.states + [None]
                tgba.states[currentState] = stateName
                while len(tgba.transitions) <= currentState:
                    tgba.transitions = tgba.transitions + [[]]
            else:
                # Transition
                if line[0] != "[":
                    raise Exception("Every transition must be conditional")
                (transitionLabel, parsePos) = parseTransitionLabel(line, 0)
                # To where
                lineRest = line[parsePos + 1:] + " "
                toState = int(lineRest[0:lineRest.find(" ")])
                postPart = lineRest[lineRest.find(" ") + 1:].strip()
                if postPart == "":
                    # Acceptance Condition
                    acc = set([])
                else:
                    assert postPart[0] == "{"
                    assert postPart[-1] == "}"
                    postPart = postPart[1:len(postPart) - 1]
                    conditions = postPart.split(" ")
                    acc = set([int(a) for a in conditions])
                tgba.transitions[currentState].append((transitionLabel, toState, acc))

        elif readingMode == 2:
            # Beyond end. Ignoring rest
            pass

            # Read all lines. Done!
    return tgba


# =================================================================
# Running tests
# =================================================================
def runTests():
    # Test tokenization of the parser
    testStr = "   1 & 3 &  \t  4 & 5 |  7  "
    (pos, tok) = readToken(testStr, 0)
    assert tok == "1"
    (pos, tok) = readToken(testStr, pos)
    assert tok == "&"
    (pos, tok) = readToken(testStr, pos)
    assert tok == "3"
    (pos, tok) = readToken(testStr, pos)
    assert tok == "&"
    (pos, tok) = readToken(testStr, pos)
    assert tok == "4"
    (pos, tok) = readToken(testStr, pos)
    assert tok == "&"
    (pos, tok) = readToken(testStr, pos)
    assert tok == "5"
    (pos, tok) = readToken(testStr, pos)
    assert tok == "|"
    (pos, tok) = readToken(testStr, pos)
    assert tok == "7"
    (pos, tok) = readToken(testStr, pos)
    assert tok is None
    assert pos == len(testStr)

    # Test parsing some Boolean expressions
    testStr = "**[2 | ! 3]"
    (result, pos) = parseTransitionLabel(testStr, 2)
    assert pos == len(testStr)
    assert result == ("|", "2", ("!", "3"))

    testStr = "**[2 | ! 3 & 4]"
    (result, pos) = parseTransitionLabel(testStr, 2)
    assert pos == len(testStr)
    assert result == ("|", "2", ("&", ("!", "3"), "4"))

    testStr = "[2 & ! 3 | 4]X"
    (result, pos) = parseTransitionLabel(testStr, 0)
    assert pos == len(testStr) - 1
    assert result == ("|", ("&", "2", ("!", "3")), "4")

    testStr = "[(2 & ! 3 | 4)]X"
    (result, pos) = parseTransitionLabel(testStr, 0)
    assert pos == len(testStr) - 1
    assert result == ("|", ("&", "2", ("!", "3")), "4")

    testStr = "[((((((2 & ! 3)))) | 4))]X"
    (result, pos) = parseTransitionLabel(testStr, 0)
    assert pos == len(testStr) - 1
    assert result == ("|", ("&", "2", ("!", "3")), "4")

    # Parsing exceptions
    for testStr in ["[2", "] 3", "[(2 &]", "[(2 & 3]", "[2 & 3)]", "[! ! !]"]:
        try:
            (result, pos) = parseTransitionLabel(testStr, 0)
            print("Should have Failed: ", testStr)
            assert False  # Should have failed
        except Exception as e:
            if isinstance(e, AssertionError):
                raise e
            else:
                # All right then!
                pass

    print("Test have all passed.")


# =================================================================
# Chain enumeration for general Buchi automata
#
# Idea:
# - We want to find all shortest words witnessing a vioation. A word is
#   shortest if no subsequence of its letters is also a violation.
# - After these shortest words have been identified, they are completed
#   to chains. A Pareto front enumeration algorithm is used.
#
# =================================================================
def enumerateChains(tgba):

    # Search for Buchi automaton states rejecting everything
    rejectsAllStates = []

    for stateNum in range(len(tgba.states)):

        # Rejects everything?
        rejectsEverything = True
        for character in range(1 << len(tgba.propositions)):
            for rejCondition in range(tgba.nofBuchiConditions):
                foundThisOne = False
                for toState,acc in tgba.transitionsPerCharacter[stateNum][character]:
                    if rejCondition in acc and toState==stateNum:
                        foundThisOne = True
                rejectsEverything = rejectsEverything and foundThisOne

        if rejectsEverything:
            rejectsAllStates.append(stateNum)


    # Sanity check: We need to have exactly one Buchi state rejecting everything, as otherwise
    # the automaton is not minimized *or* has a universal safety hull.
    if len(rejectsAllStates)!=1:
        # Ok, no chains in this case
        return []
        # raise Exception("Error: To enumerate all chains, we need that there is exactly one state in the Buchi automaton that rejects all suffix words.")


    # Build a NFA for the set of words leading to the "rejectsAll" state.
    # Since NFAs can only have one initial state in the library used, we need to introduce
    # a helper state called "init"
    transitionsNFA1 = {}
    transitionsFromInit = {}
    for character in range(1 << len(tgba.propositions)):
        transitionsFromInit[str(character)] = set([])
    transitionsNFA1["init"] = transitionsFromInit
    for stateNum in range(len(tgba.states)):
        transThisState = {}
        for character in range(1 << len(tgba.propositions)):
            transThisState[str(character)] = set([])
            for toState, acc in tgba.transitionsPerCharacter[stateNum][character]:
                transThisState[str(character)].add("q"+str(toState))
                if stateNum in tgba.initialStates:
                    transitionsFromInit[str(character)].add("q"+str(toState))
        transitionsNFA1["q"+str(stateNum)] = transThisState

    # Build NFA accepting the words leading to the rejecting self-looping Buchi
    # automaton data
    nfa = automata.fa.nfa.NFA(
        states={'q'+str(i) for i in range(0,len(tgba.states))}.union({'init'}),
        input_symbols={str(i) for i in range(0,1 << len(tgba.propositions))},
        transitions=transitionsNFA1,
        initial_state='init',
        final_states={'q'+str(rejectsAllStates[0])}
    )

    # Subtract from the NFA those words that have a strict subsequence as accepting
    # for this, (1) build an NFA for this language, and then (2) combining it with the existing NFA.

    def buildNFAForStrictSubsequence():
        newStates = nonOverlappingUnion(nfa.states,{"cpy"+b for b in nfa.states})
        newTransitions = {**copy.deepcopy(nfa.transitions), **{"cpy" + a:{c : {"cpy" + d for d in e} for (c, e) in b.items()} for (a, b) in nfa.transitions.items()}}
        newFinalStates = {"cpy" + str(a) for a in nfa.final_states}

        # Obtain other transitions
        for startingState in nfa.states:
            for b in nfa.input_symbols:
                newTransitions[startingState][b].add("cpy"+startingState)

        return automata.fa.nfa.NFA(
            states=newStates,
            input_symbols = nfa.input_symbols,
            transitions = newTransitions,
            initial_state = nfa.initial_state,
            final_states = newFinalStates)

    nfa2 = buildNFAForStrictSubsequence()
    nfa2.remove_states_with_empty_language()
    nfa2.remove_unreachable_states()
    dfa_shorter = automata.fa.dfa.DFA.from_nfa(nfa2)
    dfa_shorter.minify()
    dfa_complement = dfa_shorter.complement()
    nfa3 = automata.fa.nfa.NFA.from_dfa(dfa_complement)
    shortestWordsNFA = nfa3.intersection(nfa)
    shortestWordsNFA.remove_unreachable_states()
    shortestWordsNFA.remove_states_with_empty_language()
    shortestWordsDFA = automata.fa.dfa.DFA.from_nfa(shortestWordsNFA)
    # nfa.show_diagram("/tmp/ofig.png")
    # shortestWordsNFA.show_diagram("/tmp/shortestWords.png")
    # nfa3.show_diagram("/tmp/nfa3.png")
    dfaRejectingSuffixes = automata.fa.dfa.DFA.from_nfa(nfa)

    # Check if there are infinitely many different words in the language
    def areThereAreInfinitelyManyWordsInTheNFA(givenNFA : automata.fa.nfa.NFA):
        for startingState in givenNFA.final_states:
            todo = set([startingState])
            done = set([])
            while len(todo)>0:
                currentState = todo.pop()
                for (c,p) in givenNFA.transitions[currentState].items():
                    for nstate in p:
                        if nstate==startingState:
                            return True
                        if not nstate in done:
                            todo.add(nstate)
                            done.add(nstate)
        return False

    assert not areThereAreInfinitelyManyWordsInTheNFA(shortestWordsNFA)

    # Ok, now compute the lengths of the chains in the nfa
    def computeLengthsOfTheChains():
        lengthsChains = set([])
        todo = set([(shortestWordsNFA.initial_state,0)])
        done = set(todo)

        if shortestWordsNFA.initial_state in shortestWordsNFA.final_states:
            lengthsChains.add(0)

        while len(todo)>0:
            (thisState,thisLen) = todo.pop()
            for (c, p) in shortestWordsNFA.transitions[thisState].items():
                for destState in p:
                    (ts,tl) = (destState,thisLen+1)
                    if not (ts,tl) in done:
                        todo.add((ts,tl))
                        done.add((ts,tl))
                    if ts in shortestWordsNFA.final_states:
                        lengthsChains.add(tl)
        return lengthsChains

    lengthsOfChains = computeLengthsOfTheChains()
    print("***LEN CHAINS: "+str(lengthsOfChains))


    # Enumerate chains using the Pareto Front enumeration library
    paretoFrontAll = []
    for chainLength in lengthsOfChains:

        # Oracle function
        # Format of the input: First the bits for the letters of the transitions between states,
        # then the self-loop labels
        # the last element is always the rejecting one. Here, it has a TRUE self-loop so that
        # it does not have to be modeled
        def oracle(point):

            # Check if all the words leading here are OK --> they must all be shortest words
            possibilities = [[shortestWordsDFA.initial_state]]
            for i in range(chainLength):
                nextPossibilities = set([])
                for s in possibilities[i]:
                    for j,a in enumerate(shortestWordsDFA.input_symbols):
                        if point[i*len(shortestWordsDFA.input_symbols)+j]==0:
                            nextPossibilities.add(shortestWordsDFA.transitions[s][a])
                possibilities.append(list(nextPossibilities))

            for a in possibilities[-1]:
                if not a in shortestWordsDFA.final_states:
                    return False

            # Check which states are reachable for the whole chain
            possibilities = [[dfaRejectingSuffixes.initial_state]]
            for i in range(chainLength):
                nextPossibilities = set([])

                # Self-looping
                todo = set(possibilities[i])
                done = set(possibilities[i])

                while len(todo)!=0:
                    nextOne = todo.pop()
                    for j,a in enumerate(dfaRejectingSuffixes.input_symbols):
                        if point[(chainLength+i)*len(dfaRejectingSuffixes.input_symbols)+j]==0:
                            succState = dfaRejectingSuffixes.transitions[nextOne][a]
                            if not succState in done:
                                todo.add(succState)
                                done.add(succState)

                # Transition to next element
                for s in done:
                    for j,a in enumerate(dfaRejectingSuffixes.input_symbols):
                        if point[i*len(dfaRejectingSuffixes.input_symbols)+j]==0:
                            nextPossibilities.add(dfaRejectingSuffixes.transitions[s][a])
                possibilities.append(list(nextPossibilities))

            for a in possibilities[-1]:
                if not a in dfaRejectingSuffixes.final_states:
                    return False

            # Chain OK? Fine!
            return True

        paretoFrontPart = pareto_enumerator.computeParetoFront(oracle,
            [(0, 2) for i in range(0,len(shortestWordsNFA.input_symbols)*2*chainLength)])

        paretoFrontAll.extend(paretoFrontPart)
        print("***FRONT: ",paretoFrontPart)

    # Remove Pareto Front elements that reject a strict subset of other elements
    # Iterate over the chains that may be dominated by another chain
    indexParetoFrontElementToPotentiallyRemove = 0
    while indexParetoFrontElementToPotentiallyRemove < len(paretoFrontAll):

        # The reference chain is the one to potentially remove
        chainReference = paretoFrontAll[indexParetoFrontElementToPotentiallyRemove]
        chainLengthReference = len(chainReference)//len(shortestWordsNFA.input_symbols)//2

        # Iterate over the potentially dominating chains - the "contestant" chain
        for chainNumContestant in range(0,len(paretoFrontAll)):
            if indexParetoFrontElementToPotentiallyRemove!=chainNumContestant:

                # If there is no possibilities for the ChainToPotentiallyRemove to be in the final state
                # while the chainToCheckAgainst is not, then remove the Pareto front element to potentially remove
                chainContestant = paretoFrontAll[chainNumContestant]
                chainLengthContestant = len(chainContestant) // len(shortestWordsNFA.input_symbols) // 2

                # Which combinations of states are reachable?
                todo = set([(0,frozenset([0]))])
                done = set([(0,frozenset([0]))])
                while len(todo)!=0:
                    (sRef,sContestant) = todo.pop()
                    for k, s in enumerate(dfaRejectingSuffixes.input_symbols):
                        # Compute next states of the contestant chain
                        contestantStates = set([])
                        for fromState in sContestant:
                            # Rejecting?
                            if fromState==chainContestant:
                                contestantStates.add(fromState)
                            else:
                                # Self-loop
                                # print("X",chainLengthContestant,fromState,k,file=sys.stderr)
                                if (fromState==chainLengthContestant) or (chainContestant[(chainLengthContestant + fromState) * len(dfaRejectingSuffixes.input_symbols) + k] == 0):
                                    contestantStates.add(fromState)
                                # Transition
                                if (fromState<chainLengthContestant) and (chainContestant[(fromState) * len(dfaRejectingSuffixes.input_symbols) + k] == 0):
                                    contestantStates.add(fromState + 1)

                        # Self-loop in the reference chain?
                        # print("X",chainLengthReference,sRef,k,file=sys.stderr)
                        if (sRef==chainLengthReference) or (chainReference[(chainLengthReference + sRef) * len(dfaRejectingSuffixes.input_symbols) + k] == 0):
                            nextElement = (sRef,frozenset(contestantStates))
                            if not nextElement in done:
                                todo.add(nextElement)
                                done.add(nextElement)
                        # Transition
                        if sRef < chainLengthReference:
                            if chainReference[(sRef) * len(dfaRejectingSuffixes.input_symbols) + k] == 0:
                                nextElement = (sRef+1,frozenset(contestantStates))
                                if not nextElement in done:
                                    todo.add(nextElement)
                                    done.add(nextElement)

                # Check if the reference chain is dominated by the contestant chain
                isDominated = True
                for (sRef,sContestant) in todo:
                    if sRef==chainLengthReference:
                        # Check that the contestant is in an initial state
                        if not chainLengthContestant in sContestant:
                            isDominated = False

                # Remove domainated chain
                if isDominated:
                    paretoFrontAll.pop(indexParetoFrontElementToPotentiallyRemove)
                    indexParetoFrontElementToPotentiallyRemove -= 1
                    break

        # Continue inspecting the elements
        indexParetoFrontElementToPotentiallyRemove += 1

    def chainListToDOT(outFile):
        # Visualize the ccmplete Pareto front
        print("digraph chains {",file=outFile)
        for i,chain in enumerate(paretoFrontAll):
            chainLength = len(chain) // len(dfaRejectingSuffixes.input_symbols) // 2
            for j in range(0,chainLength+1):
                print( "node"+str(i)+"x"+str(j)+";",file=outFile)
            for j in range(0,chainLength):
                for k,s in enumerate(dfaRejectingSuffixes.input_symbols):
                    if chain[(chainLength+j)*len(dfaRejectingSuffixes.input_symbols)+k]==0:
                        print("node" + str(i) + "x" + str(j) + " -> node" + str(i) + "x" + str(j)+" [label=\""+str(s)+"\"];",file=outFile)
                    if chain[(j) * len(dfaRejectingSuffixes.input_symbols) + k] == 0:
                        print("node" + str(i) + "x" + str(j) + " -> node" + str(i) + "x" + str(j+1)+" [label=\""+str(s)+"\"];",file=outFile)
        print("}",file=outFile)

    chainListToDOT(open("/tmp/chains.dot","w"))

# =====================================================
# Try to find a formula where there are infinitely many different shortest words
# =====================================================
def tryRandomFormulas():

    # Random formula generator
    def formulaGenerator():
        seedValue= 11
        while True:
            formulaProcess = subprocess.Popen("../../lib/spot/bin/randltl -n1000 --seed="+str(seedValue)+" a b c", shell=True,
                                              stdout=subprocess.PIPE)
            for line in formulaProcess.stdout.readlines():
                thisFormula = line.decode("utf-8").strip()
                yield thisFormula
            assert formulaProcess.wait()==0
            seedValue += 1

    nofFormulasSoFar = 0
    for thisFormula in formulaGenerator():
        nofFormulasSoFar += 1

        translationCmd = "../../lib/spot/bin/ltl2tgba -Ht -f \""+thisFormula+"\""
        translationProcess = subprocess.Popen(translationCmd ,shell=True,stdout=subprocess.PIPE)
        automaton = "".join([a.decode("utf-8") for a in translationProcess.stdout.readlines()])
        print("----\n"+automaton)
        buchiAutomaton = readHOA(io.StringIO(automaton))
        buchiAutomaton.computeTransitionsPerCharacter()

        res = enumerateChains(buchiAutomaton)
        if res is True:
            print("********************GOOD!*********************** "+str(nofFormulasSoFar))


# =================================================================
# Main functions
# =================================================================
if __name__ == "__main__":

    # Parse parametersjhgh
    doRunTests = False
    tryRandom = False
    inputStream = sys.stdin
    for arg in sys.argv[1:]:
        if arg == "--tests":
            doRunTests = True
        elif arg == "--random":
            tryRandom = True
        elif arg == "--help":
            print("""
chaineumerator.py - Enumerates an UVW representing simple chains that are all accepted by a given transition-based Buchi automaton in HOA format, as produced by SPOT's ltl2tgba tool.

Usage:
    /path/to/chainenumerator.py [inputFile] [options]

Parameters:
    inputFile - The input file. If none is given, the input automaton in Hanoi format is provided on
                the standard input.
    --help    - prints this help
    --tests   - runs the integrated test suite.
            """)
            sys.exit(0)
        elif not arg.startswith("-"):
            # InputFile
            if inputStream == sys.stdin:
                inputStream = open(arg)
            else:
                print("Error: Multiple input files given", file=sys.stderr)
                sys.exit(1)
        else:
            print("Error: Did not understand argument '" + arg + "'", file=sys.stderr)
            sys.exit(1)

    # Execute program
    if doRunTests:
        runTests()
    elif tryRandom:
        tryRandomFormulas()
    else:

        # Read input automaton
        buchiAutomaton = readHOA(inputStream)
        buchiAutomaton.computeTransitionsPerCharacter()

        print("Warning: Assuming that all states accepting all words have self-loops on all characters. SPOT ensures this if you let SPOT mininmize the automaton.")

        enumerateChains(buchiAutomaton)

        # Run console
        if False:
            # noinspection PyUnresolvedReferences
            import code, readline

            variables = globals().copy()
            variables.update(locals())
            shell = code.InteractiveConsole(variables)
            shell.interact()

    # Close input file/stream
    inputStream.close()
