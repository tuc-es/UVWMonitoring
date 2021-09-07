#!/usr/bin/env python3
# =================================================================
# Script for automatic computation time taking on a microcontroller
# =================================================================
import os, sys, subprocess, glob, shutil, serial
import experiment_runner, shutil
runner = experiment_runner.Runner()

NOF_TIMING_INFO_TO_WATCH = 10

computationTimes = {}
for monitorFile in glob.glob("monitors/*.c"):

    if monitorFile=="monitors/plain.c":
        nofLUTs = 0 # Plain
        nofInputsPerLUT = 0 # Plain
    else:
        # Decode file name
        assert monitorFile.startswith("monitors/")
        assert monitorFile.endswith(".c")
        coreFileName = monitorFile[9:]
        coreFileName = coreFileName[0:-2]
        print(coreFileName)
        coreFileNameParts = coreFileName.split("_")
        nofLUTs = int(coreFileNameParts[0])
        nofInputsPerLUT = int(coreFileNameParts[1])
        assert coreFileNameParts[2].startswith("copy")
    
    # Perform build process
    shutil.copy(monitorFile,"../demos/TrafficLightsL010RB/Src/monitor.c")
    exp = runner.run("../demos/TrafficLightsL010RB","export PLATFORMIO_BUILD_FLAGS=\"\";pio run -t clean;pio run -t upload")
    
    # Serial I/O
    conn = serial.Serial(port='/dev/ttyACM0', baudrate=9600)
    conn.timeout = 0
    conn.read(1000000000)
    conn.timeout = None
    while True:
        line = conn.readline().decode("utf-8")
        print(line)
        if line.startswith("TIMINFO: "+str(NOF_TIMING_INFO_TO_WATCH)+" "):
            line = line.strip().split(" ")
            cpuCyclesOverall = int(line[2])
            cpuCyclesMonitor = int(line[3])
            break
    conn.close()
    
    # Ok, got data!
    print("Timing info: ",nofLUTs,nofInputsPerLUT,cpuCyclesOverall,cpuCyclesMonitor)
    
    if not (nofLUTs,nofInputsPerLUT) in computationTimes:
        computationTimes[(nofLUTs,nofInputsPerLUT)] = []
    
    computationTimes[(nofLUTs,nofInputsPerLUT)].append((cpuCyclesOverall,cpuCyclesMonitor))
    

# Aggregate information
for (nofLUTs,nofInputsPerLUT),data in computationTimes.items():
    
    allCyclesMonitor = [b for (a,b) in data]
    if nofLUTs==0:
        filename = "MonitorExecutionTime Plain Traffic Light"
    else:
        filename = "MonitorExecutionTime "+str(nofLUTs)+" LUTS " + str(nofInputsPerLUT)+" Inputs Traffic Light"
    runner.log(filename,runner.formatMeanStdDev(allCyclesMonitor),
    )

    percentageMonitor = [b*100/a for (a,b) in data]
    if nofLUTs==0:
        filename = "MonitorExecutionTimePercentage Plain Traffic Light"
    else:
        filename = "MonitorExecutionTimePercentage "+str(nofLUTs)+" LUTS " + str(nofInputsPerLUT)+" Inputs Traffic Light"
    runner.log(filename,runner.formatMeanStdDev(percentageMonitor,"%1.6f\,\\%% $\pm$ %1.6f\,\\%%"),
    )
    
