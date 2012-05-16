install:
	g++ -shared -Wl,-soname,libcagepeers.so.1 -o libcagepeers.so getpeers.o -I../include -I/usr/include/python2.7 -L/usr/local/lib -lcrypto -lpython2.7 -lboost_python -lboost_thread -L../src/libcage -lcage
