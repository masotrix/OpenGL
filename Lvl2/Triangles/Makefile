CC= g++
CFLAGS= -lGL -lglut -lGLEW -I. -g
DEPS= shaders.h
OBJ= main.o shaders.o


# Compiling

%.o: %.cpp	$(DEPS)
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
