tracker:libtracker
	cc -o bin/tracker main.c -Iinclude -Llib -ltracker
	rm *.o

output:
	mkdir -p bin/

libtracker:obj
	ar cr libtracker.a *.o
	mv libtracker.a lib/

obj:
	gcc -c src/*.c -Iinclude
