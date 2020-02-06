CC     = gcc
CFLAGS = -I. -lnfc
#CFLAGS = -I. /usr/local/lib/libnfc.a
#CFLAGS = -I. /usr/lib/x86_64-linux-gnu/libnfc.so.5

# sudo apt-get install libnfc-dev

OBJ = xapdu

all:
	$(CC) $(CFLAGS) $(OBJ).c -o $(OBJ)

edit:
	vi $(OBJ).c

test:
	./xapdu 00A4040000 #

clean:
	-rm -rf $(OBJ)
