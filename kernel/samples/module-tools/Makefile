#  
# 

CC=gcc
#CFLAGS= -c -O2 -Wall

insmod_SOURCES=insmod.o 
rmmod_SOURCES=rmmod.o 
libmodtools_SOURCES=util.o logging.o

all: insmod  rmmod  

insmod: $(insmod_SOURCES) $(libmodtools_SOURCES)
	$(CC) -o insmod $(insmod_SOURCES) $(libmodtools_SOURCES)

rmmod: $(rmmod_SOURCES) $(libmodtools_SOURCES)
	$(CC) -o rmmod $(rmmod_SOURCES) $(libmodtools_SOURCES)
clean:
	rm -rf *.o insmod rmmod 

.PHONY: all insmod  rmmod  clean
