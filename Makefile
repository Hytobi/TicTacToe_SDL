all : exec run


exec : main.o sldInterface.o textInterface.o ticTacToe.o 
	gcc -o exec main.o sldInterface.o textInterface.o ticTacToe.o  -L./lib/lib -lSDL2

main.o : main.c sldInterface.h textInterface.h ticTacToe.h userInterface.h
	gcc -c main.c -I./lib/include

sldInterface.o : sldInterface.c sldInterface.h userInterface.h rage.h
	gcc -c sldInterface.c -I./lib/include

textInterface.o : textInterface.c textInterface.h userInterface.h rage.h
	gcc -c textInterface.c -I./lib/include

ticTacToe.o : ticTacToe.c ticTacToe.h userInterface.h sldInterface.h textInterface.h rage.h
	gcc -c ticTacToe.c -I./lib/include


clean :
	rm -rf *.o

run : exec
	./exec
