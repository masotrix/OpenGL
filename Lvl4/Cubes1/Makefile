CC= g++
CFLAGS= -lGL -lGLEW -lglfw -I.
CFLAGS+= -IWorld -IWorld/Tool -IWorld/Figure
CFLAGS+= -ICamera -ICamera/Shaders -ICamera/Controls 
CFLAGS+= -g -std=c++11

DEPS= World/world.h World/Figure/figure.h World/Tool/tool.h 
DEPS+= Camera/camera.h Camera/Shaders/shaders.h Camera/Controls/controls.h

OBJ= main.o 
OBJ+= World/Figure/figure.o World/Tool/tool.o World/Tool/toolSamples.o
OBJ+= Camera/Shaders/shaders.o Camera/Controls/controls.o


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
