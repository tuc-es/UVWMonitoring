#!/usr/bin/env python3
# ===================================================================
# Running this python file will run all experiments reported on
# in the paper and generates the experiment results as TeX files to
# be included in the paper.
#
# All commands are given explicitely and all "beautifications" of
# the result representation are given here.
# A beautification is a scientifically acceptable replacement of
# a result and can be inspected here for appropriateness. All 
# beautifications are conditional on them being allowed - they should
# never be unconditional. As an example for a beautification, com-
# putation times <0.1 seconds can be replaced by the string "<0.1 
# seconds".
# ===================================================================
import experiment_runner, shutil

runner = experiment_runner.Runner()

NOF_REPETITIONS = 2

# ===================================================================
# Experiment 1: Extracting all simple chains of a simple LTL property
# ===================================================================
# 1a: Running the translation to a parity automaton
exp = runner.run("../src/ChainExtractor","../../lib/spot/bin/ltl2tgba -D --parity=\"max even\" -f \"~G((a | X~b) W (c & X c))\" > paperExampleSimpleFullLTLProperty.hoa")
runner.log(\
    "Computation Time LTL2TGBA Simple Full LTL Property",
    exp.cpuTime,
    beautify_condition = lambda x: x<0.01,
    beautify_replacement = "$<$ 0.01 seconds",
    regular_formatter = lambda x: "%1.3f" % x)

# 1b: Expected Number of states is 4
runner.expect_line_in_file("../src/ChainExtractor/paperExampleTrafficLight.hoa","States:","4")
runner.log(\
    "Number of States Parity Automaton Simple Full LTL Property",
    4)

# 1c: Translate to chains
exp = runner.run("../src/ChainExtractor","./chainenumerator.py paperExampleSimpleFullLTLProperty.hoa")
runner.log(\
    "Computation Time Chain Extractor Simple Full LTL Property",
    exp.cpuTime,
    beautify_condition = lambda x: x<0.01,
    beautify_replacement = "$<$ 0.01 seconds",
    regular_formatter = lambda x: "%1.3f" % x)
chains = exp.extract_from_stdout(starting_fn=lambda x:x.startswith("*** Nof final chains: "))

runner.log(\
    "All Chains Simple Full LTL Property",
    "\n".join(["\\begin{verbatim}"]+chains+["\\end{verbatim}"]))

runner.log(\
    "All Chains Simple Full LTL Property Formatted",
    chains,
    beautify_condition = lambda x: x==['~true R ((~a&~c) -> X (~((~a&~c)|b) R (b -> X (false))))', '~true R (~a -> X (~(~a|(~c&b)) R ((~c&b) -> X (false))))'],
    beautify_replacement = """\\begin{tikzpicture}
\\node[draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q0) at (-1,0) {$q_2$};

\\node[draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q1) at (1,0) {$q_1$};

\\node[accepting,draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q2) at (3,0) {$q_0$};

% Initial
\\draw[fill=black] (-1.75,0.4) circle (0.06cm);
\\draw[thick,->] (-1.75,0.4) -- (q0);

\\draw[thick] (q0) edge[loop above] node[above] {$\\TRUE$} (q0);

% \\draw[thick] (q1) edge[loop above] node[above] {$a \wedge \\neg b$} (q1);

\\draw[thick] (q2) edge[loop above] node[above] {$\\TRUE$} (q2);

\\draw[thick,->] (q0) edge node[above] {$\\neg a$} (q1);
\\draw[thick,->] (q1) edge node[above] {$\\neg b \wedge \\neg c$} (q2);
\\end{tikzpicture}""")


