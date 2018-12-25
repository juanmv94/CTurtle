# CTurtle

A C adaptation of the Logo programming language (and it infamous turtle).

## About

Logo is a good programming languaje for introducing people to programming and algorithms. However it's very limited, and learning it, you won't do any more than move turtles.
This C adaption allows you to use the C languaje to handle the turtle.

## Getting Started

CTurtle runs with the SDL2 library:

 * For Windows version using MinGW you must download SDL2 from https://www.libsdl.org/
 * For Ubuntu/Debian/Raspbian you can simply do **sudo apt-get install libsdl2_dev**

Check the examples and *turtle.h* to learn how to use it.

## How to compile

### Windows (MinGW)

gcc -O3 -c turtle.c

gcc -O3 -c *myMainFile.c*

gcc turtle.o *myMainFile.o* -lmingw32 -lSDL2main -lSDL2 -o *myExecutable.exe*

### Linux

gcc -O3 -c turtle.c

gcc -O3 -c *myMainFile.c*

gcc turtle.o *myMainFile.o* -lSDL2 -lm -o *myExecutable.exe*

## How to use

Check the examples and *turtle.h* to learn how to use it.

## Examples

 * **simple.c:** try to run this example first. This is a very basic example of the CTurtle library.
 * **sierpinski.c:** generates sierpinski pyramids.
 * **fern.c:** cool.
 * **loading.c:** simulates a loading screen animation, or something similar.
 * **rawaudio.c:** draws sound waves from a PCM_U8 file.
