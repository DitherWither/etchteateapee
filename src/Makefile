export

.PHONY: all
all: main.o
	$(MAKE) -C etch all

	mkdir -p ../build
	cp etch/libetch.so ../build
	$(CC) $(LDFLAGS) -o ../build/etchteateapee \
		-letch -L../build/ -Wl,-rpath='$$ORIGIN' main.o

.PHONY: clean
clean:
	$(MAKE) -C etch clean