CC=g++
CFLAGS=-I. -isystem /cs/class/cs130a/googletest/googletest/include -std=c++0x
LDFLAGS=-pthread /cs/class/cs130a/googletest/libgtest.a

all:	minmaxheap_test

minmaxheap_test:
	$(CC) *.cc -o $@ $(CFLAGS) $(LDFLAGS)

debug:
	$(CC) -g *.cc -o $@ $(CFLAGS) $(LDFLAGS)

.PHONY:	clean

clean:
	rm -rf minmaxheap_test debug
