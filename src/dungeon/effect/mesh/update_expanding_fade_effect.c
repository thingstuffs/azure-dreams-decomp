#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

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

typedef struct S_81977E0C_2 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_81977E0C_2;   /* arg1 in update_expanding_fade_effect */

typedef struct S_81977E0C_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_81977E0C_3;   /* D_80026208 in update_expanding_fade_effect */

extern void advance_sprite_animation_and_textures(void *);
s32 func_800644B8();
s32 func_80064584();
s32 rand();
extern s32 *D_80026208;

/* Expand and fade a spiraling effect while updating its position. */
void update_expanding_fade_effect(void *effect, void *position, void *sprite) {
    u16 height_offset;
    u16 age;
    u16 scale;
    u8 brightness;

    age = ((S_81977E0C_0 *)effect)->unk_04 + 1;
    ((S_81977E0C_0 *)effect)->unk_04 = age;
    if ((s16) age >= 0xA) {
        brightness = ((SpriteFrameState *)sprite)->color.c.b - 0x10;
        ((SpriteFrameState *)sprite)->color.c.b = brightness;
        ((SpriteFrameState *)sprite)->color.c.g = brightness;
        ((SpriteFrameState *)sprite)->color.c.r = brightness;
    }
    ((S_81977E0C_0 *)effect)->unk_08 = (u16) (((S_81977E0C_0 *)effect)->unk_08 + 0x100);
    ((S_81977E0C_0 *)effect)->unk_06 = (u16) (((S_81977E0C_0 *)effect)->unk_06 + 1);
    height_offset = (u16) (((S_81977E0C_0 *)effect)->unk_0A - 8) - (rand() % 9);
    ((S_81977E0C_0 *)effect)->unk_0A = height_offset;
    if ((u16) ((SpriteFrameState *)sprite)->scale_x < 0x400U) {
        scale = ((SpriteFrameState *)sprite)->scale_y + 0x40;
        ((SpriteFrameState *)sprite)->scale_y = scale;
        ((SpriteFrameState *)sprite)->scale_x = scale;
    }
    advance_sprite_animation_and_textures(sprite);
    if (((SpriteFrameState *)sprite)->flags & 0x6000) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_81977E0C_0_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    ((S_81977E0C_2 *)position)->unk_00 = (s32) (*D_80026208 + (((func_800644B8((s16) ((S_81977E0C_0 *)effect)->unk_08)
        >> 4) * (s16) ((S_81977E0C_0 *)effect)->unk_06) << 8));
    ((S_81977E0C_2 *)position)->unk_04 = (s32) (D_80026208[1]
        + (((func_80064584((s16) ((S_81977E0C_0 *)effect)->unk_08) >> 4) * (s16) ((S_81977E0C_0 *)effect)->unk_06)
           << 8));
    ((S_81977E0C_2 *)position)->unk_0A = (s16) (((S_81977E0C_3 *)D_80026208)->unk_0A
        + ((S_81977E0C_0 *)effect)->unk_0A);
}
