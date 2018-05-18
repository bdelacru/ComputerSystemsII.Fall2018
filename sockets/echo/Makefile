CC = gcc
LDFLAGS = -pthread -lnsl -lrt 
CFLAGS = -w 

all: xechoserver xechoclient 

xechoserver: echoserver.c nethelp.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ echoserver.c nethelp.c

xechoclient: echoclient.c nethelp.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ echoclient.c nethelp.c

clean:
	rm -f xechoserver xechoclient *.o *~ core
