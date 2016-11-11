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
    project_3.c   \
    circbuf.c   \
    error.c   \
    ftoa_utests.c   \
    buf_utests.c   \
    log.c   \
    memory.c   \
    data.c  \
    profiler.c  \
    timer.c    \
    command.c   \
    spi_bbb.c   \
    nRF24L01.c   \
    LED_control.c

OBJS := \
    main.o   \
    project_1.o   \
    project_2.o   \
    project_3.o   \
    circbuf.o   \
    error.o   \
    ftoa_utests.o   \
    buf_utests.o   \
    log.o   \
    memory.o   \
    data.o  \
    profiler.o  \
    timer.o    \
    command.o    \
    spi_bbb.o   \
    nRF24L01.o   \
    LED_control.o

HDRS := \
    project_1.h   \
    project_2.h   \
    project_3.h   \
    circbuf.h   \
    error.h   \
    ftoa_utests.h   \
    buf_utests.h   \
    log.h   \
    memory.h   \
    data.h  \
    profiler.h  \
    timer.h    \
    command.h    \
    spi_bbb.h   \
    nRF24L01.h   \
    LED_control.h

