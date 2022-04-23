CXX?=g++
CCFLAGS=-Wall -O3 -Werror
LIBDIR=./lib
BINDIR=./bin


all: tagi.so tagi.cli 

tagi.so: 
	[ -d $(LIBDIR) ] || mkdir -p $(LIBDIR)
	$(CXX) $(CCFLAGS) -shared -fPIC ./src/lib/*.cc -o ./lib/tagi.so

tagi.cli: bindir tagi.so
	$(CXX) $(CCFLAGS) $(LIBDIR)/tagi.so ./src/mains/cli.cc -o ./bin/tagi.cli

bindir:
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)

test: all
	[ -d $(BINDIR)/test ] || mkdir -p $(BINDIR)/test
	$(CXX) $(CCFLAGS) -lcppunit $(LIBDIR)/tagi.so ./test/main.cc -o $(BINDIR)/test/main.bin
	$(BINDIR)/test/main.bin

.PHONY: all
