# mousegame makefile

# compiler
CC = gcc

# source 
SOURCE = \
	main.c \
	animation.c \
	audio.c \
	bonus.c \
	cat.c \
	coffee.c \
	ending.c \
	game.c \
	gameover.c \
	graphics.c \
	input.c \
	mob.c \
	mouse.c \
	play.c \
	score.c \
	sequence.c \
	sprite.c \
	stage.c \
	tile.c \
	title.c \
	videomap.c

# compiler flags
# -ansi for ansi c standard
# -Wall for compiler warnings
#
CFLAGS = \
	-ansi \
	-Werror \

# linker flags
# -lm for math library
# -lSDL2 for SDL2
# -lSDL2_mixer for SDL2 (audio) mixer
LFLAGS = \
	-lm \
	-lSDL2 \
	-lSDL2_mixer

# output file (executable)
OUT = mousegame

all : $(SOURCE)
	@echo Building $(OUT)...
	$(CC) $(SOURCE) $(CFLAGS) $(LFLAGS) -o $(OUT)
	@echo Done.

# clean
clean:
	-rm $(OUT)

