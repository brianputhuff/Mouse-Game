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



#ifndef SPRITE_H
#define SPRITE_H



#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <SDL2/SDL.h>



#define MAXIMUM_NUMBER_OF_SPRITES 4096



struct Sprite
{
	uint16_t *data;
	uint8_t w;
	uint8_t h;
	uint16_t a;
};



/**
* Allocates memory on the heap for a Sprite structure.
*
* \param w: The width in tiles 
* \param h: The height in tiles
* \param ...: The sequence of tile indexes (variadic)
* \returns A pointer to the Sprite structure
*/
struct Sprite *createSprite ( uint8_t w, uint8_t h, ... );



/**
* Frees memory from the heap of a previously allocated Sprite structure.
*
* \param sprite: A pointer to an Sprite structure
* \returns No return value (void)
*/
void destroySprite ( struct Sprite *sprite );



/**
* Gets the tile index at a specific tile row and tile column coordinate within a sprite.
*
* \param sprite: A pointer to a Sprite structure
* \param row: A tile row within the sprite
* \param column: A tile column within the sprite
* \returns No return value (void)
*/
uint16_t getTileIdFromSprite ( struct Sprite *sprite, uint8_t row, uint8_t column );



struct Sprites
{
	struct Sprite **data;
	uint16_t count;
};



/**
* Allocates memory on the heap for a Sprites (collection) structure.
*
* \param No input arguments
* \returns A pointer to the Sprites structure
*/
struct Sprites *createSprites ( void );



/**
* Frees memory from the heap of a previously allocated Sprites structure.
*
* \param sprites: A pointer to a Sprites structure
* \returns No return value (void)
*/
void destroySprites ( struct Sprites *sprites );



/**
* Links a pointer to a sprite to the next available sprite pointer in the sprites collection.
*
* \param sequence: A pointer to a Sprites structure
* \param sequence: A pointer to a Sprite structure
* \returns No return value (void)
*/
void addSpriteToSprites ( struct Sprites *sprites, struct Sprite *sprite );



struct SpriteBatch
{
	int32_t sprite_id [ MAXIMUM_NUMBER_OF_SPRITES ];
	int16_t x [ MAXIMUM_NUMBER_OF_SPRITES ];
	int16_t y [ MAXIMUM_NUMBER_OF_SPRITES ];
	int8_t fgr [ MAXIMUM_NUMBER_OF_SPRITES ];
	int8_t bgr [ MAXIMUM_NUMBER_OF_SPRITES ];

	uint16_t count;
};



/**
* Allocates memory on the heap for a SpriteBatch structure.
*
* \param No input arguments
* \returns A pointer to the SpriteBatch structure
*/
struct SpriteBatch *createSpriteBatch ( );



/**
* Frees memory from the heap of a previously allocated SpriteBatch structure.
*
* \param sprites: A pointer to a SpriteBatch structure
* \returns No return value (void)
*/
void destroySpriteBatch ( struct SpriteBatch *spritebatch );



/**
* Clears the data in a sprite batch structure.
*
* \param sprites: A pointer to a SpriteBatch structure
* \returns No return value (void)
*/
void clearSpriteBatch ( struct SpriteBatch *spritebatch );



/**
* Adds sprite data to a sprite batch structure.
*
* \param sprites: A pointer to a SpriteBatch structure
* \param sprite_id: A sprite index
* \param x: The horizontal pixel position to draw the sprite to
* \param y: The vertical pixel position to draw the sprite to
* \param fgr: -1 to not draw the foreground color pixels, 1 to draw them
* \param bgr: -1 to not draw the background color pixels, 1 to draw them
* \returns No return value (void)
*/
void addSpriteToSpriteBatch ( struct SpriteBatch *spritebatch, uint16_t sprite_id, int16_t x, int16_t y, int8_t fgr, int8_t bgr );



#endif
