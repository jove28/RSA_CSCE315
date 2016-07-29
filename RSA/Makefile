# makefile

all: dorothy munchkincrypt

Prime.o: Prime.h Prime.cpp
	g++ -std=c++11 -c -g Prime.cpp

RSA.o: RSA.h RSA.cpp
	g++ -std=c++11 -c -g RSA.cpp

munchkincrypt: munchkincrypt.cpp Prime.o RSA.o
	g++ -std=c++11 -g -o munchkincrypt munchkincrypt.cpp Prime.o RSA.o

dorothy: Dorothy.cpp RSA.o Prime.o PollardAttack.h Fermat.h ChineseRemainder.h
	g++ -std=c++11 -g -o dorothy Dorothy.cpp Fermat.cpp ChineseRemainder.cpp PollardAttack.cpp RSA.o Prime.o
	
clean: 
	rm *.o dorothy munchkincrypt
