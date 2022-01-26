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



#ifndef FPS_H
#define FPS_H



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <SDL2/SDL.h>



#define FPS 60
#define FPS_AVG_COUNT 60
#define FPS_FRAME_DURATION ( float ) ( 1000.0f / ( float ) FPS )



/**
 * @brief Collects frame timing data and provides a mean FPS for count display.
 */
struct FramesPerSecond
{
        uint64_t performance_counter_start;
        uint64_t performance_counter_end;
        float elapsed_ms;
        float fps_data [ FPS_AVG_COUNT ];
        uint8_t fps_data_index;
        uint8_t average;
};



/**
 * @brief Initializes a frames per second data structure.
 * @param fps: A pointer to a FramesPerSecond data structure
 * @returns Nothing
 */
void FPS_init ( struct FramesPerSecond *fps_struct );



/**
 * @brief Starts performance counter from a frames per second data structure.
 * @param fps: A pointer to a FramesPerSecond data structure
 * @returns Nothing
 */
void FPS_start ( struct FramesPerSecond *fps_struct );



/**
 * @brief Gets elapsed time and spins idle until FPS cap is met. Updates the FPS counter data.
 * @param fps: A pointer to a FramesPerSecond data structure
 * @returns Nothing
 */
void FPS_end ( struct FramesPerSecond *fps_struct );



#endif