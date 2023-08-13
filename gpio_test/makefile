INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt


blink : blink.c
	gcc -Wall -o blink blink.c $(INCLUDE) $(CFLAGS) $(LDIBS) $(LDFLAGS)
