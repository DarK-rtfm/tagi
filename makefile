CXX=clang++
INC_DIR=./src/include
CCFLAGS=-Wall -Werror -O3 -I$(INC_DIR) -std=c++20 -stdlib=libc++ -U_LIBCPP_HAS_NO_INCOMPLETE_RANGES
CCFLAGS_TEST=-Wall -Werror -O3 -I$(INC_DIR) -std=c++20
LIBDIR=./lib
BINDIR=./bin


all: tagi-unittest.so tagi.so tagi.cli 

tagi.so: 
	[ -d $(LIBDIR) ] || mkdir -p $(LIBDIR)
	$(CXX) $(CCFLAGS) -shared -fPIC ./src/lib/*/*/*.cc -o ./lib/tagi.so

tagi-unittest.so: tagi.so
	$(CXX) $(CCFLAGS_TEST) -shared -fPIC ./src/lib/*/*/*.cc -o ./lib/tagi-unittest.so

tagi.cli: tagi.so
	[ -d $(BINDIR) ] || mkdir -p $(BINDIR)
	$(CXX) $(CCFLAGS) $(LIBDIR)/tagi.so ./src/mains/cli.cc -o ./bin/tagi.cli

test: tagi-unittest.so 
	[ -d $(BINDIR)/test ] || mkdir -p $(BINDIR)/test
	$(CXX) $(CCFLAGS_TEST) -lcppunit $(LIBDIR)/tagi-unittest.so ./test/*.cc -o $(BINDIR)/test/main.bin
	$(BINDIR)/test/main.bin

.PHONY: all
