PROJ=fast
CC=cc
SRC=fast.c
LIBS=-lgpiod
CFLAGS=-D CONSUMER=\"$(PROJ)\"

all:
	$(CC) $(SRC) $(LIBS) $(CFLAGS) -o $(PROJ)
	$(CC) fast2pins.c -g $(LIBS) $(CLAGS) -o fast2
clean:
	rm $(PROJ)
