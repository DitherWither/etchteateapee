export CC = clang
export AR = llvm-ar
export AS = llvm-mc
export CPP = clang++
export LD = ld.lld
export CFLAGS = -Wall -Werror -std=c17 -flto -I$(PWD)/include/ -O0 -g -fpic
export LDFLAGS = -fuse-ld=lld 


.PHONY: all
all: 
	$(MAKE) -C src all

# etchteateapee: $(OBJS)
# 	$(CC) $(LDFLAGS) -o etchteateapee $(OBJS)
	