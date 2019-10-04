all: ./main.o ./life_game.o ./draw.o

# client:client.o
# 	g++ -g -o client client.o
life.o:life_game.cpp draw.cpp main.cpp
	g++ -g -c life_game.cpp draw.cpp main.cpp
life:main.o life_game.o draw.o
	g++ -o life life.o -lGL -lGLU -lglut
# client.o:client.cpp
# 	g++ -g -c client.cpp
clean:all
	rm -rf main.o life_game.o draw.o life