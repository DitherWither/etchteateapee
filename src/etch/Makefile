export

.PHONY: all
all: libetch.so

libetch.so:
	$(MAKE) -C core all
	$(MAKE) -C http all

	$(LD) -o etch.o -relocatable core.o http.o

	$(CC) $(LDFLAGS) -shared -o libetch.so etch.o
	

clean:
	rm -f etch.o libetch.so
	$(MAKE) -C core clean
	$(MAKE) -C http clean

