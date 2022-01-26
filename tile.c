/**

Mouse Game

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



#include "tile.h"



struct Tile *createTile ( void )
{
        struct Tile *tile;



        tile = NULL;
        tile = malloc ( sizeof ( struct Tile ) );
        if ( tile == NULL )
        {
                return NULL;
        }

        clearTile ( tile, 0x00 );

        return tile;
}



void destroyTile ( struct Tile *tile )
{
        if ( tile == NULL )
        {
                return;
        }

        free ( tile );
}



uint8_t getTilePattern ( struct Tile *tile, uint8_t row )
{
        if ( ( tile == NULL ) || ( row > 7 ) )
        {
                return 0;
        }

        return ( tile->patterns [ row ] );
}



void setTilePattern ( struct Tile *tile, uint8_t row, uint8_t pattern )
{
        if ( ( tile == NULL ) || ( row > 7 ) )
        {
                /* error code */
                return;
        }

        tile->patterns [ row ] = pattern;
}



uint8_t getTilePatternBit ( struct Tile *tile, uint8_t row, uint8_t bit_position )
{
        if ( ( tile == NULL ) || ( row > 7 ) || ( bit_position > 7 ) )
        {
                /* error code */
                return 0;
        }

        return ( ( getTilePattern ( tile, row ) >> bit_position ) & 0x01 );
}



void setTilePatternBit ( struct Tile *tile, uint8_t row, uint8_t bit_position, uint8_t bit_value )
{
        if ( ( tile == NULL ) || ( row > 7 ) || ( bit_position > 7 ) || ( bit_value > 1 ) )
        {
                /* error code */
                return;
        }

        if ( bit_value == 0 )
        {
                tile->patterns [ row ] &= ~( 0x01 << bit_position );
                return;
        }

        tile->patterns [ row ] |= ( 0x01 << bit_position );
}



void clearTile ( struct Tile *tile, uint8_t pattern )
{
        uint8_t i;



        if ( tile == NULL )
        {
                return;
        }

        for ( i = 0; i < 8; i++ )
        {
                tile->patterns [ i ] = pattern;
        }
}



void printTile ( struct Tile *tile )
{
        uint8_t r;
        uint8_t c;
        uint8_t bit;



        if ( tile == NULL )
        {
                /* error code */
                return;
        }

        for ( r = 0; r < 8; r++ )
        {
                for ( c = 0; c < 8; c++ )
                {
                        bit = getTilePatternBit ( tile, r, 7 - c );
                        printf ( "%d", bit );

                        if ( c < 7 )
                        {
                                printf ( " " );
                        }
                }
                printf ( "\n" );
        }
        printf ( "\n" );
}



struct Tiles *createTiles ( void )
{
        uint16_t i;
        struct Tiles *tiles;
        struct Tile **data;



        /* create array of Tile pointers */
        data = NULL;
        data = malloc ( sizeof ( struct Tile * ) * MAXIMUM_NUMBER_OF_TILES );
        if ( data == NULL )
        {
                return NULL;
        }

        /* create tiles container */
        tiles = NULL;
        tiles = malloc ( sizeof ( struct Tiles ) );
        if ( tiles == NULL )
        {
                free ( tiles );
                return NULL;
        }

        /* connect data */
        tiles->data = data;

        /* connect data pointers to heap allocated tiles */
        for ( i = 0; i < MAXIMUM_NUMBER_OF_TILES; i++ )
        {
                tiles->data [ i ] = createTile ( );
        }

        /* load data */
        loadTileDataIntoTiles ( tiles, FILENAME_TILE_DATA );

        return tiles;
}



void destroyTiles ( struct Tiles *tiles )
{
        uint16_t i;



        if ( tiles == NULL )
        {
                return;
        }

        for ( i = 0; i < MAXIMUM_NUMBER_OF_TILES; i++ )
        {
                destroyTile ( tiles->data [ i ] );
        }

        free ( tiles );
}



void loadTileDataIntoTiles ( struct Tiles *tiles, char *filename )
{
        uint8_t r;
        uint16_t i;
        FILE *file = NULL;



        if ( ( file = fopen ( filename, "rb" ) ) == NULL )
        {
                printf ( "Data file could not be opened.\n" );
                return;
        }

        printf ( "File opened.\n" );

        r = 0;
        i = 0;

        while ( ( i < MAXIMUM_NUMBER_OF_TILES ) && ( feof ( file ) != EOF ) )
        {
                setTilePattern ( tiles->data [ i ], r, ( uint8_t ) fgetc ( file ) );
                r++;
                if ( r == 8 )
                {
                        r = 0;
                        i++;
                }
        }

        fclose ( file );
        printf ( "File closed.\n" );
}