# ==========================================================================
# Experiment 2: Extracting all simple chains of the property from full LTL
# used for the case study
# ==========================================================================
# 1a: Running the translation to a parity automaton
exp = runner.run("../src/ChainExtractor","../../lib/spot/bin/ltl2tgba -D --parity=\"max even\" -f \"~(~m W ((a1 & ~a2 & X(~a1 & a2) )))\" > paperExampleTrafficLight.hoa")
runner.log(\
    "Computation Time Chain LTL2TGBA Full LTL Property From Case Study",
    exp.cpuTime,
    beautify_condition = lambda x: x<0.01,
    beautify_replacement = "$<$ 0.01 seconds",
    regular_formatter = lambda x: "%1.3f" % x)

# 1b: Expected Number of states is 4
runner.expect_line_in_file("../src/ChainExtractor/paperExampleTrafficLight.hoa","States:","4")

runner.log(\
    "Number of States Parity Automaton Full LTL Property From Case Study",
    4)
    
# 1c: Translate to chains
exp = runner.run("../src/ChainExtractor","./chainenumerator.py paperExampleTrafficLight.hoa")

runner.log(\
    "Computation Time Chain Extractor Simple Full LTL Property From Traffic Light Case Study",
    exp.cpuTime,
    beautify_condition = lambda x: x<0.01,
    beautify_replacement = "$<$ 0.01 seconds",
    regular_formatter = lambda x: "%1.3f" % x)

chains = exp.extract_from_stdout(starting_fn=lambda x:x.startswith("*** Nof final chains: "))

runner.log(\
    "All Chains Full LTL Property From Case Study",
    "\n".join(["\\begin{verbatim}"]+chains+["\\end{verbatim}"]))

runner.log(\
    "All Chains Full LTL Property From Case Study Formatted",
    chains,
    beautify_condition = lambda x: x==['~(~a1|a2) R (((~a1&m)|(a2&m)) -> X (false))', '~(~a1|a2) R ((a1&~a2&m) -> X (~(~a2|a1) R (((~a2&~m)|(a1&~m)|(a1&~a2)) -> X (false))))', '~(~a2|a1) R (((~a1&~a2&m)|(a1&a2&m)) -> X (false))', '~(~a2|a1) R ((a1&~a2&m) -> X (~(~a2|a1) R (((~a2&~m)|(a1&~m)|(a1&~a2)) -> X (false))))'],
    beautify_replacement = """\\begin{tikzpicture}
\\node[draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q0) at (-1,0) {$q_1$};

\\node[accepting,draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q2) at (2,0) {$q_0$};

% Initial
\\draw[fill=black] (-1.75,0.4) circle (0.06cm);
\\draw[thick,->] (-1.75,0.4) -- (q0);
\\draw[thick] (q0) edge[loop above] node[above] {$\\neg a_1 \\vee a_2$} (q0);

% \\\\draw[thick] (q1) edge[loop above] node[above] {$a \\wedge \\\\neg b$} (q1);

\\draw[thick] (q2) edge[loop above] node[above] {$\\TRUE$} (q2);

\\draw[thick,->] (q0) edge node[above] {$m \\wedge (\\neg a_1 \\vee a_2)$} (q2);


% Chain three

\\node[draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q0) at (5,0) {$q_2$};

\\node[accepting,draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q2) at (8,0) {$q_0$};

\\draw[fill=black] (4.25,0.4) circle (0.06cm);
\\draw[thick,->] (4.25,0.4) -- (q0);

\\draw[thick] (q0) edge[loop above] node[above] {$\\neg a_2 \\vee a_1$} (q0);
\\draw[thick] (q2) edge[loop above] node[above] {$\\TRUE$} (q2);

\\draw[thick,->] (q0) edge node[above] {$m \\wedge (a_1 \\equiv a_2)$} (q2);


% Chain two
\\node[draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q0) at (-1,-2) {$q_3$};

\\node[draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q1) at (2,-2) {$q_4$};

\\node[accepting,draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q2) at (7,-2) {$q_0$};



\\draw[thick,->] (q0) edge[loop above] node[above] {$\\neg a_1 \\vee a_2$} (q0);

\\draw[thick,->] (q1) edge[loop above] node[above] {$\\neg a_2 \\vee a_1$} (q1);

\\draw[thick,->] (q2) edge[loop above] node[above] {$\\TRUE$} (q2);

\\draw[thick,->] (q0) edge node[above] {$a_1 \\wedge \\neg a_2 \\wedge m$} (q1);

\\draw[thick,->] (q1) edge node[above] {$(\\neg m \\wedge (\\neg a_2 \\vee a_1)) \\vee (a_1 \\wedge \\neg a_2)$} (q2);

\\draw[fill=black] (-1.75,-1.6) circle (0.06cm);
\\draw[thick,->] (-1.75,-1.6) -- (q0);



% Chain four
\\node[draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q0) at (-1,-4) {$q_5$};

\\node[draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q1) at (2,-4) {$q_6$};

\\node[accepting,draw,state,inner sep=0pt,minimum size=0.7cm,thick] (q2) at (7,-4) {$q_0$};



\\draw[thick,->] (q0) edge[loop above] node[above] {$\\neg a_2 \\vee a_1$} (q0);

\\draw[thick,->] (q1) edge[loop above] node[above] {$\\neg a_2 \\vee a_1$} (q1);

\\draw[thick,->] (q2) edge[loop above] node[above] {$\\TRUE$} (q2);

\\draw[thick,->] (q0) edge node[above] {$a_1 \\wedge \\neg a_2 \\wedge m$} (q1);

\\draw[thick,->] (q1) edge node[above] {$(\\neg m \\wedge (\\neg a_2 \\vee a_1)) \\vee (a_1 \\wedge \\neg a_2)$} (q2);

\\draw[fill=black] (-1.75,-3.6) circle (0.06cm);
\\draw[thick,->] (-1.75,-3.6) -- (q0);


\\end{tikzpicture}
""")

