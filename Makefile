export CC = clang
export AR = llvm-ar
export AS = llvm-mc
export CPP = clang++
export LD = ld.lld
export CFLAGS = -Wall -Werror -std=c99 -flto -I$(PWD)/include/ -O0 -g -fpic
export LDFLAGS = -fuse-ld=lld 

.PHONY: all
all: 
	$(MAKE) -C src all

.PHONY: dist
dist:
	rm -rf dist
	mkdir -p dist/lib
	cp build/libetch.so dist/lib/libetch.so
	cp dist.makefile dist/Makefile
	cp -r include dist/include

	tar -czvf etch_precompiled_alpha.tar.xz -C dist $$(cd dist && echo *)
