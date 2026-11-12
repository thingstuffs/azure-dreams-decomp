#ifndef SLUS_GP_SHARED_SLOTS_H
#define SLUS_GP_SHARED_SLOTS_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "shared/runtime_dispatch.h"
#include "common.h"


extern void *g_game_work[3];
extern u16 scene_sprite_mode_word[5];
extern s16 scene_sprite_wave_tick;
extern u16 scene_sprite_cached_mode;
extern u16 scene_sprite_fade_ticks;
extern u8 scene_sprite_last_field;
extern s16 scene_sprite_x_history[64];
extern s16 scene_sprite_y_history[64];
extern void draw_sprite_list(void);
extern void func_8003D0F0(void);
extern void draw_cd_wait_sprite_trail(s32 layer);

static inline s32 shift10(s32 value)
{
    return value >> 10;
}

/* Swap draw buffers and update the animated coordinate history on a new display field. */


#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))


extern s16 scene_sprite_list_initialized;
extern void *scene_sprite_list_base;
extern s16 scene_sprite_wave_tick;
extern u16 scene_sprite_fade_ticks;
extern u8 scene_sprite_glyph_ids[14];
extern u8 scene_sprite_object_storage[];
extern s16 scene_sprite_x_history[64];
extern s16 scene_sprite_y_history[64];
extern void *g_game_work[3];

/* Draw fourteen sprites with interpolated positions and pulsing color. */

void render_cd_wait_animation_on_new_field(void);
void draw_cd_wait_sprite_trail(s32 blend_step);

#endif
