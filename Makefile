CFLAGS=-Wall -pedantic -g

file_manip: file_manip.o myio.o
	gcc -o $@ $^

%.o: %.c
	gcc -c $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f file_manip file_manip.o myio.o
