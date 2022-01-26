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



#include "graphics.h"



struct Graphics *createGraphics ( void )
{
	uint8_t i;
	struct Graphics *graphics;
	uint32_t r_mask;
	uint32_t g_mask;
	uint32_t b_mask;
	uint32_t a_mask;
	uint32_t icon_transparent_color_key;
	SDL_Surface *icon;



	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		r_mask = 0xff000000;
		g_mask = 0x00ff0000;
		b_mask = 0x0000ff00;
		a_mask = 0x000000ff;
	#else
		r_mask = 0x000000ff;
		g_mask = 0x0000ff00;
		b_mask = 0x00ff0000;
		a_mask = 0xff000000;
	#endif

	/* allocate graphics struct onto the heap */
	graphics = NULL;
	graphics = malloc ( sizeof ( struct Graphics ) );
	if ( graphics == NULL )
	{
		printf ( "Graphics structure memory could not be allocated onto the heap. Graphics structure not created.\n" );
		return NULL;
	}

	/* create window, renderer, mix surface, and stream texture */
	graphics->scaler = getScale ( );
	if ( SDL_CreateWindowAndRenderer ( RENDER_W * graphics->scaler, RENDER_H * graphics->scaler, SDL_WINDOW_SHOWN, &graphics->window, &graphics->renderer ) < 0 )
	{
		printf ( "%s\n", SDL_GetError ( ) );
	}
	else
	{
		SDL_SetHint ( SDL_HINT_RENDER_SCALE_QUALITY, "0" );
		SDL_RenderSetLogicalSize ( graphics->renderer, RENDER_W, RENDER_H );
		SDL_SetRenderDrawBlendMode ( graphics->renderer, SDL_BLENDMODE_NONE );

		/* create window icon */
		icon = SDL_LoadBMP ( "icon.bmp" );
		icon_transparent_color_key = SDL_MapRGBA ( icon->format, 0x00, 0xff, 0xff, 0xff );
		SDL_SetColorKey ( icon, SDL_TRUE, icon_transparent_color_key );
		SDL_SetWindowIcon ( graphics->window, icon );
		SDL_FreeSurface ( icon );

		/* create scaled surface for screenshots */
		graphics->scaled_surface = SDL_CreateRGBSurface ( 0, RENDER_W * graphics->scaler, RENDER_H * graphics->scaler, 32, r_mask, g_mask, b_mask, a_mask );

		/* create mix surface and stream texture */
		graphics->surface = SDL_CreateRGBSurface ( 0, RENDER_W, RENDER_H, 32, r_mask, g_mask, b_mask, a_mask );
		graphics->texture = SDL_CreateTexture ( graphics->renderer, graphics->surface->format->format, SDL_TEXTUREACCESS_STREAMING, RENDER_W, RENDER_H );
		SDL_SetWindowTitle ( graphics->window, "Mouse Game" );
	}

	/* create and initialize palette */
	graphics->palette = 0;
	for ( i = 0; i < NUMBER_OF_PALETTES; i++ )
	{
		graphics->palettes [ i ] = SDL_AllocPalette ( 2 );
	}
	initializePalettes ( graphics->palettes );

	return graphics;
}



void destroyGraphics ( struct Graphics *graphics )
{
	uint8_t i;



	/* free SDL data structures */
	SDL_FreeSurface ( graphics->scaled_surface );
	SDL_FreeSurface ( graphics->surface );
	SDL_DestroyTexture ( graphics->texture );
	SDL_DestroyWindow ( graphics->window );
	SDL_DestroyRenderer ( graphics->renderer );
	for ( i = 0; i < NUMBER_OF_PALETTES; i++ )
	{
		SDL_FreePalette ( graphics->palettes [ i ] );
	}

}



