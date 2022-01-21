all: plumbing.o
	gcc -o output plumbing.o

plumbing.o: plumbing.c
	gcc -c plumbing.c

run:
	./output

clean:
	-rm output
	-rm *.o
