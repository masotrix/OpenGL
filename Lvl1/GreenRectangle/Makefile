CC= g++
CFLAGS= -lGL -lglut -lGLEW -I. -g
OBJ= main.o


# Compiling

%.o: %.cpp
		$(CC) $< -c -o $@ $(CFLAGS)


# Linking

all:
	$(MAKE) run
	$(MAKE) clean

run: $(OBJ)
		$(CC) $^ -o $@ $(CFLAGS)


# Cleaning

.PHONY: clean

clean:
	rm -f *.o
