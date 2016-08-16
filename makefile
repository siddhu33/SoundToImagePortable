CFLAGS = -std=c++11 -O3 -Wall

soundToImage:
	$(CXX) soundToImage.cpp colorManipulation.cpp -I SFML-2.3.2/include/ -L SFML-2.3.2/lib/ $(CFLAGS) -o soundToImage -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
clean:
	rm -f soundToImage