# ===================================================================
# Experiment C: Monitor code compilation
# ===================================================================
cpuTimes = []
for repetition in range(NOF_REPETITIONS):
    exp = runner.run(".","../lib/kissat/build/kissat aigbased_8_7.cnf; test $? -eq 20")
    cpuTimes.append(exp.cpuTime)
runner.log(\
    "Computation Times Kissat AIG Based 8 7",runner.formatMeanStdDev(cpuTimes))


# ===================================================================
# Experiment B: Monitor code compilation
# ===================================================================
# --> Helper function forextracting performance
def extractFlashAndMemUsageFromPlatformIORun(output):
    flash = None
    ram = None
    for line in output:
        if line.startswith("RAM:  "):
            parts = line.split(" ")
            assert ram is None
            ram = int(parts[parts.index("(used")+1])
        elif line.startswith("Flash: "):
            parts = line.split(" ")
            assert flash is None
            flash = int(parts[parts.index("(used")+1])
    return (flash,ram)

# Experiment B-1: Lines of Code main.c
exp = runner.run(".","cloc ../demos/TrafficLightsL010RB/Src/main.c")
for a in exp.output:
    if a.startswith("C "):
        codeLines = int(a.split(" ")[-1])
runner.log(\
    "LOC Traffic Light Main File",
    codeLines)
del codeLines
exp = runner.run(".","cp ../demos/TrafficLightsL010RB/Src/mainOnlySTM32CubeCode.old /tmp/main.c; cloc /tmp/main.c")
for a in exp.output:
    if a.startswith("C "):
        codeLines = int(a.split(" ")[-1])
runner.log(\
    "LOC STM32CUBE Code Traffic Light Main File",
    codeLines)
    
# Experiment B0: No monitoring code

with open("../demos/TrafficLightsL010RB/Src/monitor.c","w") as outFile:
    outFile.write("""#include <stdint.h>\nvoid monitorUpdate(uint32_t d) {
    if (d==0xFFFFFFFF) logViolationExplanation(0,0,0);
    }\n""")

     
