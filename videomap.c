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



#include "videomap.h"



struct VideoMap *createVideoMap ( uint16_t w, uint16_t h )
{
        uint32_t a;
        uint16_t *data;
        struct VideoMap *videomap;



        if ( ( w == 0 ) || ( h == 0 ) )
        {
                return NULL;
        }

        a = w * h;
        data = NULL;
        data = malloc ( sizeof ( uint16_t ) * a );
        if ( data == NULL )
        {
                return NULL;
        }

        videomap = NULL;
        videomap = malloc ( sizeof ( struct VideoMap ) );
        if ( videomap == NULL )
        {
                free ( data );
                return NULL;
        }

        videomap->data = data;
        videomap->w = w;
        videomap->h = h;
        videomap->a = a;

        setAllVideoMapTiles ( videomap, 0 );

        return videomap;
}



void destroyVideoMap ( struct VideoMap *videomap )
{
        if ( videomap == NULL )
        {
                return;
        }

        if ( videomap->data != NULL )
        {
                free ( videomap->data );
        }

        free ( videomap );
}



void putStringOnVideoMap ( struct VideoMap *videomap, const char *message, uint8_t message_length, uint16_t x, uint16_t y, uint16_t ascii_start_tile_id )
{
        uint8_t i;
        uint16_t tile_id;



        if ( ( videomap == NULL ) || ( x >= videomap->w ) || ( y >= videomap->h ) )
        {
                return;
        }


        /* display loop */
        for ( i = 0; i < message_length; i++ )
        {
                tile_id = ( uint16_t ) ( message [ i ] - 32 ) + ascii_start_tile_id;
                setVideoMapTile ( videomap, tile_id, x, y );
                x++;

                /* handle wrapping */
                if ( x == videomap->w )
                {
                        x = 0;
                        y++;
                        if ( y == videomap->h )
                        {
                                y = 0;
                        }
                }
        }
}



void putIntOnVideoMap ( struct VideoMap *videomap, uint32_t value, uint8_t padding, uint16_t x, uint16_t y, uint16_t ascii_start_tile_id, uint16_t padding_tile_id )
{
        char c_value [ 10 ];
        uint8_t length;
        uint8_t i;



        if ( videomap == NULL )
        {
                return;
        }

        /* clear buffers */
        for ( i = 0; i < 10; i++ )
        {
                c_value [ i ] = '\0';
        }

        /* convert to string and get size */
        snprintf ( c_value, 10, "%d", value );
        length = 0;
        i = 0;
        while ( ( i == 0 ) && ( length < 10 ) )
        {
                if ( c_value [ length ] == '\0' )
                {
                        /* break while loop early */
                        i = 1;
                }
                else
                {
                        length++;
                }
        }

        /* render padding */
        if ( padding > length )
        {
                for ( i = 0; i < ( padding - length ); i++ )
                {
                        setVideoMapTile ( videomap, padding_tile_id, x, y );
                        x++;
                        /* handle wrapping */
                        if ( x == videomap->w )
                        {
                                x = 0;
                                y++;
                                if ( y == videomap->h )
                                {
                                        y = 0;
                                }
                        }
                }
        }
        /* render value */
        putStringOnVideoMap ( videomap, c_value, length, x, y, 0 );
}



uint16_t getVideoMapTile ( struct VideoMap *videomap, uint16_t x, uint16_t y )
{
        if ( ( videomap == NULL ) || ( x >= videomap->w ) || ( y >= videomap->h ) )
        {
                return 0;
        }

        return videomap->data [ ( videomap->w * y ) + x ];
}



void setVideoMapTile ( struct VideoMap *videomap, uint16_t tile_id, uint16_t x, uint16_t y )
{
        if ( ( videomap == NULL ) || ( x >= videomap->w ) || ( y >= videomap->h ) || ( tile_id >= MAXIMUM_NUMBER_OF_TILES ) )
        {
                return;
        }

        videomap->data [ ( videomap->w * y ) + x ] = tile_id;
}



void setAllVideoMapTiles ( struct VideoMap *videomap, uint16_t tile_id )
{
        uint32_t i;



        if ( ( videomap == NULL ) || ( tile_id >= MAXIMUM_NUMBER_OF_TILES ) )
        {
                return;
        }

        for ( i = 0; i < videomap->a; i++ )
        {
                videomap->data [ i ] = tile_id;
        }
}



void setVideoMapRowTiles ( struct VideoMap *videomap, uint16_t tile_id, uint16_t row )
{
        uint16_t i;



        if ( ( videomap == NULL ) || ( row >= videomap->h) || ( tile_id >= MAXIMUM_NUMBER_OF_TILES ) )
        {
                return;
        }

        for ( i = 0; i < videomap->w; i++ )
        {
                setVideoMapTile ( videomap, tile_id, i, row );
        }
}



void setVideoMapColumnTiles ( struct VideoMap *videomap, uint16_t tile_id, uint16_t column )
{
        uint16_t i;



        if ( ( videomap == NULL ) || ( column >= videomap->w ) || ( tile_id >= MAXIMUM_NUMBER_OF_TILES ) )
        {
                return;
        }

        for ( i = 0; i < videomap->h; i++ )
        {
                setVideoMapTile ( videomap, tile_id, column, i );
        }
}
