export

OBJS=parse.o serve_file.o

.PHONY: all
all: ../response.o 

../response.o: $(OBJS)
	$(LD) -o ../response.o -relocatable $(OBJS)

.PHONY: clean
clean:
	rm $(OBJS)