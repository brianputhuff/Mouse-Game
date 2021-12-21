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



#ifndef TILE_H
#define TILE_H



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



#define MAXIMUM_NUMBER_OF_TILES 16384
#define FILENAME_TILE_DATA "tiles.bin"



struct Tile
{
	uint8_t patterns [ 8 ];
};



/**
* Allocates memory on the heap for a Tile structure.
*
* \param No input arguments (void)
* \returns A pointer to the Tile structure
*/
struct Tile *createTile ( void );



/**
* Frees memory from the heap of a previously allocated Tile structure.
*
* \param tile: A pointer to an Tile structure
* \returns No return value (void)
*/
void destroyTile ( struct Tile *tile );



/**
* Gets an 8-bit value whose binary representation is a single pixel pattern row.
*
* \param tile: A pointer to an Tile structure
* \param row: A row number in the tile (0 - 7)
* \returns an 8-bit value whose binary representation is a single pixel pattern row
*/
uint8_t getTilePattern ( struct Tile *tile, uint8_t row );



/**
* Sets single pixel pattern row.
*
* \param tile: A pointer to an Tile structure
* \param row: A row number in the tile (0 - 7)
* \param pattern: 8-bit value whose binary representation is a single pixel pattern row
* \returns No return value (void)
*/
void setTilePattern ( struct Tile *tile, uint8_t row, uint8_t pattern );



/**
* Gets single pixel pattern bit value from a select tile row.
*
* \param tile: A pointer to an Tile structure
* \param row: A row number in the tile (0 - 7)
* \param bit_position: Pixel position (0 - 7)
* \returns 1 if bit is on (foreground), and 0 if bit is off (background)
*/
uint8_t getTilePatternBit ( struct Tile *tile, uint8_t row, uint8_t bit_position );



/**
* Sets single pixel pattern bit value from a select tile row.
*
* \param tile: A pointer to an Tile structure
* \param row: A row number in the tile (0 - 7)
* \param bit_position: Pixel position (0 - 7)
* \param but_value: Either 0 (off, background) or 1 (on, foreground)
* \returns 1 if bit is on (foreground), and 0 if bit is off (background)
*/
void setTilePatternBit ( struct Tile *tile, uint8_t row, uint8_t bit_position, uint8_t bit_value );



/**
* Clear and set all rows of a tile to a single pattern.
*
* \param tile: A pointer to an Tile structure
* \param pattern: 8-bit value whose binary representation is a single pixel pattern row
* \returns No return value (void)
*/
void clearTile ( struct Tile *tile, uint8_t pattern );



/**
* Print a tile's data to the console (8 row patterns).
*
* \param tile: A pointer to an Tile structure
* \returns No return value (void)
*/
void printTile ( struct Tile *tile );



struct Tiles
{
	struct Tile** data;
};



/**
* Allocates memory on the heap for a Tiles (collection) structure.
*
* \param No input arguments (void)
* \returns A pointer to the Tiles structure
*/
struct Tiles *createTiles ( void );



/**
* Frees memory from the heap of a previously allocated Tiles (collection) structure.
*
* \param tiles: A pointer to an Tiles structure
* \returns No return value (void)
*/
void destroyTiles ( struct Tiles *tiles );



/**
* Loads a binary file and stores its contents into a Tiles structure.
*
* \param tiles: A pointer to an Tiles structure
* \param filename: The name of the binary file to open
* \returns No return value (void)
*/
void loadTileDataIntoTiles ( struct Tiles *tiles, char *filename );



#endif
