#ifndef OVMOVIE_GAME_H
#define OVMOVIE_GAME_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/runtime_dispatch.h"

typedef struct { s16 x, y, w, h; } MovieRect;
/* Playback work block. The buffer view below starts at byte 4. */
typedef struct {
    s32 tag;
    void *frame_buffers[2];
    s32 frame_buffer_index;
    void *output;
    MovieRect screen[2];
    s32 screen_index;
    MovieRect strip;
    s32 ready;
    s32 done;
    s32 width, height;
} MovieState;
/* Initializer's 0x30-byte view of MovieState + 4. */
typedef struct {
    void *unk00;
    void *unk04;
    s32 unk08;
    void *unk0C;
    s16 unk10, unk12, unk14, unk16;
    s16 unk18, unk1A, unk1C, unk1E;
    s32 unk20;
    s16 unk24, unk26, unk28, unk2A;
    s32 unk2C;
} MovieBuffer;
/* Waiter's unsigned halfword copy view of the same buffer subobject. */
typedef struct {
    u8 pad00[0x10];
    u16 unk10, unk12;
    u8 pad14[0x0C];
    s32 unk20;
    u16 unk24, unk26;
    u8 pad28[0x04];
    s32 unk2C;
} MovieEntity;
typedef struct { u8 pad00[8]; u32 frame; u8 pad0C[4]; u16 width, height; } FrameInfo;
typedef struct { u8 pad00[0x14]; s16 w0, h0; u8 pad18[4]; s16 w1, h1; u8 pad20[10]; s16 rounded_height; } FrameDisplay;
typedef struct { MovieRect viewport, screen; u8 interlaced, rgb24, pad[6]; } MovieDisplayEnv;
typedef struct { u8 bytes[96]; } MovieDrawEnv;

extern s8 scene_music_hold;
extern u8 scene_mode_code;
extern s32 D_80086D8C;
extern s32 movie_frame_number, movie_stop_frame, movie_strip_x_offset, movie_strip_y_offset, movie_rgb24_mode, D_801781E4;
extern u8 movie_cd_status[8];
extern MovieState *active_movie;
extern s32 movie_frame_control;
extern u8 movie_work_buffer[];
extern s32 movie_start_sector, movie_volume;
extern u8 upper_draw_context[];

extern s32 Control_CD(s32, s32, s32);
extern void func_8003F320(void);
#include "engine/scene.h"
extern void SD_Call(s32);
extern void drain_audio_commands_and_service_channels(void);
extern void func_8005A4E8(s32, s32, s32);
extern void func_8005A56C(s32, s16, s16);
extern void VSync(s32);
extern void func_80060B04(void *, s32);
extern void func_80060D90(s32, u8 *);
extern void func_80060DE8(s32);
extern void func_80061208(s32);
extern void func_8006124C(s32, void *);
#include "sdk/libcd.h"
extern s32 func_80063424(s32);
extern void func_80063538(void);
extern void func_800636AC(s32, s32, s32, s32, s32);
extern s32 func_80063734(s32);
extern s32 func_80063828(s32 *, FrameInfo **);
extern void func_8006390C(void);
extern void func_8006636C(void *, s32, s32, s32, s32);
extern void func_80066424(void *, s32, s32, s32, s32);
extern void SetDispMask(s32);
extern void DrawSync(s32);
extern void ClearImage(s16 *, s32, s32, s32);
extern void LoadImage(MovieRect *, void *);
extern void func_8006751C(void *, s32);
extern void func_80067688(void *);
extern void func_800678E0(void *);
/* LIBPRESS public entries; signatures agree with its shared header. */
extern void set_movie_decode_mode(s32);
extern void configure_decoder_command_flags(s32 *, s32);
extern void request_decoder_output_dma(s32, u32);
extern s32 register_mode_one_callback(void (*)(void));
/* The unregistered VLC routine is an external platform boundary. */
extern s32 func_80177E6C(s32, void *);

void play_selected_movie_and_restore_display(void);
void clear_movie_display_area(s32);
void set_movie_strip_offsets(s16, s16);
void initialize_movie_decoder_and_start_stream(void *, void (*)(void));
void initialize_movie_frame_buffers(MovieBuffer *, s32, s32, s32, s32);
void upload_movie_strip_and_advance_buffer(void);
s32 decode_next_movie_frame(void *);
s32 poll_movie_frame_and_update_dimensions(u8 *);
void wait_for_movie_strip_completion(MovieEntity *, s32);
void start_movie_cd_stream_and_wait_ready(void *);
s32 play_movie_frames_with_skip_fade(s32, s32, s32, s32);
#endif
