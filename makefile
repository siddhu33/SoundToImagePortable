main:
	$(CXX) main.cpp colorManipulation.cpp  -I SFML-2.3.2/include/ -L SFML-2.3.2/lib/ -o main -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-window
clean:
	rm -rf main
