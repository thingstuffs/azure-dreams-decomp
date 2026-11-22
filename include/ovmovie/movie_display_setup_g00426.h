#ifndef OVMOVIE_MOVIE_DISPLAY_SETUP_G00426_H
#define OVMOVIE_MOVIE_DISPLAY_SETUP_G00426_H
/* Movie display setup shared declarations. */

#include "../../src/ovmovie/modules/ovmovie_game.h"

/* Functions defined in this translation unit. */
void play_selected_movie_and_restore_display(void);
void clear_movie_display_area(s32 useFullHeight);
void set_movie_strip_offsets(s16 value_d8, s16 value_dc);
void initialize_movie_decoder_and_start_stream(void *playback_state, void (*playback_option)(void));
void initialize_movie_frame_buffers(MovieBuffer *movie, s32 frame_x, s32 frame_y, s32 next_frame_x, s32 next_frame_y);
void upload_movie_strip_and_advance_buffer(void);

#endif
