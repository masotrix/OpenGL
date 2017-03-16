CC= g++
CFLAGS= -lGL -lglut -lGLEW -Ishaders -I. -g -lglfw
DEPS= shaders/shaders.h
OBJ= main.o shaders/shaders.o


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
