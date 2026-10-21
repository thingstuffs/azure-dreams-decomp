#ifndef OVMOVIE_MOVIE_FRAME_PLAYBACK_G00427_H
#define OVMOVIE_MOVIE_FRAME_PLAYBACK_G00427_H
/* Movie frame playback shared declarations (G00427). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00427 - CL:ovmovie/func_80040360, CL:ovmovie/func_800403EC, CL:ovmovie/func_80040690, CL:ovmovie/func_8004072C, CL:ovmovie/func_800408BC, CL:ovmovie/func_80040954, CL:ovmovie/func_80040ED8, PD:ovmovie/ovmovie_bin:801781D0. */

#include "../../src/ovmovie/modules/ovmovie_game.h"

/* Functions defined in this translation unit. */
s32 decode_next_movie_frame(void *buffer_state);
s32 poll_movie_frame_and_update_dimensions(u8 *display);
void wait_for_movie_strip_completion(MovieEntity *entity, s32 unused);
void start_movie_cd_stream_and_wait_ready(void *playback_state);
s32 play_movie_frames_with_skip_fade(s32 unused,s32 frame_limit,s32 stream,s32 mode);

#endif
