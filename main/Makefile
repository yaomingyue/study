main:print.o main.o
	gcc -o main print.o main.o
print.o:print.c
	gcc -c print.c
main.o:main.c main.h
	gcc -c main.c main.h

clean:
	rm main.o print.o main