void renderGame ( struct Game *game )
{
	uint32_t *s_pixels;



	/* set pointer to surface pixel data ( READ ) */
	s_pixels = ( uint32_t * ) game->graphics->surface->pixels;

	/* set background color */
	SDL_SetRenderDrawColor (
		game->graphics->renderer,
		game->graphics->palettes [ game->graphics->palette ]->colors [ 0 ].r,
		game->graphics->palettes [ game->graphics->palette ]->colors [ 0 ].g,
		game->graphics->palettes [ game->graphics->palette ]->colors [ 0 ].b,
		game->graphics->palettes [ game->graphics->palette ]->colors [ 0 ].a
	);
	
	/* clear renderer */
	SDL_RenderClear ( game->graphics->renderer );

	/* render videomap */
	renderVideoMapToSurface ( game );

	/* render spritebatch */
	renderSpriteBatchToSurface ( game );



	/* copy surface to texture */
	SDL_UpdateTexture ( game->graphics->texture, NULL, s_pixels, RENDER_W * sizeof ( uint32_t ) );

	/* copy texture to renderer */
	SDL_RenderCopy ( game->graphics->renderer, game->graphics->texture, NULL, NULL );

	/* present renderer */
	SDL_RenderPresent ( game->graphics->renderer );
}



void initializePalettes ( SDL_Palette **palettes )
{
	/* Palette 0: BLACK AND WHITE ( MAIN ) */
	palettes [ 0 ]->colors [ 0 ].r = 0x11;
	palettes [ 0 ]->colors [ 0 ].g = 0x11;
	palettes [ 0 ]->colors [ 0 ].b = 0x11;
	palettes [ 0 ]->colors [ 0 ].a = 0xff;
	palettes [ 0 ]->colors [ 1 ].r = 0xef;
	palettes [ 0 ]->colors [ 1 ].g = 0xef;
	palettes [ 0 ]->colors [ 1 ].b = 0xef;
	palettes [ 0 ]->colors [ 1 ].a = 0xff;


	/* Palette 1 */
	palettes [ 1 ]->colors [ 0 ].r = 0x42;
	palettes [ 1 ]->colors [ 0 ].g = 0x61;
	palettes [ 1 ]->colors [ 0 ].b = 0x36;
	palettes [ 1 ]->colors [ 0 ].a = 0xff;
	palettes [ 1 ]->colors [ 1 ].r = 0xce;
	palettes [ 1 ]->colors [ 1 ].g = 0xe6;
	palettes [ 1 ]->colors [ 1 ].b = 0xc5;
	palettes [ 1 ]->colors [ 1 ].a = 0xff;


	/* Palette 2 */
	palettes [ 2 ]->colors [ 0 ].r = 0xad;
	palettes [ 2 ]->colors [ 0 ].g = 0x5e;
	palettes [ 2 ]->colors [ 0 ].b = 0x8c;
	palettes [ 2 ]->colors [ 0 ].a = 0xff;
	palettes [ 2 ]->colors [ 1 ].r = 0xe6;
	palettes [ 2 ]->colors [ 1 ].g = 0xc1;
	palettes [ 2 ]->colors [ 1 ].b = 0xd6;
	palettes [ 2 ]->colors [ 1 ].a = 0xff;


	/* Palette 3 */
	palettes [ 3 ]->colors [ 0 ].r = 0x82;
	palettes [ 3 ]->colors [ 0 ].g = 0x4d;
	palettes [ 3 ]->colors [ 0 ].b = 0x67;
	palettes [ 3 ]->colors [ 0 ].a = 0xff;
	palettes [ 3 ]->colors [ 1 ].r = 0xee;
	palettes [ 3 ]->colors [ 1 ].g = 0xd2;
	palettes [ 3 ]->colors [ 1 ].b = 0xbc;
	palettes [ 3 ]->colors [ 1 ].a = 0xff;


	/* Palette 4 */
	palettes [ 4 ]->colors [ 0 ].r = 0x86;
	palettes [ 4 ]->colors [ 0 ].g = 0x76;
	palettes [ 4 ]->colors [ 0 ].b = 0x66;
	palettes [ 4 ]->colors [ 0 ].a = 0xff;
	palettes [ 4 ]->colors [ 1 ].r = 0xea;
	palettes [ 4 ]->colors [ 1 ].g = 0xe2;
	palettes [ 4 ]->colors [ 1 ].b = 0xd6;
	palettes [ 4 ]->colors [ 1 ].a = 0xff;


	/* Palette 5 */
	palettes [ 5 ]->colors [ 0 ].r = 0x2c;
	palettes [ 5 ]->colors [ 0 ].g = 0x4a;
	palettes [ 5 ]->colors [ 0 ].b = 0x52;
	palettes [ 5 ]->colors [ 0 ].a = 0xff;
	palettes [ 5 ]->colors [ 1 ].r = 0xf4;
	palettes [ 5 ]->colors [ 1 ].g = 0xeb;
	palettes [ 5 ]->colors [ 1 ].b = 0xdb;
	palettes [ 5 ]->colors [ 1 ].a = 0xff;


	/* Palette 6 */
	palettes [ 6 ]->colors [ 0 ].r = 0x52;
	palettes [ 6 ]->colors [ 0 ].g = 0x36;
	palettes [ 6 ]->colors [ 0 ].b = 0x34;
	palettes [ 6 ]->colors [ 0 ].a = 0xff;
	palettes [ 6 ]->colors [ 1 ].r = 0xdd;
	palettes [ 6 ]->colors [ 1 ].g = 0xc5;
	palettes [ 6 ]->colors [ 1 ].b = 0xa2;
	palettes [ 6 ]->colors [ 1 ].a = 0xff;


	/* Palette 7 */
	palettes [ 7 ]->colors [ 0 ].r = 0x53;
	palettes [ 7 ]->colors [ 0 ].g = 0x65;
	palettes [ 7 ]->colors [ 0 ].b = 0xb5;
	palettes [ 7 ]->colors [ 0 ].a = 0xff;
	palettes [ 7 ]->colors [ 1 ].r = 0x6b;
	palettes [ 7 ]->colors [ 1 ].g = 0xb1;
	palettes [ 7 ]->colors [ 1 ].b = 0xe1;
	palettes [ 7 ]->colors [ 1 ].a = 0xff;


	/* Palette 8 */
	palettes [ 8 ]->colors [ 0 ].r = 0xfa;
	palettes [ 8 ]->colors [ 0 ].g = 0x81;
	palettes [ 8 ]->colors [ 0 ].b = 0x2f;
	palettes [ 8 ]->colors [ 0 ].a = 0xff;
	palettes [ 8 ]->colors [ 1 ].r = 0xfe;
	palettes [ 8 ]->colors [ 1 ].g = 0xf3;
	palettes [ 8 ]->colors [ 1 ].b = 0xe2;
	palettes [ 8 ]->colors [ 1 ].a = 0xff;


	/* Palette 9 */
	palettes [ 9 ]->colors [ 0 ].r = 0x1e;
	palettes [ 9 ]->colors [ 0 ].g = 0x43;
	palettes [ 9 ]->colors [ 0 ].b = 0x4c;
	palettes [ 9 ]->colors [ 0 ].a = 0xff;
	palettes [ 9 ]->colors [ 1 ].r = 0xc9;
	palettes [ 9 ]->colors [ 1 ].g = 0x9e;
	palettes [ 9 ]->colors [ 1 ].b = 0x10;
	palettes [ 9 ]->colors [ 1 ].a = 0xff;


	/* Palette 10 */
	palettes [ 10 ]->colors [ 0 ].r = 0x19;
	palettes [ 10 ]->colors [ 0 ].g = 0x95;
	palettes [ 10 ]->colors [ 0 ].b = 0xad;
	palettes [ 10 ]->colors [ 0 ].a = 0xff;
	palettes [ 10 ]->colors [ 1 ].r = 0xf1;
	palettes [ 10 ]->colors [ 1 ].g = 0xf1;
	palettes [ 10 ]->colors [ 1 ].b = 0xf2;
	palettes [ 10 ]->colors [ 1 ].a = 0xff;


	/* Palette 11 */
	palettes [ 11 ]->colors [ 0 ].r = 0x5d;
	palettes [ 11 ]->colors [ 0 ].g = 0x53;
	palettes [ 11 ]->colors [ 0 ].b = 0x5e;
	palettes [ 11 ]->colors [ 0 ].a = 0xff;
	palettes [ 11 ]->colors [ 1 ].r = 0xec;
	palettes [ 11 ]->colors [ 1 ].g = 0x96;
	palettes [ 11 ]->colors [ 1 ].b = 0xa4;
	palettes [ 11 ]->colors [ 1 ].a = 0xff;


	/* Palette 12 */
	palettes [ 12 ]->colors [ 0 ].r = 0xa1;
	palettes [ 12 ]->colors [ 0 ].g = 0x1f;
	palettes [ 12 ]->colors [ 0 ].b = 0x0c;
	palettes [ 12 ]->colors [ 0 ].a = 0xff;
	palettes [ 12 ]->colors [ 1 ].r = 0xf4;
	palettes [ 12 ]->colors [ 1 ].g = 0xec;
	palettes [ 12 ]->colors [ 1 ].b = 0x6a;
	palettes [ 12 ]->colors [ 1 ].a = 0xff;


	/* Palette 13 */
	palettes [ 13 ]->colors [ 0 ].r = 0x2c;
	palettes [ 13 ]->colors [ 0 ].g = 0x4a;
	palettes [ 13 ]->colors [ 0 ].b = 0x52;
	palettes [ 13 ]->colors [ 0 ].a = 0xff;
	palettes [ 13 ]->colors [ 1 ].r = 0x8e;
	palettes [ 13 ]->colors [ 1 ].g = 0x9b;
	palettes [ 13 ]->colors [ 1 ].b = 0x97;
	palettes [ 13 ]->colors [ 1 ].a = 0xff;


	/* Palette 14 */
	palettes [ 14 ]->colors [ 0 ].r = 0xaf;
	palettes [ 14 ]->colors [ 0 ].g = 0x1c;
	palettes [ 14 ]->colors [ 0 ].b = 0x1c;
	palettes [ 14 ]->colors [ 0 ].a = 0xff;
	palettes [ 14 ]->colors [ 1 ].r = 0x31;
	palettes [ 14 ]->colors [ 1 ].g = 0xa2;
	palettes [ 14 ]->colors [ 1 ].b = 0xac;
	palettes [ 14 ]->colors [ 1 ].a = 0xff;


	/* Palette 15 */
	palettes [ 15 ]->colors [ 0 ].r = 0x28;
	palettes [ 15 ]->colors [ 0 ].g = 0x36;
	palettes [ 15 ]->colors [ 0 ].b = 0x55;
	palettes [ 15 ]->colors [ 0 ].a = 0xff;
	palettes [ 15 ]->colors [ 1 ].r = 0xd0;
	palettes [ 15 ]->colors [ 1 ].g = 0xe1;
	palettes [ 15 ]->colors [ 1 ].b = 0xf9;
	palettes [ 15 ]->colors [ 1 ].a = 0xff;
}



