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
    project_2.c   \
    circbuf.c   \
    error.c   \
    ftoa_utests.c   \
    buf_utests.c   \
    log.c   \
    memory.c   \
    data.c   

OBJS := \
    main.o   \
    project_1.o   \
    project_2.o   \
    circbuf.o   \
    error.o   \
    ftoa_utests.o   \
    buf_utests.o   \
    log.o   \
    memory.o   \
    data.o  

HDRS := \
    project_1.h   \
    project_2.h   \
    circbuf.h   \
    error.h   \
    ftoa_utests.h   \
    buf_utests.h   \
    log.h   \
    memory.h   \
    data.h  

