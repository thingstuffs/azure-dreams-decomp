#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80170D44_0_pre {
    u16 unk_00;
} S_80170D44_0_pre;   /* the 0x2 bytes before arg0 in expand_fade_effect_and_expire, addressed as arg0[-1] */

typedef struct S_80170D44_0 {
    u8 pad_00[0x96];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x10];
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
} S_80170D44_0;   /* arg0 in expand_fade_effect_and_expire */

   /* arg1 in expand_fade_effect_and_expire */

   /* src in expand_fade_effect_and_expire */

extern void advance_sprite_animation_and_textures(void *primitive);

/* Copy the effect position, expand and fade its primitive, and flag expiration. */
void expand_fade_effect_and_expire(void *effect, MovingPosition *position, SpriteFrameState *primitive)
{
    s16 ticks_left;
    s32 shade;
    u16 extent;
    MovingPosition *source_position;

    source_position = ((S_80170D44_0 *)effect)->unk_AC;
    position->x = source_position->x;
    position->y = source_position->y;
    position->z = source_position->z;

    extent = primitive->scale_y + 0x320;
    primitive->scale_y = extent;
    primitive->scale_x = extent;

    ticks_left = ((S_80170D44_0 *)effect)->unk_96.s - 1;
    shade = (s32)(ticks_left * 0x50) / (s16)((S_80170D44_0 *)effect)->unk_A8;
    ((S_80170D44_0 *)effect)->unk_96.s = (u16)ticks_left;
    primitive->color.c.b = (s8)shade;
    primitive->color.c.g = (s8)shade;
    primitive->color.c.r = (s8)shade;
    advance_sprite_animation_and_textures(primitive);

    if (((S_80170D44_0 *)effect)->unk_96.u <= 0) {
        ((S_80170D44_0_pre *)effect)[-1].unk_00 = (u16)(((S_80170D44_0_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