void renderTileToSurface ( struct Game *game, uint16_t tile_id, int16_t x, int16_t y, int8_t foreground_render, int8_t background_render )
{
	uint8_t bit;
	uint8_t px;
	uint8_t py;
	uint32_t *s_pixels;



	/* set pointer to surface pixel data ( WRITE ) */
	s_pixels = ( uint32_t * ) game->graphics->surface->pixels;

	/* render tile */
	for ( py = 0; py < 8; py++ )
	{
		for ( px = 0; px < 8; px++ )
		{
			bit = getTilePatternBit ( game->tiles->data [ tile_id ], py, ( 7 - px ) );

			if ( bit == 0 )
			{
				if ( background_render > -1 )  
				{
					s_pixels [ ( ( ( y + py ) * game->graphics->surface->w ) + ( x + px ) ) ] =
						SDL_MapRGBA
						(
							game->graphics->surface->format,
							game->graphics->palettes [ game->graphics->palette ]->colors [ 0 ].r,
							game->graphics->palettes [ game->graphics->palette ]->colors [ 0 ].g,
							game->graphics->palettes [ game->graphics->palette ]->colors [ 0 ].b,
							game->graphics->palettes [ game->graphics->palette ]->colors [ 0 ].a
						);
				}
			}
			else
			{
				if ( foreground_render > -1 )
				{
					s_pixels [ ( ( ( y + py ) * game->graphics->surface->w ) + ( x + px ) ) ] =
						SDL_MapRGBA
						(
							game->graphics->surface->format,
							game->graphics->palettes [ game->graphics->palette ]->colors [ 1 ].r,
							game->graphics->palettes [ game->graphics->palette ]->colors [ 1 ].g,
							game->graphics->palettes [ game->graphics->palette ]->colors [ 1 ].b,
							game->graphics->palettes [ game->graphics->palette ]->colors [ 1 ].a
						);
				}
			}
		}
	}
}



