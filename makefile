CXX = g++
CXXFLAGS = -Wall

proj4: proj4.cpp Cipher.o Atbash.o Ong.o Scytale.o CipherTool.o
	$(CXX) $(CXXFLAGS) proj4.cpp Cipher.o Atbash.o Ong.o Scytale.o CipherTool.o -o proj4

Cipher.o: Cipher.h Cipher.cpp
	$(CXX) $(CXXFLAGS) -c Cipher.cpp

Atbash.o: Atbash.h Atbash.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Atbash.cpp

Ong.o: Ong.h Ong.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Ong.cpp

Scytale.o: Scytale.h Scytale.cpp Cipher.o
	$(CXX) $(CXXFLAGS) -c Scytale.cpp

CipherTool.o: CipherTool.h CipherTool.cpp Cipher.o Atbash.o Ong.o Scytale.o
	$(CXX) $(CXXFLAGS) -c CipherTool.cpp
submit:
	cp proj4.cpp Cipher.h Cipher.cpp Atbash.h Atbash.cpp Scytale.h Scytale.cpp CipherTool.h CipherTool.cpp ~/cs202proj/proj4
