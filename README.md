To compile:

g++ -c src/*.cpp -std=c++11
g++ -o starship *.o -lSDL -lSDL_image -lSDL_mixer -std=c++11
./starship

Created on fedora 20.

Initial goals of game:
Spawn as rabbit on game world, collect/eat carrots, avoid enemy foxes scattered round the map. Once enough carrots have been eaten
progress to next level of the game. 

Goals not met: 
Enemy foxes (made the player also disappear when collision occurred so had to keep them static)

true pixel game world (used green colour to simulate grass instead as could not figure out how to implement tile map
into pre-existing code)

game completion/level change (created an image to declare game over but did not understand how to call it when enough carrots
were eaten)