############################################################################
#
#  	Filename: sources.mk
#	Description: Includes a list of source files and include paths
#                    needed for the build system
#       Author: Kathy Grimes 
#               Dylan Way
#       
############################################################################

INCHDRS := ./headers

INCSRC := ./source

VPATH = $(INCSRC) $(INCHDRS)

SRCS := \
    main.c   \
    project_1.c   \
    memory.c   \
    data.c

OBJS := \
    main.o   \
    project_1.o   \
    memory.o   \
    data.o

HDRS := \
    project_1.h   \
    memory.h   \
    data.h

