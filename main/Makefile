main:moon.o main.o
	gcc -o main moon.o main.o
print.o:moon.c
	gcc -c moon.c
main.o:main.c main.h
	gcc -c main.c main.h

clean:
	rm main.o moon.o main
