#ifndef OVMOVIE_GAME_MOVIE_PLAYBACK_G01063_H
#define OVMOVIE_GAME_MOVIE_PLAYBACK_G01063_H
/* Game movie playback and display lifecycle. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01063 - refs/tuweak1/split_plan.tsv:game_movie_playback. */

/* Movie display setup (G00426).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00426 - CL:ovmovie/func_800402D8, CL:ovmovie/func_8004033C, CL:ovmovie/func_80040360, CL:ovmovie/func_800403EC, CL:ovmovie/func_80040954, CL:ovmovie/func_80040ED8, PD:ovmovie/ovmovie_bin:801781D8, PD:ovmovie/ovmovie_bin:80189390.
 */
#include "ovmovie/movie_display_setup_g00426.h"
/* Movie frame playback (G00427).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00427 - CL:ovmovie/func_80040360, CL:ovmovie/func_800403EC, CL:ovmovie/func_80040690, CL:ovmovie/func_8004072C, CL:ovmovie/func_800408BC, CL:ovmovie/func_80040954, CL:ovmovie/func_80040ED8, PD:ovmovie/ovmovie_bin:801781D0.
 */
#include "ovmovie/movie_frame_playback_g00427.h"

/* Functions defined in this translation unit. */
void play_selected_movie_and_restore_display(void);
void clear_movie_display_area(s32 useFullHeight);
void set_movie_strip_offsets(s16 value_d8, s16 value_dc);
void initialize_movie_decoder_and_start_stream(void *playback_state, void (*playback_option)(void));
void initialize_movie_frame_buffers(MovieBuffer *movie, s32 frame_x, s32 frame_y, s32 next_frame_x, s32 next_frame_y);
void upload_movie_strip_and_advance_buffer(void);
s32 decode_next_movie_frame(void *buffer_state);
s32 poll_movie_frame_and_update_dimensions(u8 *display);
void wait_for_movie_strip_completion(MovieEntity *entity, s32 unused);
void start_movie_cd_stream_and_wait_ready(void *playback_state);
s32 play_movie_frames_with_skip_fade(s32 unused,s32 frame_limit,s32 stream,s32 mode);

#endif
