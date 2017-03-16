CC= g++
CFLAGS= -lGL -lGLEW -lglfw
CFLAGS+= -I. -IShaders -IControls -IEntity/Tool -IEntity/Figure
CFLAGS+= -g -std=c++11

DEPS= Shaders/shaders.h Controls/controls.h
DEPS+= Entity/Figure/figure.h Entity/Tool/tool.h 

OBJ= main.o Shaders/shaders.o Controls/controls.o
OBJ+= Entity/Figure/figure.o Entity/Tool/tool.o
OBJ+= Entity/Tool/toolSamples.o


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
