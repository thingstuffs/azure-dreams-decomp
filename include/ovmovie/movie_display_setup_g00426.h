#ifndef OVMOVIE_MOVIE_DISPLAY_SETUP_G00426_H
#define OVMOVIE_MOVIE_DISPLAY_SETUP_G00426_H
/* Movie display setup shared declarations (G00426). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00426 - CL:ovmovie/func_800402D8, CL:ovmovie/func_8004033C, CL:ovmovie/func_80040360, CL:ovmovie/func_800403EC, CL:ovmovie/func_80040954, CL:ovmovie/func_80040ED8, PD:ovmovie/ovmovie_bin:801781D8, PD:ovmovie/ovmovie_bin:80189390. */

#include "../../src/ovmovie/modules/ovmovie_game.h"

/* Functions defined in this translation unit. */
void play_selected_movie_and_restore_display(void);
void clear_movie_display_area(s32 useFullHeight);
void set_movie_strip_offsets(s16 value_d8, s16 value_dc);
void initialize_movie_decoder_and_start_stream(void *playback_state, void (*playback_option)(void));
void initialize_movie_frame_buffers(MovieBuffer *movie, s32 frame_x, s32 frame_y, s32 next_frame_x, s32 next_frame_y);
void upload_movie_strip_and_advance_buffer(void);

#endif
