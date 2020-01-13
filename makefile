CC = g++
CFLAGS = -O2 -Wall -g

all: bed2ends determine_enriched_ends

bed2ends: bed2ends.o message.o EndsTools.o 
	$(CC) $(CFLAGS) bed2ends.o message.o EndsTools.o -o bed2ends 

determine_enriched_ends: determine_enriched_ends.o message.o EndsTools.o
	$(CC) $(CFLAGS) determine_enriched_ends.o message.o EndsTools.o -o determine_enriched_ends

bed2ends.o: bed2ends.cpp
	$(CC) $(CFLAGS) -c bed2ends.cpp

determine_enriched_ends.o: determine_enriched_ends.cpp
	$(CC) $(CFLAGS) -c determine_enriched_ends.cpp 

message.o: message.cpp message.h
	$(CC) $(CFLAGS) -c message.cpp

EndsTools.o: EndsTools.cpp EndsTools.h
	$(CC) $(CFLAGS) -c EndsTools.cpp

clean:
	rm *.o bed2ends determine_enriched_ends
