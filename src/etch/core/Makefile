export

OBJS=config.o utils.o

.PHONY: all
all: ../core.o

../core.o: $(OBJS)
	$(LD) -o ../core.o -relocatable $(OBJS)

clean:
	rm -f $(OBJS) ../core.o