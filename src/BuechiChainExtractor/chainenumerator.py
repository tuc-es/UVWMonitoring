#!/usr/bin/env python3
#
# Enumerates an UVW representing simple chains that are all accepted by a given
# transition-based Buchi automaton in HOA format, as produced by SPOT's ltl2tgba tool.
#
# Example command to produce a transition-based generalized Buchi automaton
# ./ltl2tgba -Ht -f "[] <> a"
import os, sys
from pysat.formula import CNF

# =================================================================
# Class representing a transition-based generalized Buchi automaton
# =================================================================
class TGBA:
    def __init__(self):
        self.propositions = None
        self.states = []
        self.initialStates = []
        self.name = None
        self.nofBuchiConditions = None
        self.transitions = []



# =================================================================
# Parsing HOA
# =================================================================
def readToken(inputString,pos):
    while pos<len(inputString) and (inputString[pos]==" " or inputString[pos]=="\t"):
        pos += 1
        if pos>=len(inputString):
            return (pos,None)
    ps = pos
    if inputString[pos] in "01234567890":
        while inputString[pos] in "01234567890":
            pos += 1
            if pos>=len(inputString):
                return (pos,inputString[ps:pos])
        return (pos,inputString[ps:pos])
    if inputString[pos] in "!&|()][":
        return (pos+1,inputString[pos])
    raise Exception("Illegal string to be parsed: ",inputString,pos)

def parseTransitionLabel(inputString,pos):
    if inputString[pos] != "[":
        raise Exception("Condition does not start with a '['")
    pos+=1
    tokens = []
    nextToken = None
    while (nextToken!="]"):
        (pos,nextToken) = readToken(inputString,pos)
        if nextToken!="]":
            tokens.append(nextToken)
        else:
            pos = pos - 1 # Wind back

    def parseDisjunction(tokens,pos):
        (rest,pos) = parseConjunction(tokens,pos)
        if (pos<len(tokens)) and tokens[pos] == "|":
            (rest2,pos) = parseConjunction(tokens,pos+1)
            return (("|",rest,rest2),pos)
        else:
            return (rest,pos)
            
    def parseConjunction(tokens,pos):
        (rest,pos) = parseNegation(tokens,pos)
        if (pos<len(tokens)) and tokens[pos] == "&":
            (rest2,pos) = parseNegation(tokens,pos+1)
            return (("&",rest,rest2),pos)
        else:
            return (rest,pos)

    def parseNegation(tokens,pos):
        if tokens[pos]=="!":
            (rest2,pos) = parseConstant(tokens,pos+1)
            return (("!",rest2),pos)
        else:
            return parseConstant(tokens,pos)
            
    def parseConstant(tokens,pos):
        if tokens[pos]=="(":
            (rest,pos) = parseDisjunction(tokens,pos+1)
            if tokens[pos]!=")":
                raise Exception("Brace not properly closed.")
            return (rest,pos+1)
        # Atom
        return (tokens[pos],pos+1)
            
    (result,pos2) = parseDisjunction(tokens,0)
    if pos2!=len(tokens):
        raise Exception("Not all tokens in conditions needed")
    if inputString[pos] != "]":
        raise Exception("Condition does not end with a ']' properly")
    return (result,pos+1)

