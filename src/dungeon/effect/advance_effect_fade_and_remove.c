#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"

struct Dst;
struct Elem;

typedef struct S_800B7C14_1_pre {
    u16 unk_00;
} S_800B7C14_1_pre;   /* the 0x2 bytes before arg0 in advance_effect_fade_and_remove, addressed as arg0[-1] */

typedef struct S_800B7C14_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u16 unk_16;
} S_800B7C14_1;   /* arg0 in advance_effect_fade_and_remove */

typedef struct S_800B7C14_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800B7C14_2;   /* arg1 in advance_effect_fade_and_remove */

extern void select_record_entry_and_value(struct Dst *state, struct Elem *entries, short index);        /* extern */
extern void advance_sprite_animation_and_textures(void *entity);                      /* extern */

/* Advance effect motion, fade its primitive, and mark it for removal when its lifetime ends. */
void advance_effect_fade_and_remove(void *effect, void *motion, SpriteFrameState *primitive) {
    s32 velocity_x;
    u16 life_left;
    u8 brightness;

    if (*(s32 *)&primitive->unk_00 != 0) {
        advance_sprite_animation_and_textures(primitive);
        if (primitive->flags & 0x4000) {
            select_record_entry_and_value(primitive, ((S_800B7C14_1 *)effect)->unk_08, 0);
        }
    }
    ((S_800B7C14_2 *)motion)->unk_00 = (s32) (((S_800B7C14_2 *)motion)->unk_00 + ((S_800B7C14_2 *)motion)->unk_0C);
    ((S_800B7C14_2 *)motion)->unk_04 = (s32) (((S_800B7C14_2 *)motion)->unk_04 + ((S_800B7C14_2 *)motion)->unk_10);
    velocity_x = ((S_800B7C14_2 *)motion)->unk_0C;
    ((S_800B7C14_2 *)motion)->unk_08 = (s32) (((S_800B7C14_2 *)motion)->unk_08 + ((S_800B7C14_2 *)motion)->unk_14);
    ((S_800B7C14_2 *)motion)->unk_0C = (s32) (velocity_x - (velocity_x >> 4));
    ((S_800B7C14_2 *)motion)->unk_10 = (s32) (((S_800B7C14_2 *)motion)->unk_10 - (((S_800B7C14_2 *)motion)->unk_10
        >> 4));
    ((S_800B7C14_2 *)motion)->unk_14 = (s32) (((S_800B7C14_2 *)motion)->unk_14 + 0x40000);
    if (((S_800B7C14_1 *)effect)->unk_12 != 0) {
        brightness = primitive->color.c.r;
        if (brightness != 0) {
            brightness -= 8;
            primitive->color.c.r = brightness;
            primitive->color.c.b = brightness;
            primitive->color.c.g = brightness;
        }
    }
    primitive->angle_x = (u16) (primitive->angle_x
        + ((S_800B7C14_1 *)effect)->unk_14);
    primitive->angle_y = (u16) (primitive->angle_y
        + ((S_800B7C14_1 *)effect)->unk_16);
    life_left = ((S_800B7C14_1 *)effect)->unk_10 - 1;
    ((S_800B7C14_1 *)effect)->unk_10 = life_left;
    if ((life_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (((S_800B7C14_1_pre *)effect)[-1].unk_00 | NODE_REMOVE);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
