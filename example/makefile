test:
	g++ test.cpp $(pkg-config --cflags libcurl) $(curl-config --libs) -std=c++11 -o test
	./test

run:
	./test

clean:
	rm -r test