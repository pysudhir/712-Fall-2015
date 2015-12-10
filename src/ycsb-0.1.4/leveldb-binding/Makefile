LIB=-L../../leveldb
INCLUDES=-I/usr/lib/jvm/java-7-openjdk-amd64/include -I../../leveldb/include 

.PHONY: all

all: ycsbleveldb

ycsbleveldb: ycsbleveldb.cpp
	g++ -Wall $(LIB) $(INCLUDES) -g -shared -o libycsbleveldb.so ycsbleveldb.cpp -fPIC -lleveldb -lpthread

clean:
	rm -f libycsbleveldb.so
