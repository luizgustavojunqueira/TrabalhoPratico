CC=g++

mj_compiler: principal.cpp parser.cpp scanner.cpp token.h
	$(CC) -o mj_compiler principal.cpp parser.cpp scanner.cpp

clean: 
	rm *.o mj_compiler
