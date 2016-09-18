############################################################################
#
#  	Filename: sources.mk
#	Description: Includes a list of source files and include paths
#                    needed for the build system
#       Author: Kathy Grimes 
#               Dylan Way
#       
############################################################################

SRCS := \
    main.c   \
    project_1.c   \
    memory.c   \
    data.c

OBJS := $(SRCS:.c = .o) 

HDRS := \
    project_1.h   \
    memory.c   \
    data.c

INCLUDES = \
    ../source   \
    ../headers

