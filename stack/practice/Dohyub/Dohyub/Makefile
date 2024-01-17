.SUFFIXES : .c .o
CC = gcc
CFLAGS = -g -Wall -ansi -std=c99
 all: test

OBJS = ArrayStack.o stack_ex02.o
SRCS = $(OBJS:.o=.c)

test: $(OBJS)
	$(CC) -o stack_ex02 $(OBJS) 

clean: 
	rm -rf $(OBJS)
distclean: 
	rm -rf $(OBJS) ArrayStack test
