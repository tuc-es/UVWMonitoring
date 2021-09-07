#!/usr/bin/env python3
#
# Enumerates an UVW representing simple chains that are all accepted by a given
# transition-based deterministic parity automaton in HOA format, as produced by SPOT's ltl2tgba tool.
#
# Example command to produce a transition-based deterministic parity automaton
# OLD: ./ltl2tgba -Ht -f "[] <> a"
# ./ltl2tgba -D --parity="max even" -f "F(~a R ~b)" > example1.hoa2

#
# Requires an extended version of automata-lib. Can be installed with:
#   pip3 uninstall automata-lib
#   pip3 install git+https://github.com/progirep/automata
#
import sys
import subprocess, random, time

# =================================================================
# Helper Functions
# =================================================================
basePathScript = sys.argv[0][0:sys.argv[0].rfind("/")]
randomSeed = int(time.time()*1000)
print("Random seed: ",randomSeed)
random.seed(randomSeed)

for iteration in range(0,100):

    sys.stdout.write(".")
    sys.stdout.flush()

    nofOpt = 5
    nofBits = 15
    optima = []
    for x in range(0,nofOpt):
        thisOne = []
        for y in range(0,nofBits):
            thisOne.append(random.random()>0.5)
        optima.append(tuple(thisOne))
        

    pathToEnumerator = basePathScript+"/../BooleanParetoEnumerator/enumerator"
    enumeratorProcess = subprocess.Popen(pathToEnumerator,stdout=subprocess.PIPE,stdin=subprocess.PIPE)
    with open("/tmp/enumeratorTest.txt","wb") as debugOutFile:

        # Init
        enumeratorProcess.stdin.write(("INIT "+str(nofBits)+"\n").encode("utf-8"))
        debugOutFile.write(("INIT "+str(nofBits)+"\n").encode("utf-8"))

        enumeratorProcess.stdin.write("START\n".encode("utf-8"))
        debugOutFile.write("START\n".encode("utf-8"))
        enumeratorProcess.stdin.flush()

        # Get Queries
        paretoFrontPart = []
        while True:
            nextLine = enumeratorProcess.stdout.readline().decode("utf-8").strip()
            if nextLine.startswith("SOLUTION"):
                break
            nextPoint = []
            for a in nextLine:
                if a=="1":
                    nextPoint.append(True)
                elif a=="0":
                    nextPoint.append(False)
                else:
                    raise Exception("Unknown pareto query: "+nextLine)
            debugOutFile.write(("> "+str(nextPoint)+"\n").encode("utf-8"))
            
            # Check this one
            foundCase = False
            for optimum in optima:
                thisOneOK = True
                for x in range(0,nofBits):
                    if not optimum[x] or nextPoint[x]:
                        pass
                    else:
                        thisOneOK = False
                if thisOneOK:
                    foundCase = True
            
            if foundCase:
                enumeratorProcess.stdin.write("Y\n".encode("utf-8"))
                debugOutFile.write("Y\n".encode("utf-8"))
            else:
                enumeratorProcess.stdin.write("N\n".encode("utf-8"))
                debugOutFile.write("N\n".encode("utf-8"))
            enumeratorProcess.stdin.flush()

        # Enumerate Pareto front parts
        paretoFrontPart = []
        while True:
            nextLine = enumeratorProcess.stdout.readline().decode("utf-8").strip()
            if nextLine.startswith("END"):
                break
            nextPoint = []
            for a in nextLine:
                if a == "1":
                    nextPoint.append(True)
                elif a == "0":
                    nextPoint.append(False)
                else:
                    raise Exception("Unknown pareto query: " + nextLine)
            paretoFrontPart.append(tuple(nextPoint))
            debugOutFile.write(("> SOL "+str(nextPoint)+"\n").encode("utf-8"))
            
        # Check that every optimum element has a smaller found element"):
        # print("Found:",paretoFrontPart)
        # print("Optima:",optima)
        for a in optima:
            foundThis = False
            for b in paretoFrontPart:
                thisOne = True
                for x in range(0,nofBits):
                    if not a[x] and b[x]:
                        thisOne = False
                foundThis = foundThis | thisOne
            assert foundThis


        # Chech that all found elements are contained in "optima"
        for optimum in paretoFrontPart:
            assert optimum in optima
