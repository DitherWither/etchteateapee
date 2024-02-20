export

.PHONY: all
all: main.o
	$(MAKE) -C etch all

	mkdir -p ../build
	cp etch/libetch.so ../build
	$(CC) $(LDFLAGS) $(CFLAGS) -o ../build/etchteateapee \
		-letch -L../build/ -Wl,-rpath='$$ORIGIN' main.o

.PHONY: clean
clean:
	rm -rf ../build
	$(MAKE) -C etch clean