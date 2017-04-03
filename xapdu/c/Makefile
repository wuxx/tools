CC     = gcc
CFLAGS = -I. -lnfc
#CFLAGS = -I. /usr/local/lib/libnfc.a
#CFLAGS = -I. /usr/lib/x86_64-linux-gnu/libnfc.so.5

OBJ = xapdu

all:
	$(CC) $(CFLAGS) $(OBJ).c -o $(OBJ)

edit:
	vi $(OBJ).c

clean:
	-rm -rf $(OBJ)
