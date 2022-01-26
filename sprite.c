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



#include "sprite.h"



struct Sprite *createSprite ( uint8_t w, uint8_t h, ... )
{
        uint16_t i;
        uint16_t a;
        uint16_t *data;
        va_list args;
        struct Sprite *sprite;



        if ( ( w == 0 ) || ( h == 0 ) || ( w > 32 ) || ( h > 32 ) )
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

        sprite = NULL;
        sprite = malloc ( sizeof ( struct Sprite ) );
        if ( sprite == NULL )
        {
                free ( data );
                return NULL;
        }

        va_start ( args, h );
        for ( i = 0; i < a; i++ )
        {
                data [ i ] = va_arg ( args, int32_t );
        }
        va_end ( args );

        sprite->data = data;
        sprite->w = w;
        sprite->h = h;
        sprite->a = a;

        return sprite;
}



void destroySprite ( struct Sprite *sprite )
{
        if ( sprite == NULL )
        {
                return;
        }

        if ( sprite->data != NULL )
        {
                free ( sprite->data );
        }

        free ( sprite );
}



uint16_t getTileIdFromSprite ( struct Sprite *sprite, uint8_t row, uint8_t column )
{
        if ( ( sprite == NULL ) || ( row >= sprite->h ) || ( column >= sprite->w ) )
        {
                return 0;
        }

        return ( sprite->data [ ( row * sprite->w ) + column ] );
}



struct Sprites *createSprites ( void )
{
        uint16_t i;
        struct Sprites *sprites;
        struct Sprite **data;



        data = NULL;
        data = malloc ( sizeof ( struct Sprite * ) * MAXIMUM_NUMBER_OF_SPRITES );
        if ( data == NULL )
        {
                return NULL;
        }

        sprites = NULL;
        sprites = malloc ( sizeof ( struct Sprites ) );
        if ( sprites == NULL )
        {
                free ( data );
                return NULL;
        }

        for ( i = 0; i < MAXIMUM_NUMBER_OF_SPRITES; i++ )
        {
                data [ i ] = NULL;
        }

        sprites->data = data;
        sprites->count = 0;

        return sprites;
}



void destroySprites ( struct Sprites *sprites )
{
        uint16_t i;



        if ( sprites == NULL )
        {
                return;
        }

        for ( i = 0; i < sprites->count; i++ )
        {
                destroySprite ( sprites->data [ i ] );
        }
        free ( sprites->data );
        free ( sprites );
}



void addSpriteToSprites ( struct Sprites *sprites, struct Sprite *sprite )
{
        if ( ( sprites == NULL ) || ( sprites->count == MAXIMUM_NUMBER_OF_SPRITES ) )
        {
                return;
        }

        sprites->data [ sprites->count ] = sprite;
        sprites->count += 1;
}



struct SpriteBatch *createSpriteBatch ( )
{
        struct SpriteBatch *spritebatch;


        spritebatch = NULL;
        spritebatch = malloc ( sizeof ( struct SpriteBatch ) );
        if ( spritebatch == NULL )
        {
                return NULL;
        }

        clearSpriteBatch ( spritebatch );

        return spritebatch;
}



void destroySpriteBatch ( struct SpriteBatch *spritebatch )
{
        if ( spritebatch == NULL )
        {
                return;
        }

        free ( spritebatch );
}



void clearSpriteBatch ( struct SpriteBatch *spritebatch )
{
        uint16_t i;



        for ( i = 0; i < MAXIMUM_NUMBER_OF_SPRITES; i++ )
        {
                spritebatch->sprite_id [ i ] = -1;
                spritebatch->x  [ i ] = 0;
                spritebatch->y [ i ] = 0;
                spritebatch->fgr [ i ] = 1;
                spritebatch->bgr [ i ] = -1;
        }
        spritebatch->count = 0;
}



void addSpriteToSpriteBatch ( struct SpriteBatch *spritebatch, uint16_t sprite_id, int16_t x, int16_t y, int8_t fgr, int8_t bgr )
{
        if ( spritebatch->count >= ( MAXIMUM_NUMBER_OF_SPRITES - 1 ) )
        {
                return;
        }

        spritebatch->sprite_id [ spritebatch->count ] = sprite_id;
        spritebatch->x [ spritebatch->count ] = x;
        spritebatch->y [ spritebatch->count ] = y;
        if ( fgr > 0 )
        {
                fgr = 1;
        }
        else
        {
                fgr = -1;
        }
        spritebatch->fgr [ spritebatch->count ] = fgr;
        if ( bgr > 0 )
        {
                bgr = 1;
        }
        else
        {
                bgr = -1;
        }
        spritebatch->bgr [ spritebatch->count ] = bgr;

        spritebatch->count++;

}