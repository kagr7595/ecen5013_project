#
##########################################################################
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


# Target filename = project


### Dependent on architecture
# CC [options] filenames [libraries]...
# Accepts a list of C source and object files contained in the list of files specified by filenames
# One option is -o (if not used the executed code is placed in a.out rather than the file named by the -o option
# libraries can be standard or user-provided libraries containing functions, macros, and definitons of constants





include sources.mk
VPATH = $(INCSRC) $(INCHDRS)

ARCH ?= host
LDFLAGS := -O0 -Wl,-Map=project.map
CFLAGS := -DPROJECT_1 -DPROJECT_2 -DFTOATEST -DCIRCBUFTESTS -Wall -g -std=c99 -I$(INCSRC) -I$(INCHDRS)

ifeq ($(ARCH),bbb)
    CC := arm-linux-gnueabihf-gcc

else 
ifeq ($(ARCH),frdm)
    CC := arm-none-eabi-gcc
    override CFLAGS :=  -DFRDM $(CFLAGS)
    override LDFLAGS := -lc -lrdimon $(LDFLAGS)
else
    CC := gcc

endif
endif


.PHONY: %.o
# Individually compiles any single object file
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $<

.PHONY: %.S
# Generates the assembly output of all files or a single file
%.S: %.c
	$(CC) -S $(CFLAGS) $<

.PHONY: %.i
# Generates the preprocessed output of all files or a single file
%.i: %.c
	$(CC) -E $(CFLAGS) $< > $@ 

.PHONY: compile-all
# Compiles the object files
compile-all: $(SRCS)
	$(CC) -c $(CFLAGS) $^

.PHONY: build
# Compiles all object files and links
build:  clean $(OBJS) depend
	$(CC) $(LDFLAGS) -o project $(OBJS)
	size project

.PHONY: upload
# Takes an executable and copies it over to a release directory on the beagle bone
upload: 
	scp project root@192.168.7.2:/home/debian/bin

.PHONY: clean
# Removes all compiled object, preprocessed output, assembly output, executables, and build output files
clean:
	rm -f project *.o *.s *.i *.map *.out *.dep *.objdump

.PHONY: build-lib
# Generates a library of your memory.c and data.c into an archive called libproject1.a
build-lib: memory.c data.c
	ar cr libproject1.a $+

.PHONY: depend
# Generates a dependencies file for the build
depend: $(SRCS) $(HDRS)
	$(CC) -M $(CFLAGS) $^ > file_dependencies.dep

.PHONY: %.objdump
# Runs objdump -S on the specified file and outputs to a file %.objdump
%.objdump: %.o
	objdump -S $< > $@
