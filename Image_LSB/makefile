##
#  EasyBMP Cross-Platform Windows Bitmap Library  
#                                                
#  Author: Paul Macklin                          
#   email: macklin01@users.sourceforge.net       
# support: http://easybmp.sourceforge.net        
#          file: makefile                
#    date added: 04-22-2006                      
# date modified: 12-01-2006                      
#       version: 1.06                            
#                                                
#   License: BSD (revised/modified)              
# Copyright: 2005-6 by the EasyBMP Project        
#                                                
# description: Sample makefile for compiling with
#              the EasyBMP library. This compiles
#              the EasyBMPsample.cpp program.
#

CC = g++

# this line gives compiler optimizations that are geared towards g++ and Pentium4 
# computers. Comment it out if you don't have a Pentium 4 (or Athlon XP) or up

# CFLAGS = -O3 -Wno-deprecated -mcpu=pentium4 -march=pentium4 \
# -mfpmath=sse -msse -mmmx -msse2 -pipe -fomit-frame-pointer -s 

# Uncomment these two lines to use with any Pentium with MMX or up.

# CFLAGS = -Wno-deprecated -mcpu=pentium -march=pentium -pipe \
# -fomit-frame-pointer -mmmx -funroll-all-loops -s

# Uncomment these lines for some "safe" optimization flags

CFLAGS = -O3 -pipe

all: munchkinsteg toto

munchkinsteg: EasyBMP.o steganography.o munchkinsteg.o
	g++ -std=c++11 $(CFLAGS) EasyBMP.o steganography.o munchkinsteg.o -o munchkinsteg

toto: EasyBMP.o steganography.o toto.o
	g++ -std=c++11 $(CFLAGS) EasyBMP.o steganography.o toto.o -o toto

EasyBMP.o: EasyBMP.cpp EasyBMP*.h
	g++ -std=c++11 $(CFLAGS) -c EasyBMP.cpp

steganography.o: steganography.h steganography.cpp 
	g++ -std=c++11 -c steganography.cpp 
	
munchkinsteg.o: steganography.h munchkinsteg.cpp
	g++ -std=c++11 -c munchkinsteg.cpp

toto.o: steganography.h toto.cpp
	g++ -std=c++11 -c toto.cpp

test: munchkinstegTest totoTest

munchkinstegTest: steganography.h EasyBMP.h LSBTests.cpp
	g++ -std=c++11 -isystem gtest/include -pthread steganography.cpp LSBTests.cpp EasyBMP.cpp libgtest.a -o munchkinstegTest

totoTest: steganography.h EasyBMP.h LSBAttackTests.cpp
	g++ -std=c++11 -isystem gtest/include -pthread steganography.cpp LSBAttackTests.cpp EasyBMP.cpp libgtest.a -o totoTest


clean:
	rm -f *.o
