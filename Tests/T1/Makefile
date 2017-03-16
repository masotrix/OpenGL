CC= g++
CFLAGS= -lGL -lGLEW -lglfw
CFLAGS+= -g -std=c++11

OBJ= main.o

# Compiling

%.o: %.cpp
		$(CC) $< -c -o $@ $(CFLAGS)


# LinkingV

run: $(OBJ)
		$(CC) $^ -o $@ $(CFLAGS)


# Cleaning

.PHONY: clean

clean:
	rm -f *.o
