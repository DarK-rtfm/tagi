CXX=clang++
INC_DIR=./src/include
CCFLAGS=-Wall -Werror -O3 -I$(INC_DIR) -std=c++2b -stdlib=libc++ -fexperimental-library
CCFLAGS_TEST=-Wall -Werror -O3 -I$(INC_DIR) -std=c++20
LIBDIR=./lib
BINDIR=./bin


all: tagi.cli 

tagi.so: 
	[ -d $(LIBDIR) ] || mkdir -p $(LIBDIR)
	$(CXX) $(CCFLAGS) -shared -Wl,-soname,libtagi.so.0 -fPIC ./src/lib/*/*.cc -o ./lib/libtagi.so.0

tagi-unittest.so: tagi.so
	$(CXX) $(CCFLAGS_TEST) -shared -fPIC ./src/lib/*/*.cc -o ./lib/tagi-unittest.so

tagi.cli: tagi.so
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(CXX) $(CCFLAGS) -L./lib -ltagi ./src/mains/cli.cc -o ./bin/tagi.cli

test: tagi-unittest.so 
	[ -d $(BINDIR)/test ] || mkdir -p $(BINDIR)/test
	$(CXX) $(CCFLAGS_TEST) -lcppunit $(LIBDIR)/tagi-unittest.so ./test/*.cc -o $(BINDIR)/test/main.bin
	$(BINDIR)/test/main.bin

install: 
	install --owner root --group root ./lib/libtagi.so.0 /usr/local/lib/libtagi.so.0
	install --owner root --group root ./bin/tagi.cli /usr/local/bin/tagi
	ldconfig

.PHONY: all
