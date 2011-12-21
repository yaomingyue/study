
main:main.o dog.o cat.o cock.o moon
	cc -o main main.o dog.o cat.o cock.o

main.o: main.c main.h cat.h dog.h cock.h
	cc -c main.c

moon:
	echo 'kkkkkkkkkkkkk'
cat.o: cat.c main.h
	cc -c cat.c
dog.o: dog.c main.h
	cc -c dog.c
cock.o: cock.c main.h
	cc -c cock.c
moon = "yaomoon"
$(info $(moon))
clean:
	rm main main.o cat.o dog.o cock.o
