LIB=-L/Users/pysudhir/ados/leveldb/ldb
INCLUDES=-I/System/Library/Frameworks/JavaVM.framework/Headers -I/Users/pysudhir/ados/leveldb/ldb/include 

.PHONY: all

all: ycsbleveldb

ycsbleveldb: ycsbleveldb.cpp
	g++ -Wall $(LIB) $(INCLUDES) -g -dynamiclib -o /Users/pysudhir/ycsb/ycsb-0.1.4/leveldb-binding/libycsbleveldb.dylib ycsbleveldb.cpp -framework JavaVM -lleveldb -lpthread

clean:
	rm -f /Users/pysudhir/ycsb/ycsb-0.1.4/leveldb-binding/libycsbleveldb.dylib
	rm -rf /Users/pysudhir/ycsb/ycsb-0.1.4/leveldb-binding/libycsbleveldb.dylib.dSYM
