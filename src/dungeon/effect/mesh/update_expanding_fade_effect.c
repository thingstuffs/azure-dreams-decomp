#include "common.h"
#include "dungeon/effect/mesh.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"

typedef struct S_81977E0C_0_pre {
    u16 unk_00;
} S_81977E0C_0_pre;   /* the 0x2 bytes before arg0 in update_expanding_fade_effect, addressed as arg0[-1] */

typedef struct S_81977E0C_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} S_81977E0C_0;   /* arg0 in update_expanding_fade_effect */


typedef struct S_81977E0C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_81977E0C_3;   /* D_80026208 in update_expanding_fade_effect */

extern void advance_sprite_animation_and_textures(void *);
extern s32 *effect_position_source;

/* Expand and fade a spiraling effect while updating its position. */
void update_expanding_fade_effect(void *effect, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 height_offset;
    u16 age;
    u16 scale;
    u8 brightness;

    age = ((S_81977E0C_0 *)effect)->unk_04 + 1;
    ((S_81977E0C_0 *)effect)->unk_04 = age;
    if ((s16) age >= 0xA) {
        brightness = sprite->color.c.b - 0x10;
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        sprite->color.c.r = brightness;
    }
    ((S_81977E0C_0 *)effect)->unk_08 = (u16) (((S_81977E0C_0 *)effect)->unk_08 + 0x100);
    ((S_81977E0C_0 *)effect)->unk_06 = (u16) (((S_81977E0C_0 *)effect)->unk_06 + 1);
    height_offset = (u16) (((S_81977E0C_0 *)effect)->unk_0A - 8) - (rand() % 9);
    ((S_81977E0C_0 *)effect)->unk_0A = height_offset;
    if ((u16) sprite->scale_x < 0x400U) {
        scale = sprite->scale_y + 0x40;
        sprite->scale_y = scale;
        sprite->scale_x = scale;
    }
    advance_sprite_animation_and_textures(sprite);
    if (sprite->flags & 0x6000) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_81977E0C_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    position->x.v = (s32) (*effect_position_source + (((rsin((s16) ((S_81977E0C_0 *)effect)->unk_08)
        >> 4) * (s16) ((S_81977E0C_0 *)effect)->unk_06) << 8));
    position->y.v = (s32) (effect_position_source[1]
        + (((rcos((s16) ((S_81977E0C_0 *)effect)->unk_08) >> 4) * (s16) ((S_81977E0C_0 *)effect)->unk_06)
           << 8));
    position->z.w.i = (s16) (((S_81977E0C_3 *)effect_position_source)->unk_0A
        + ((S_81977E0C_0 *)effect)->unk_0A);
}
