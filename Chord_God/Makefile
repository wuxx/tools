JC   = javac
JDC  = javap

JAVA = java

OBJECT = Chord_God

.PHONY: all

all: 
	$(JC) $(OBJECT).java
	$(JDC) -classpath . -c $(OBJECT) > $(OBJECT).dsm

run: 
	$(JAVA) $(OBJECT)


clean:	
	rm -f *.dsm *.class
