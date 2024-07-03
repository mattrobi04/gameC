build:
	gcc -Wall -std=c99 -I/opt/homebrew/Cellar/sdl2/2.30.4/include ./src/*.c -o game -L/opt/homebrew/Cellar/sdl2/2.30.4/lib -lSDL2

run:
	./game

clean:
	rm game

# CC = gcc
# CFLAGS = -Wall -std=c99 -I/opt/homebrew/Cellar/sdl2/2.30.4/include
# LDFLAGS = -L/opt/homebrew/Cellar/sdl2/2.30.4/lib -lSDL2

# SRCDIR = ./src
# SOURCES = $(wildcard $(SRCDIR)/*.c)
# EXECUTABLE = game

# all: $(EXECUTABLE)

# $(EXECUTABLE): $(SOURCES)
# 	$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

# clean:
# 	rm -f $(EXECUTABLE)
