CXX?=g++
CCFLAGS=-Wall -Werror -O3 -std=c++20
LIBDIR=./lib
BINDIR=./bin


all: tagi.so tagi.cli 

tagi.so: 
	[ -d $(LIBDIR) ] || mkdir -p $(LIBDIR)
	$(CXX) $(CCFLAGS) -shared -fPIC ./src/lib/*.cc -o ./lib/tagi.so

tagi.cli: tagi.so
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(CXX) $(CCFLAGS) $(LIBDIR)/tagi.so ./src/mains/cli.cc -o ./bin/tagi.cli

test: all
	[ -d $(BINDIR)/test ] || mkdir -p $(BINDIR)/test
	$(CXX) $(CCFLAGS) -lcppunit $(LIBDIR)/tagi.so ./test/*.cc -o $(BINDIR)/test/main.bin
	$(BINDIR)/test/main.bin

.PHONY: all
