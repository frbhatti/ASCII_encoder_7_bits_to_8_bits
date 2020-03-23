#******************************************************************************
# 
#
# Redistribution, modification or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are 
# permitted to modify this and use it to learn about the field of embedded
# software. 
#
#*****************************************************************************

#------------------------------------------------------------------------------
# Makefile for ASCII encoder application
#
# Use: make <optional>build
#
#@author: Fahad Rahim Bhatti
#@date: 23 March 2020
#------------------------------------------------------------------------------

# Compiler Flags and Defines
CSTD=c99
CC = gcc
CFLAGS = -g -std=$(CSTD) -Wall -Werror -O0

# Other Flags and Defines


# Rule and Recipe to generate object files from source files, do not link

build: main.c 
	$(CC) -o main.out main.c 

clean:
	rm -f main.out

