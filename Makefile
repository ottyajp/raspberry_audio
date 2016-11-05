build:
	g++ ./main.cpp -lwiringPi -lpthread -std=c++11

clean:
	rm ./a.out
