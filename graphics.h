/**

Mouse Game
Version 0.9.8

Copyright 2021 Brian Puthuff

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
   may be used to endorse or promote products derived from this software without
   specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/



#ifndef GRAPHICS_H
#define GRAPHICS_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "game.h"



#define RENDER_W 288
#define RENDER_H 216
#define WINDOW_SCALE 5
#define NUMBER_OF_PALETTES 16



extern struct Game game;



struct Graphics
{
	uint8_t palette;
	uint16_t scaler;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Surface *surface;
	SDL_Surface *scaled_surface;
	SDL_Texture *texture;
	SDL_Palette *palettes [ NUMBER_OF_PALETTES ];
};


/**
* Allocates memory on the heap for a Graphics structure.
*
* \param No input parameters
* \returns A pointer to the allocated Graphics structure
*/
struct Graphics *createGraphics ( void );



/**
* Frees memory from the heap of a previously allocated Graphics structure.
*
* \param graphics: A pointer to a Graphics structure
* \returns No return value (void)
*/
void destroyGraphics ( struct Graphics *graphics );



/**
* Performs rendering sequence. This function draws tiles and sprites to the mix surface, transfers the mix surface to the streaming texture and renders the streaming texture.
*
* \param game: A pointer to a Game struct
* \returns No return value (void)
*/
void renderGame ( struct Game *game );



/**
* Initialize the palette colors for all the palettes.
*
* \param game: A pointer to a SDL_Palette pointer array
* \returns No return value (void)
*/
void initializePalettes ( SDL_Palette **palettes );


/**
* Draws a tile to the mix surface.
*
* \param game: A pointer to a Game struct
* \param tile_id: The index of the tile to draw.
* \param x: The horizontal pixel position to start drawing the tile.
* \param y: The vertical pixel position to start drawing the tile.
* \param foreground_render: -1 skips drawing of foreground (on) pixels. 1 draws foreground (on) pixels.
* \param background_render: -1 skips drawing of background (off) pixels. 1 draws background (off) pixels.
* \returns No return value (void)
*/
void renderTileToSurface ( struct Game *game, uint16_t tile_id, int16_t x, int16_t y, int8_t foreground_render, int8_t background_render );



/**
* Draws all tiles on video map to the mix surface.
*
* \param game: A pointer to a Game struct
* \returns No return value (void)
*/
void renderVideoMapToSurface ( struct Game *game );



/**
* Draws a sprite to the mix surface.
*
* \param game: A pointer to a Game struct
* \param sprite_id: The index of the sprite to draw.
* \param x: The horizontal pixel position to start drawing the sprite.
* \param y: The vertical pixel position to start drawing the sprite.
* \param foreground_render: -1 skips drawing of foreground (on) pixels. 1 draws foreground (on) pixels.
* \param background_render: -1 skips drawing of background (off) pixels. 1 draws background (off) pixels.
* \returns No return value (void)
*/
void renderSpriteToSurface ( struct Game *game, int16_t sprite_id, int16_t x, int16_t y, int8_t foreground_render, int8_t background_render );



/**
* Draws all sprites from the sprite batch to the mix surface.
*
* \param game: A pointer to a Game struct
* \returns No return value (void)
*/
void renderSpriteBatchToSurface ( struct Game *game );


/**
* Checks the desktop video display resolution and determines a rationale scaler value for the game window.
*
* \param No input parameter (void)
* \returns A scale integer value
*/
uint16_t getScale ( void );



/**
* Creates and exports BMP image copy of the mix surface, integer scaled to the game window resolution.
*
* \param graphics: A pointer to a Graphics structure
* \returns No return value (void)
*/
void screenShot ( struct Graphics *graphics );



#endif
