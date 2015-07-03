all:
	
	swig -c++ -python long_number_lib.i
	g++ -c -w -std=c++11 long_number_lib.cpp
	g++ -c -w -std=c++11 long_number_lib_wrap.cxx -I/Library/Frameworks/Python.framework/Versions/2.7/include/python2.7
	g++ -lpython -dynamiclib long_number_lib.o  long_number_lib_wrap.o -o _long_number_lib.so
