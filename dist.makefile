CFLAGS=-Wall -Werror -std=c17 -I$(PWD)/include/
LDFLAGS=-letch -Llib/ -Wl,-rpath='$$ORIGIN/lib'