CC= g++
CFLAGS= -lGL -lglut -lGLEW -lglfw -I. -g
DEPS= shaders.h
OBJ= main.o shaders.o

all:
	$(MAKE) run
	$(MAKE) clean

run: $(OBJ)
		$(CC) $^ -o $@ $(CFLAGS)

%.o: %.cpp	$(DEPS)
		$(CC) $< -c -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
