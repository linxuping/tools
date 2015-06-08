
CC = g++
CFLAGS = 
CPPFLAGS = -g -w

COMPILE = $(CC) $(CFLAGS) $(CPPFLAGS) 
BUILT_SOURCES = common.h
BASE_SOURCES = common.h
objects = main.o
main.o: test_common.c ${BASE_SOURCES}

all:
	@echo "make now "
	# ${COMPILE} ${objects}

install:
	@echo "install... ..."

clean: 
	@rm *.o *.i *.ii *.s

