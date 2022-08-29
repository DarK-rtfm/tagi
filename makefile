CXX=clang++
INC_DIR=./src/include
CCFLAGS=-Wall -Werror -O3 -I$(INC_DIR) -std=c++20 -stdlib=libc++
LIBDIR=./lib
BINDIR=./bin


all: tagi.so tagi.cli 

tagi.so: 
	[ -d $(LIBDIR) ] || mkdir -p $(LIBDIR)
	$(CXX) $(CCFLAGS) -shared -fPIC ./src/lib/*/*/*.cc -o ./lib/tagi.so

tagi.cli: tagi.so
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(CXX) $(CCFLAGS) $(LIBDIR)/tagi.so ./src/mains/cli.cc -o ./bin/tagi.cli

test: tagi.so 
	[ -d $(BINDIR)/test ] || mkdir -p $(BINDIR)/test
	$(CXX) $(CCFLAGS) -lcppunit $(LIBDIR)/tagi.so ./test/*.cc -o $(BINDIR)/test/main.bin
	$(BINDIR)/test/main.bin

.PHONY: all
