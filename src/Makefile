.PHONY: clean

OBJS := main.o server.o dispatcher.o handler.o rio.o

CC := g++ 

.cc.o:
	$(CC) $(CFLAGS) $< -c -o $@

sulcata: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f *.o
	@rm -f sulcata
