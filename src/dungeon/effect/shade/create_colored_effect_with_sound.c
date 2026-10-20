#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct Rec_func_800D4BD4_arg2 Rec_func_800D4BD4_arg2;

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;

extern void func_8003DB94(void *, void *, s32);
extern void play_sound_if_enabled(s32);
void emit_particles_until_expired(void *emitter, Rec_func_800D4BD4_arg2 *position, s32 init_param);
extern M2C_UNK D_800DECF8[3];
/* Creates a colored effect at the source position and optionally plays a sound. */
void create_colored_effect_with_sound(void *source, s32 color, unsigned short sound_id)
{
    DungeonGlobalStatus *effect_state;
    s32 *color_ptr;
    s32 sound;
    s32 packed_color;
    SpriteFrameState *render_flags;
    SpriteFrameState *render_data;
    void *effect_data;
    void *sprite_data;
    void *effect;
    void *position;
    color_ptr = &color;
    effect = func_8003FC64(0x12);
    if (effect != 0) {
        effect_data = effect + 0x20;
        *((void **) (((u8 *) effect_data) + 0x24)) = source;
        *((s32 **) (((u8 *) effect) + 0x10)) = &emit_particles_until_expired;
        *((s16 *) (((u8 *) effect_data) + 0x1E)) = 0x1E;
        render_flags = *((void **) (((u8 *) effect) + 0xC));
        render_flags->tpage_abr = 0x20;
        render_flags->flags = (u16) (render_flags->flags | 0xC);
        position = *((void **) (((u8 *) effect) + 8));
        *((u16 *) (((u8 *) position) + 2)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2)));
        *((u16 *) (((u8 *) position) + 6)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6)));
        *((u16 *) (((u8 *) position) + 0xA)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA)));
        render_data = *((void **) (((u8 *) effect) + 0xC));
        render_data->color.c.b = 0x80;
        render_data->color.c.g = 0x80;
        render_data->color.c.r = 0x80;
        packed_color = *color_ptr;
        render_data->scale_y = ONE;
        render_data->scale_x = ONE;
        render_data->color.word = packed_color;
        *((s32 *) (((u8 *) effect_data) + 0xC)) = packed_color;
        render_data->clut = 0x7DCE;
        sprite_data = D_800DECF8;
        render_data->flags = (u16) (render_data->flags | 0x100);
        func_8003DB94(render_data, sprite_data, 0);
        sound = sound_id & 0xFFFF;
        if (sound != 0) {
            play_sound_if_enabled(sound);
        }
        effect_state = &g_dungeon_status;
        *((u16 *) (((u8 *) effect_state) + 0xA)) = (u16) ((*((u16 *) (((u8 *) effect_state) + 0xA))) + 1);
    }
}
