tracker: output
		 cc -o bin/tracker -g main.c src/tools.c src/date.c 
output:
		mkdir -p bin/
