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
import experiment_runner

runner = experiment_runner.Runner()

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
    chains)
    
    
    
    

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
    
    
# Experiment B0: No monitoring code
with open("../demos/TrafficLightsL010RB/Src/monitor.c","w") as outFile:
    outFile.write("#include <stdint.h>\nvoid monitorUpdate(uint32_t d) {}\n")
    
exp = runner.run("../demos/TrafficLightsL010RB","export PLATFORMIO_BUILD_FLAGS=\"-DNO_MONITORING\";run -t clean;pio run")
(flash,ram) = extractFlashAndMemUsageFromPlatformIORun(exp.output)
runner.log(\
    "Number of Flash Bytes No Monitoring Code Traffic Light",
    flash)
runner.log(\
    "Number of RAM Bytes No Monitoring Code Traffic Light",
    ram)    

# Experiment B1: Empty Monitor
exp = runner.run("../demos/TrafficLightsL010RB","pio run -t clean;pio run")
(flash,ram) = extractFlashAndMemUsageFromPlatformIORun(exp.output)
runner.log(\
    "Number of Flash Bytes Empty Monitor Traffic Light",
    flash)
runner.log(\
    "Number of RAM Bytes No Empty Monitor Traffic Light",
    ram)    

# Experiment B2: Plain monitor    
exp = runner.run("../src/monitorcompiler","./monitorcompiler.py ../../examples/specTrafficLightBigger.txt --nondeterministic --outFile ../../demos/TrafficLightsL010RB/Src/monitor.c")
runner.log(\
    "Computation Time Plain Monitor Compiler Traffic Light",
    exp.cpuTime,
    beautify_condition = lambda x: x<0.01,
    beautify_replacement = "$<$ 0.01 seconds",
    regular_formatter = lambda x: "%1.3f" % x)

exp = runner.run("../demos/TrafficLightsL010RB","pio run -t clean;pio run")
(flash,ram) = extractFlashAndMemUsageFromPlatformIORun(exp.output)
runner.log(\
    "Number of Flash Bytes Plain Monitor Traffic Light",
    flash)
runner.log(\
    "Number of RAM Bytes Plain Monitor Traffic Light",
    ram)    

# Experiment B3: Optimizing Monitors / Cases that work
for (nofLUTs,nofInputs) in [(7,8),(15,5),(11,6),(9,7)]:
    exp = runner.run("../src/monitorcompiler","./monitorcompiler.py ../../examples/specTrafficLightBigger.txt --aigBased --nofLUTs "+str(nofLUTs)+" --nofInputsPerLUT "+str(nofInputs)+" --outFile ../../demos/TrafficLightsL010RB/Src/monitor.c")
    runner.log(\
        "Computation Time Optimizing Monitor Compiler "+str(nofLUTs)+" LUTS " + str(nofInputs)+" Inputs Traffic Light",
        exp.cpuTime,
        beautify_condition = lambda x: x<0.01,
        beautify_replacement = "$<$ 0.01 seconds",
        regular_formatter = lambda x: "%1.3f" % x)

    exp = runner.run("../demos/TrafficLightsL010RB","pio run -t clean;pio run")
    (flash,ram) = extractFlashAndMemUsageFromPlatformIORun(exp.output)
    runner.log(\
        "Number of Flash Bytes Optimizing Monitor Compiler "+str(nofLUTs)+" LUTS " + str(nofInputs)+" Inputs Traffic Light",
        flash)
    runner.log(\
        "Number of RAM Bytes Optimizing Monitor Compiler "+str(nofLUTs)+" LUTS " + str(nofInputs)+" Inputs Traffic Light",
        ram)    


