#===============================================================
# ExperimentRunner
# 
# Functions for running experiments using a self-explatory
# experiment logbook.
#===============================================================
import subprocess, os
import selectors, sys, psutil, time, resource

# Source: https://stackoverflow.com/questions/26475636/measure-elapsed-time-amount-of-memory-and-cpu-used-by-the-extern-program

class Experiment:
    def __init__(self):
        self.output = []
        self.errors = []
        self.cpuTime = 0.0
        self.wallTime = 0.0

    def extract_from_stdout(self,starting_line=None,starting_fn=None,ending_line=None,ending_fn=None):
        returnLines = []
        active = (starting_line is None) and (starting_fn is None)
        for line in self.output:
            if ((not starting_line is None) and line.rstrip("\n")==starting_line) or ((not starting_fn is None) and starting_fn(line)):
                if active:
                    raise Exception("Extraction failed: Activated twice.")
                else:
                    active = True
            elif ((not ending_line is None) and line.rstrip("\n")==ending_line) or ((not ending_fn is None) and ending_fn(line)):
                if active:
                    active = False
                else:
                    raise Exception("Extraction failed: Double deactive")
            else:
                if active:
                    returnLines.append(line)
        # Last element empty? Then that's a spurious empty line. Remove it!
        if active and len(returnLines)>0 and returnLines[-1]=="":
            return returnLines[0:len(returnLines)-1]
        return returnLines
    


class Runner:
    
    def __init__(self):
        self.overallCPUTime = 0.0
        self.filesWritten = []
        self.resultsSubPath = "results/"
                
    def expect_line_in_file(self,outputFile,linePrefix,lineSuffix):
        duplicate = False
        for line in open(outputFile,"r").readlines():
            if line.startswith(linePrefix):
                if duplicate:
                    raise Exception("Error: multiple lines with the prefix.")
                if line[len(linePrefix):].strip()!=lineSuffix:
                    raise Exception("Error: expectation does not hold.")
                else:
                    duplicate = True
    
    def log(self,loggingID,loggedValue,beautify_condition = lambda x: False, beautify_replacement = None, regular_formatter = lambda x:x):
        if beautify_condition(loggedValue):
            loggedValue = beautify_replacement
        loggedValue = regular_formatter(loggedValue)
        loggedValuePrinted = str(loggedValue).replace("\n"," / ")
        if len(loggedValuePrinted)>30:
            loggedValuePrinted = loggedValuePrinted[0:27]+"..."
        print(loggingID+": "+loggedValuePrinted)
        for character in loggingID:
            if not character in "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_- ":
                raise Exception("Error: Logging ID does not lend itself to Camel Case File naming.")
            loggingID = "".join([a for a in loggingID if not a==" "])
        loggingID = self.resultsSubPath+loggingID+".txt"
        if loggingID in self.filesWritten:
            raise Exception("Error: Duplicate file writing to output file: "+loggingID)
        self.filesWritten.append(loggingID)
        with open(loggingID,"w") as outFile:
            outFile.write(str(loggedValue))

    def run(self, directory = None,commandLine=None):
        # Check if environment is sane
        if directory is None:
            directory = os.getcwd()
        directory = os.path.normpath(directory)
        for character in directory:
            if not character in "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ/_-.":
                raise Exception("Error: The path '"+directory+"' contains characters that can cause problems with experiments. Please avoid spaces in particular.")
        
        experiment = Experiment()       
        oldrusage = resource.getrusage(resource.RUSAGE_CHILDREN)
        startTime = time.time()

        with subprocess.Popen(commandLine,shell=True,cwd=directory,encoding="utf-8",stdout=subprocess.PIPE,\
               stderr=subprocess.PIPE,stdin=subprocess.DEVNULL) as experimentProcess:

            (allout,allerr) = experimentProcess.communicate() 
            experiment.output = allout.split("\n")
            experiment.errors = allerr.split("\n")

            returnValue = experimentProcess.wait()
            rusage = resource.getrusage(resource.RUSAGE_CHILDREN)
            experiment.cpuTime = (rusage.ru_utime-oldrusage.ru_utime)+(rusage.ru_stime-oldrusage.ru_stime)
            if returnValue!=0:
                raise Exception("Execution failed. with error level "+str(returnValue)+". Stderr output: "+"\n".join(experiment.errors))
            endTime = time.time()
            experiment.wallTime = endTime-startTime
            self.overallCPUTime += experiment.cpuTime
            return experiment

