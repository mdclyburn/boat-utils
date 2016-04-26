CC = gcc
CFLAGS = -g -std=gnu99

dp: main.o
	$(CC) $(CFLAGS) $^ -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

.PHONY: clean
clean:
	rm -f *.o dp
