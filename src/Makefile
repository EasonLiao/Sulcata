.PHONY: clean

OBJS := main.o server.o dispatcher.o handler.o rio.o config.o
CFLAGS := -std=c++0x
LDFLAGS := -pthread
CC := g++ 

.cc.o:
	$(CC) $(CFLAGS) $< -c -o $@

sulcata: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f *.o
	@rm -f sulcata
