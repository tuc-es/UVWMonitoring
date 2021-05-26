#!/usr/bin/env python3
# Example compiler-invocation of and binary size taking script
# Params: (1) C input file
#
# WARNING: REALLY NOT CODE-INJECTION SAVE...LIKE NOT AT ALL....
import os, sys, subprocess

print("PARAMS:",sys.argv,file=sys.stderr)

if len(sys.argv)<2:
    print("Error: No input C file given!",file=sys.stderr)
    sys.exit(1)


# Get script location / Hacky way
scriptLocation = sys.argv[0]
while scriptLocation[-1]!="/":
    scriptLocation = scriptLocation[0:len(scriptLocation)-1]
if " " in scriptLocation:
    print("Error: No spaces in folder names allowed here. This is just an example compiler script, no proper tool.",file=sys.stderr)
    sys.exit(1)


# Outfile file name - yes, hacky way.
outFile = "/tmp/testOutput"+str(os.getpid())+".o"    
    
cmdCompile = "~/.platformio/packages/toolchain-gccarmnoneeabi/bin/arm-none-eabi-gcc -o "+outFile+" -c -O2 -ffunction-sections -fdata-sections -Wall -mthumb -mcpu=cortex-m0plus -nostdlib -DPLATFORMIO=50003 -DSTM32L010xB -DUSE_HAL_DRIVER -DF_CPU=32000000L -I~/.platformio/packages/framework-stm32cube/l0/Drivers/CMSIS/Include -I~/.platformio/packages/framework-stm32cube/l0/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I~/.platformio/packages/framework-stm32cube/l0/Drivers/STM32L0xx_HAL_Driver/Inc -I"+scriptLocation+" -I~/.platformio/packages/framework-stm32cube/l0/Drivers/BSP/Components/Common "+sys.argv[1]
assert os.system(cmdCompile)==0


# Ok, run "size" then
checkProc = subprocess.Popen("size "+outFile,shell=True,stdout=subprocess.PIPE)
assert checkProc.wait()==0
allInput = [a.decode("utf-8").strip() for a in checkProc.stdout.readlines()]
assert allInput[0].startswith("text")
numbers = allInput[1].split(" ")
print(numbers[0])

# Clean up, at least a bit.
os.unlink(outFile)
