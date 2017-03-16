CC= g++
CFLAGS= -lglut -lGL
OBJ= main.o

# Compile

%.o: %.cpp
		$(CC) $< -c -o $@ $(CFLAGS)


# Linking

all:
		$(MAKE) run
		$(MAKE) clean

run: $(OBJ)
		$(CC) $^ -o $@ $(CFLAGS)


# Clean

.PHONY: clean

clean:
		rm -f *.o


