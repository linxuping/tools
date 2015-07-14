#$@--目标文件，$^--所有的依赖文件，$<--第一个依赖文件。
CC = g++
CFLAGS = -Wall -g -w
CPPFLAGS = -g -w

COMPILE = $(CC) $(CFLAGS) $(CPPFLAGS) 
BASE_SOURCES = common.h

test: test_common.c ${BASE_SOURCES}
	@echo "make now !"
	$(CC) $(CFLAGS) -o $@ $^

install:
	@echo "install... ..."

clean: 
	@rm *.o *.i *.ii *.s test

