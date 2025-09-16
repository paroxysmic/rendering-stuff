br: obj/br.o obj/dl.o obj/ml.o
	g++ -Iinclude obj/br.o obj/dl.o obj/ml.o -Wall -O3 -o br
obj/br.o: src/basicrasterizer.cpp
	g++ -Iinclude -c src/basicrasterizer.cpp -o obj/br.o
obj/dl.o: src/drawlib.cpp
	g++ -Iinclude -c src/drawlib.cpp -o obj/dl.o
obj/ml.o: src/matrlib.cpp
	g++ -Iinclude -c src/matrlib.cpp -o obj/ml.o

.PHONY: clean

clean:
	CLEAN br
	@rm -f obj/br.o obj/dl.o obj/ml.o br
	