void renderVideoMapToSurface ( struct Game *game )
{
	uint16_t c;
	uint16_t r;



	for ( r = 0; r < game->videomap->h; r++ )
	{
		for ( c = 0; c < game->videomap->w; c++ )
		{
			renderTileToSurface ( game, getVideoMapTile ( game->videomap, c, r ), ( c * 8 ), ( r * 8 ), 1, 1 );
		}
	}
}



void renderSpriteToSurface ( struct Game *game, int16_t sprite_id, int16_t x, int16_t y, int8_t foreground_render, int8_t background_render )
{
	{
		int16_t r;
		int16_t c;
		uint16_t tile_id;
		uint16_t w;
		uint16_t h;



		w = game->sprites->data [ sprite_id ]->w;
		h = game->sprites->data [ sprite_id ]->h;

		for ( r = 0; r < h; r++ )
		{
			for ( c = 0; c < w; c++ )
			{
				tile_id = game->sprites->data [ sprite_id ]->data [ ( r * w ) + c ];

				renderTileToSurface
				(
					game, 
					tile_id,
					( c * 8 ) + x,
					( r * 8 ) + y,
					foreground_render,
					background_render
				);
			}
		}
	}
}




void renderSpriteBatchToSurface ( struct Game *game )
{
	uint16_t i;



	for ( i = 0; i < game->spritebatch->count; i++ )
	{
		renderSpriteToSurface
		(
			game,
			game->spritebatch->sprite_id [ i ],
			game->spritebatch->x [ i ],
			game->spritebatch->y [ i ],
			game->spritebatch->fgr [ i ],
			game->spritebatch->bgr [ i ]
		);
	}

	clearSpriteBatch ( game->spritebatch );
}



uint16_t getScale ( )
{
	uint16_t s;
	SDL_DisplayMode mode;



	if ( SDL_GetCurrentDisplayMode ( 0, &mode ) < 0 )
	{
		/* cannot get display mode information, return 2x scaler by default */
		printf ( "Could not get video display information. Default scale set to 2X.\n" );
		return 2;
	}

	s = ( uint16_t ) floor ( mode.h / RENDER_H ) - 1;
	printf ( "Display vertical resolution: %d.\n", mode.h );
	printf ( "Default scale set to %dX.\n", s );
	return s;
}



void screenShot ( struct Graphics *graphics )
{
	time_t rawtime;
	struct tm *time_information;
	char filename [ 30 ];
	


	SDL_BlitScaled ( graphics->surface, NULL, graphics->scaled_surface, NULL );
	time ( &rawtime );
	time_information = localtime ( &rawtime );
	strftime ( filename, 30, "mousegame_%Y%m%d-%H%M%S.bmp", time_information );
	SDL_SaveBMP ( graphics->scaled_surface, filename );
}
