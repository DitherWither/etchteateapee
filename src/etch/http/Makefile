export

OBJS=header.o request.o server.o

.PHONY: all
all: ../http.o

../http.o: $(OBJS)
	$(MAKE) -C response all
	$(LD) -o ../http.o -relocatable $(OBJS) response.o

.PHONY: clean
clean:
	rm $(OBJS)
	$(MAKE) -C response clean