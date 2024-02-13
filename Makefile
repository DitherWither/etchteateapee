CC=clang
AR=llvm-ar
AS=llvm-mc
CPP=clang++
LD=ld.lld
CFLAGS=-Wall -Werror -std=c17 -flto -Iinclude/ -fsanitize=address -O0 -g
LDFLAGS=-fuse-ld=lld -fsanitize=address 

SRCS=\
	src/main.c \
	src/connection.c \
	src/request.c \
	src/response.c \
	src/utils.c \
	src/header.c
OBJS=\
    src/main.o \
	src/connection.o \
	src/request.o \
	src/response.o \
	src/utils.o \
	src/header.o

.PHONY: all
all: etchteateapee

etchteateapee: $(OBJS)
	$(CC) $(LDFLAGS) -o etchteateapee $(OBJS)
	