install:
	g++ -shared -Wl,-soname,libcagepeers.so.1 -o libcagepeers.so getpeers.cpp -I../include -I/home/sunshadow/Software/BoostInstall/include -I/usr/include/python2.7/ -L/home/sunshadow/Software/BoostInstall/lib -L/home/sunshadow/Software/openssl-0.9.8x -lcrypto -lpython2.7 -lboost_python -lboost_thread -L../src/libcage -lcage
