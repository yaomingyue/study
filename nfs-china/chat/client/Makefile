all:curses.o client.o
	cc -o client curses.o client.o -lncurses
curses.o:curses.c
	cc -c -g curses.c -lncurses

client.o:client.c
	cc -c -g client.c 
