# ecen5013_project
This repository is for CU Boulder ECEN5013 Group Projects for kagr7595 and dywa6993

-----------------------------------------------------------------------------------
Makefile Targets:
	preprocess: Generates the preprocessed output of a file
		Ex: make file.i

	asm-file: Generates the assembly output of a file
		Ex: make file.S

	%.o: Compiles a single object file
		Ex: make file.o

	compile-all: Compiles all of the object files but does not link
		Ex: make compile-all

	build: Compiles all object files and links them. Also reports the size of the executable and creates a dependency file
		This target can also take an input specifying the intended build architecture. 
		Options:
			Host -> host (default)
			Beagle Bone -> bbb
			FRDM-KL25Z -> frdm
		Ex: make build ARCH=bbb

	upload: Copies the executable file to the release directory on the Beagle Bone using scp
		Ex: make upload

	clean: Removes all .map, .out, .o, .S, .i, .dep, and .objdump files
		Ex: make clean

	build-lib: Generates a library of the memory.c and data.c files into an archive called libproject1.a
		Ex: make build-lib

	%.objdump: Generates a *.objdump containing the source code along with the disassembly for the matching object file
		Ex: make file.objdump

	depend: Generates a dependency file containing the dependencies for each of the object files called file_dependency.dep
		Ex: make depend
	
