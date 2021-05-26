# Runtime Monitoring using Universal Very-Weak Automata (UVW)

This repository contains a compiler reading specifications in the linear temporal logic (LTL) fragment defined in the paper "A Fragment of Linear Temporal Logic for Universal Very Weak Automata" (ATVA 2018 conference) and outputting runtime monitor code for the specification to be executed on a 32-bit microcontroller. The monitor code also keeps track of violation information explanation whenever a violation occurs.

The code in this repository includes a library for universal very weak automata already used in the repositories [here](https://github.com/tuc-es/guisynth) and [here](https://github.com/tuc-es/unite). It also includes a Pareto Front enumeration library available [here](https://github.com/progirep/ParetoFrontEnumerationAlgorithm).

## Installation and Preparation

The code in this repository is meant to be run on Linux, and has been tested under Ubuntu Linux 20.04. It is likely to work on other Linux distributions or distribution version as well, though. Whether the code compiles well is also tested using the Github Actions CI system:

![Current Build Status](https://github.com/tuc-es/UVWMonitoring/actions/workflows/build.yml/badge.svg)

The code depends on the [SPOT model checking library](https://gitlab.lrde.epita.fr/spot/). To install the prerequisites for running spot, the following `apt-get` command can be used (on Ubuntu Linux):
    
    sudo apt-get install latexmk texlive-latex-extra texlive-fonts-extra texlive-science pdf2svg
    
Furthermore, to compile an LTL parser in C++, the `qmake` utility must be installed. If you develop using the QT library, this should work out of the box. Otherwise, you can install `qmake` as follows:

    sudo apt-get install qt5-qmake qt5-default
    
Afterwards, the spot library can be obtained an installed as follows:

    cd lib; git clone https://gitlab.lrde.epita.fr/spot/spot.git; cd spot; git checkout edfcd5b0d8f3862c7eebb3adbd035ba84df7d753; autoreconf -i; ./configure --disable-devel; make; cd ../..

The LTL parser is then compiled with the following commands:

    cd src/ltltopolish; qmake Tool.pro; make; cd ../..

This repository also contains Python 3 code. The package `dd` needs to be installed (e.g., with `pip3 install dd`) to the use tool. 

## Running the tool

In the `examples` folder, there are a couple in example input specification files that can be used. To compile, for example, the monitor for a traffic light controller, the following command can be run from the main folder of the project:

    python3 src/monitorcompiler/monitorcompiler.py examples/specTrafficLight.txt --liveness --outFile demos/TrafficLightsL010RB/Src/monitor.c
    
Leaving out `--liveness` will make the code shorter by not performing monitoring for liveness properties. If no `--outFile` is given, the resulting code will be written to the standard output.

## Running the traffic light example controller demo
The traffic light controller example runs on a ST Microelectronics Nucleo-L010RB microcontroller board with a 'Multi-Function Shield' attached to it.

The project in the `demos/TrafficLightsL010RB` folder can be compiled with the [`platform.io`](https://platformio.org/) framework. It doesn't support this particular microcontroller board out of the box. However, after installing the support for other Nucleo-L boards (such as the [NUCLEO L011K4](https://docs.platformio.org/en/latest/boards/ststm32/nucleo_l011k4.html)), the file lib/nucleo_l010rb.json file can be copied to the `platforms/ststm32/boards/` subdirectory of the platform.io installation (typically in `/home/username/.platformio/`). Note this JSON file is just enough to get the board working. Many of the debugging symbols are incorrect, and for unknown reasons, compiled binaries of a size greater than 64 kilobytes are not transferred to the microcontroller correctly.

Running `pio run -t upload` then compiles the project and uploads the compiled project to the microcontroller board.
