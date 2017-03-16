CC= g++
CFLAGS= -lGL -lGLEW -lglfw
CFLAGS+= -I. -IFigure -IShaders -ITexture -IControls
CFLAGS+= -g -std=c++11
DEPS= Shaders/shaders.h Figure/figure.h
DEPS+= Texture/texture.h Controls/controls.h
OBJ= main.o Shaders/shaders.o Figure/figure.o
OBJ+= Texture/texture.o Controls/controls.o


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
	rm -f Texture/*.o
	rm -f Controls/*.o
