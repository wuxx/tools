JC   = javac
JDC  = javap

JAVA = java

.PHONY: all

all: 
	$(JC) HelloWorld.java
	$(JDC) -classpath . -c HelloWorld > HelloWorld.dsm

run: 
	$(JAVA) HelloWorld


clean:	
	rm -f sha1