def readHOA(sourceStream):

    tgba = TGBA()
    nofStates = None

    # Read Header
    firstLine = sourceStream.readline().strip()
    assert firstLine.startswith("HOA: v1")
    
    # Read lines
    readingMode = 0    # 0=headers, 1=body, 2=ended
    currentState = None
    nextLines = list(sourceStream.readlines())
    for line in nextLines:
        line = line.strip()
        
        if readingMode==0:
            
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
                pass # We don't care about the tool.
            elif line.startswith("Alias: "):
                raise Exception("Error: HOA format support does not include aliases.")
            elif line.startswith("AP: "):
                if not tgba.propositions is None:
                    raise Exception("Error: Multiple sets of APs given.")
                restLine = line[4:]
                assert restLine.find(" ")!=-1
                partA = restLine[0:restLine.find(" ")]
                partB = restLine[restLine.find(" "):].strip()
                nofAPs = int(partA)
                # Poor man's direct parser
                current = None
                allAPs = []
                escaped = False
                for character in partB:
                    if escaped:
                        if current is None:
                            raise Exception("Can't escape outside of AP: '"+partB+"'")
                        current += character
                        escaped = False
                    elif character=="\\":
                        escaped = True
                    elif character in " \t":
                        if not current is None:
                            current += " "
                    elif character=="\"":
                        if current is None:
                            current = ""
                        else:
                            allAPs.append(current)
                            current = None
                    else:
                        if current is None:
                            raise Exception("Unquoted character in: '"+partB+"'")
                        current += character
                if escaped:
                    raise Exception("Escaping not terminated")
                if not current is None:
                    raise Exception("String not terminated")
                if len(allAPs)!=nofAPs:
                    raise Exception("Nof declared APs is illegal: '"+line+"'")
                tgba.propositions = allAPs
            elif line.startswith("Acceptance: "):
                assert tgba.nofBuchiConditions is None
                parts = line.split(" ")
                nofAcceptanceElements = int(parts[1])
                # Only supports TGBA!
                for i in range(0,nofAcceptanceElements):
                    assert parts[2+i]=="Inf("+str(i)+")"
                tgba.nofBuchiConditions = nofAcceptanceElements
            elif line.startswith("acc-name:"):
                pass #Ignored.
            elif line.startswith("properties:"):
                pass #Ignored.
            elif line == "--BODY--":
                readingMode = 1
            else:
                raise Exception("Did not unterstand line: '"+line+"'")
       
        elif readingMode==1:
            # Body
            if line.startswith("--END--"):
                readingMode = 2
            elif line.startswith("State: "):
                # Read a new state
                restLine = line[7:]+" "
                if restLine[0]=="[":
                    raise Exception("State Labels not supported.")
                assert restLine.find(" ")!=-1
                currentState = int(restLine[0:restLine.find(" ")])
                stateName = restLine[restLine.find(" ")+1:]
                while len(tgba.states)<=currentState:
                    tgba.states = tgba.states+[None]
                tgba.states[currentState] = stateName
                while len(tgba.transitions)<=currentState:
                    tgba.transitions = tgba.transitions+[[]]
            else:
                # Transition
                if (line[0]!="["):
                    raise Exception("Every transition must be conditional")
                (transitionLabel,parsePos) = parseTransitionLabel(line,0)
                # To where
                lineRest = line[parsePos+1:]+" "
                toState = lineRest[0:lineRest.find(" ")]
                postPart = lineRest[lineRest.find(" ")+1:].strip()
                if postPart=="":
                    # Acceptance Condition
                    acc = set([])
                else:
                    print("Acc:",postPart)
                    assert postPart[0]=="{"
                    assert postPart[-1]=="}"
                    postPart = postPart[1:len(postPart)-1]
                    conditions = postPart.split(",")
                    acc = set([int(a) for a in conditions])
                tgba.transitions[currentState].append((transitionLabel,acc))
            
        elif readingMode==2:
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
    (pos,tok) = readToken(testStr,0)
    assert tok=="1"
    (pos,tok) = readToken(testStr,pos)
    assert tok=="&"
    (pos,tok) = readToken(testStr,pos)
    assert tok=="3"
    (pos,tok) = readToken(testStr,pos)
    assert tok=="&"
    (pos,tok) = readToken(testStr,pos)
    assert tok=="4"
    (pos,tok) = readToken(testStr,pos)
    assert tok=="&"
    (pos,tok) = readToken(testStr,pos)
    assert tok=="5"
    (pos,tok) = readToken(testStr,pos)
    assert tok=="|"
    (pos,tok) = readToken(testStr,pos)
    assert tok=="7"
    (pos,tok) = readToken(testStr,pos)
    assert tok is None
    assert pos == len(testStr)
    
    # Test parsing some Boolean expressions
    testStr = "**[2 | ! 3]"
    (result,pos) = parseTransitionLabel(testStr,2)
    assert pos==len(testStr)
    assert result==("|","2",("!","3"))
    
    testStr = "**[2 | ! 3 & 4]"
    (result,pos) = parseTransitionLabel(testStr,2)
    assert pos==len(testStr)
    assert result==("|","2",("&",("!","3"),"4"))

    testStr = "[2 & ! 3 | 4]X"
    (result,pos) = parseTransitionLabel(testStr,0)
    assert pos==len(testStr)-1
    assert result==("|",("&","2",("!","3")),"4")
    
    testStr = "[(2 & ! 3 | 4)]X"
    (result,pos) = parseTransitionLabel(testStr,0)
    assert pos==len(testStr)-1
    assert result==("|",("&","2",("!","3")),"4")
    
    testStr = "[((((((2 & ! 3)))) | 4))]X"
    (result,pos) = parseTransitionLabel(testStr,0)
    assert pos==len(testStr)-1
    assert result==("|",("&","2",("!","3")),"4")
    
    # Parsing exceptions
    for testStr in ["[2","] 3","[(2 &]","[(2 & 3]","[2 & 3)]"]:
        try:
            (result,pos) = parseTransitionLabel(testStr,0)
            print("Should have Failed: ",testStr)
            assert False # Should have failed
        except Exception as e:
            if isinstance(e,AssertionError):
                raise e
            else:
                # All right then!
                pass
        
    
    
    
    
    print("Test have all passed.")

# =================================================================
# Main functions
# =================================================================
if __name__ == "__main__":

    # Parse parameters
    doRunTests = False
    inputStream = sys.stdin
    for arg in sys.argv[1:]:
        if arg=="--tests":
            doRunTests = True
        elif arg=="--help":
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
                print("Error: Multiple input files given",file=sys.stderr)
                sys.exit(1)
        else:
            print("Error: Did not understand argument '"+arg+"'",file=sys.stderr)
            sys.exit(1)
           
    # Execute program           
    if doRunTests:
        runTests()
    else:

        # Read input automaton
        buchiAutomaton = readHOA(inputStream)

        # Run console
        import readline # optional, will allow Up/Down/History in the console
        import code
        variables = globals().copy()
        variables.update(locals())
        shell = code.InteractiveConsole(variables)
        shell.interact()
        
        
        
    # Close input file/stream
    inputStream.close()
    
