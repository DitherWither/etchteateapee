CC=clang
AR=llvm-ar
AS=llvm-mc
CPP=clang++
LD=ld.lld
CFLAGS=-Wall -Werror -std=c17 -flto -Iinclude/ -O0 -g
LDFLAGS=-fuse-ld=lld 

SRCS=\
	src/main.c \
	src/server.c \
	src/request.c \
	src/response.c \
	src/utils.c \
	src/header.c \
	src/response_serve_file.c \
	src/config.c
	
OBJS=\
    src/main.o \
	src/server.o \
	src/request.o \
	src/response.o \
	src/utils.o \
	src/header.o \
	src/response_serve_file.o \
	src/config.o

.PHONY: all
all: etchteateapee

etchteateapee: $(OBJS)
	$(CC) $(LDFLAGS) -o etchteateapee $(OBJS)
	