with open("../demos/TrafficLightsL010RB/Src/monitor.c","w") as outFile:
    outFile.write("""#include <stdint.h>\nvoid monitorUpdate(uint32_t d) {
    if (d==0xFFFFFFFF) logViolationExplanation(0,0,0);
    }\n""")
    
exp = runner.run("../demos/TrafficLightsL010RB","export PLATFORMIO_BUILD_FLAGS=\"-DNO_MONITORING\";run -t clean;pio run")
(flash,ram) = extractFlashAndMemUsageFromPlatformIORun(exp.output)
runner.log(\
    "Number of Flash Bytes No Monitoring Code Traffic Light",
    flash)
runner.log(\
    "Number of RAM Bytes No Monitoring Code Traffic Light",
    ram)    

# Experiment B1: Empty Monitor
exp = runner.run("../demos/TrafficLightsL010RB","export PLATFORMIO_BUILD_FLAGS=\"\";pio run -t clean;pio run")
(flash,ram) = extractFlashAndMemUsageFromPlatformIORun(exp.output)
runner.log(\
    "Number of Flash Bytes Empty Monitor Traffic Light",
    flash)
runner.log(\
    "Number of RAM Bytes Empty Monitor Traffic Light",
    ram)    

# Experiment B2: Plain monitor    
exp = runner.run("../src/monitorcompiler","./monitorcompiler.py ../../examples/specTrafficLightBigger.txt --nondeterministic --outFile ../../demos/TrafficLightsL010RB/Src/monitor.c")
runner.log(\
    "Computation Time Plain Monitor Compiler Traffic Light",
    exp.cpuTime,
    beautify_condition = lambda x: x<0.01,
    beautify_replacement = "$<$ 0.01 seconds",
    regular_formatter = lambda x: "%1.3f" % x)

exp = runner.run("../demos/TrafficLightsL010RB","export PLATFORMIO_BUILD_FLAGS=\"\";pio run -t clean;pio run")
(flash,ram) = extractFlashAndMemUsageFromPlatformIORun(exp.output)
runner.log(\
    "Number of Flash Bytes Plain Monitor Traffic Light",
    flash)
runner.log(\
    "Number of RAM Bytes Plain Monitor Traffic Light",
    ram)    

# Experiment B3: Optimizing Monitors / Cases that work
for repetition in range(NOF_REPETITIONS):
    flashSizes = []
    times = []
    for (nofLUTs,nofInputs) in [(7,8),(15,5),(11,6),(9,7)]:
        exp = runner.run("../src/monitorcompiler","./monitorcompiler.py ../../examples/specTrafficLightBigger.txt --aigBased --nofLUTs "+str(nofLUTs)+" --nofInputsPerLUT "+str(nofInputs)+" --outFile ../../demos/TrafficLightsL010RB/Src/monitor.c")
    
        exp = runner.run("../demos/TrafficLightsL010RB","export PLATFORMIO_BUILD_FLAGS=\"\";pio run -t clean;pio run")
        (flash,ram) = extractFlashAndMemUsageFromPlatformIORun(exp.output)
        
        shutil.copy("../demos/TrafficLightsL010RB/Src/monitor.c","monitors/"+str(nofLUTs)+"_"+str(nofInputs)+"_copy"+str(repetition)+".c")

        runner.log(\
            "Number of RAM Bytes Optimizing Monitor Compiler "+str(nofLUTs)+" LUTS " + str(nofInputs)+" Inputs Traffic Light",
            ram)    

        flashSizes.append(flash)
        times.append(exp.cpuTime)
            

    runner.log(\
        "Computation Time Optimizing Monitor Compiler "+str(nofLUTs)+" LUTS " + str(nofInputs)+" Inputs Traffic Light",
        runner.formatMeanStdDev(times),
        )

    runner.log(\
        "Number of Flash Bytes Optimizing Monitor Compiler "+str(nofLUTs)+" LUTS " + str(nofInputs)+" Inputs Traffic Light",
        runner.formatMeanStdDev(flashSizes,formatString = "%04.2f $\pm$ %04.2f"))


