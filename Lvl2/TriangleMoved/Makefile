CC= g++
CFLAGS= -lGL -lGLEW -I. -IShaders -IFigure -IControls
CFLAGS+= -g -lglfw -std=c++11
DEPS= Shaders/shaders.h Figure/figure.h Controls/controls.h
OBJ= main.o Shaders/shaders.o Figure/figure.o Controls/controls.o


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
	rm -f Figure/*.o
	rm -f Shaders/*.o
