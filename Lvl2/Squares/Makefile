CC= g++
CFLAGS= -lGL -lGLEW -lglfw -I. -IFigure -IShaders -g -std=c++11
DEPS= Shaders/shaders.h Figure/figure.h
OBJ= main.o Shaders/shaders.o Figure/figure.o

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
	rm -f Shaders/*.o
	rm -f Figure/*.o
