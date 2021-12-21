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



#ifndef VIDEOMAP_H
#define VIDEOMAP_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "tile.h"



struct VideoMap
{
	uint16_t *data;
	uint16_t w;
	uint16_t h;
	uint32_t a;
};



/**
* Allocates memory on the heap for a VideoMap structure.
*
* \param w: width (in tiles)
* \param h: height (in tiles)
* \returns A pointer to the VideoMap structure
*/
struct VideoMap *createVideoMap ( uint16_t w, uint16_t h );



/**
* Frees memory from the heap of a previously allocated VideoMap structure.
*
* \param videomap: A pointer to an VideoMap structure
* \returns No return value (void)
*/
void destroyVideoMap ( struct VideoMap *videomap );



/**
* Copies character string to the videomap using tiles.
*
* \param videomap: A pointer to an VideoMap structure
* \param message: A pointer to a character string
* \param message_length: The length of the character string
* \param x: A horizontal tile position on the video map
* \param y: A vertical tile position on the video map
* \param ascii_start_tile_id: The tile index that corellates to the start or the ASCII order
* \returns No return value (void)
*/
void putStringOnVideoMap ( struct VideoMap *videomap, const char *message, uint8_t message_length, uint16_t x, uint16_t y, uint16_t ascii_start_tile_id );



/**
* Converts an integer to a string string and copies the string to the videomap using tiles.
*
* \param videomap: A pointer to an VideoMap structure
* \param value: A 32-bit unsigned integer
* \param padding: The number of tiles to padd the displayed number to
* \param x: A horizontal tile position on the video map
* \param y: A vertical tile position on the video map
* \param ascii_start_tile_id: The tile index that corellates to the start or the ASCII order
* \param padding_tile_id: The tile index to be used for the padding character
* \returns No return value (void)
*/
void putIntOnVideoMap ( struct VideoMap *videomap, uint32_t value, uint8_t padding, uint16_t x, uint16_t y, uint16_t ascii_start_tile_id, uint16_t padding_tile_id );



/**
* Gets the tile index value stored in a video map cell location.
*
* \param videomap: A pointer to an VideoMap structure
* \param x: A horizontal tile position on the video map
* \param y: A vertical tile position on the video map
* \returns The tile index value stored in the video map cell
*/
uint16_t getVideoMapTile ( struct VideoMap *videomap, uint16_t x, uint16_t y );



/**
* Sets the tile index value stored in a video map cell location.
*
* \param videomap: A pointer to an VideoMap structure
* \param tile_id: The tile index to store
* \param x: A horizontal tile position on the video map
* \param y: A vertical tile position on the video map
* \returns No return value (void)
*/
void setVideoMapTile ( struct VideoMap *videomap, uint16_t tile_id, uint16_t x, uint16_t y );



/**
* Sets all the the tile index values stored in all the video map cell locations.
*
* \param videomap: A pointer to an VideoMap structure
* \param tile_id: The tile index to store
* \returns No return value (void)
*/
void setAllVideoMapTiles ( struct VideoMap *videomap, uint16_t tile_id );



/**
* Sets all the the tile index values stored in a single row the video map row.
*
* \param videomap: A pointer to an VideoMap structure
* \param tile_id: The tile index to store
* \param row: The vertical row to set
* \returns No return value (void)
*/
void setVideoMapRowTiles ( struct VideoMap *videomap, uint16_t tile_id, uint16_t row );



/**
* Sets all the the tile index values stored in a single column the video map row.
*
* \param videomap: A pointer to an VideoMap structure
* \param tile_id: The tile index to store
* \param column: The horizontal column to set
* \returns No return value (void)
*/
void setVideoMapColumnTiles ( struct VideoMap *videomap, uint16_t tile_id, uint16_t column );



#endif
