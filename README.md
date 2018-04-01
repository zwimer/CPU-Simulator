# CPU Simlulator

A fully functional CPU simlulator that runs different scheduling algorithm and compares the results!

## Disclaimer

This application was designed with certain specifications, such as the time it takes for a context switch to occur (t_cs) to be greater than 0. Furthermore, it expects that io-time will be greater than t_cs. This application also expects input to be given as follows: Each line not beginning with a # (a comment line character), must either contain only whitespace or must be in the following form: \<proc-num\>|\<burst-time\>|\<num-burst\>|\<io-time\>

## Requirements

This application requires the use of cmake 3.0 and C++98 to build.

## Installation Instructions:

First, cd into the directory you would like to install this application in

Then git clone this repository
```bash
git clone https://github.com/zwimer/OpSysProject1
```

Create your build directory as follows
```bash
mkdir OpSysProject1/build && cd OpSysProject1/build/
```

After that run qmake and make with the command below
```bash
cmake ../Project1 && make
```

## Usage
This application takes two arguments. The first is the input file, the file to be read. And the second is the file to which the simulations statics must be written.
