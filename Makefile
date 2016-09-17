############################################################################
#
#  	Filename: Makefile
#	Description: A makefile which supports three compilers:
#		     (a) Host - GCC
#                    (b) BeableBone - ARM_LINUX
#                    (c) FRDM-KL25z - ARM_NONE
#                    Please see README.md for information on makefile use
#                    
#       Author: Kathy Grimes 
#               Dylan Way
#       
############################################################################


# Instruction 12 requires output executable to be called project for BBB or Host
# Target filename = project


### Dependent on architecture
# CC [options] filenames [libraries]...
# Accepts a list of C source and object files contained in the list of files specified by filenames
# One option is -o (if not used the executed code is placed in a.out rather than the file named by the -o option
# libraries can be standard or user-provided libraries containing functions, macros, and definitons of constants
CC =

#
CFLAGS =


# Always have a clean
clean:


# Do we have dependencies in this project
depend: