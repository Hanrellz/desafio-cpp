all: publisherSubscriber

publisherSubscriber: pubSub.o libZeromq.o
	g++ pubSub.o libZeromq.o -lPocoFoundation -pthread -lzmq -o publisherSubscriber

pubSub.o: pubSub.cpp
	g++ -c pubSub.cpp -o pubSub.o

libZeromq.o: libZeromq.cpp 
	g++ -c libZeromq.cpp -o libZeromq.o

.PHONY: clean

clean: 
	rm -f publisherSubscriber libZeromq.o pubSub.o