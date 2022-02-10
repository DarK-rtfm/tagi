CXX=g++
CCFLAGS=-Wall -O3


all: tagi.so tagi.cli 

tagi.so: 
	$(CXX) $(CCFLAGS) -shared -fPIC ./src/lib/*.cc -o ./lib/tagi.so

tagi.cli: tagi.so
	$(CXX) $(CCFLAGS) ./lib/tagi.so ./src/mains/cli.cc -o ./bin/tagi.cli

