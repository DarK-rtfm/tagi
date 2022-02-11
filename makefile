CXX=g++
CCFLAGS=-Wall -O3 -Werror
LIBDIR=./lib
BINDIR=./bin


all: tagi.so tagi.cli 

tagi.so: 
	[ -d $(LIBDIR) ] || mkdir -p $(LIBDIR)
	$(CXX) $(CCFLAGS) -shared -fPIC ./src/lib/*.cc -o ./lib/tagi.so

tagi.cli: tagi.so
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(CXX) $(CCFLAGS) ./lib/tagi.so ./src/mains/cli.cc -o ./bin/tagi.cli

