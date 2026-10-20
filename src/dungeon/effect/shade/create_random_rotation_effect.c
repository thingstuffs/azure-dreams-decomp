#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"

typedef unsigned long uptr;
typedef long long s64_local;
typedef struct { s32 word[6]; } Copy24;

typedef union {
    s64_local all;
    struct {
        s32 hi;
        s32 lo;
    } part;
} product_pair;

#ifndef NULL
#define NULL 0
#endif

extern s32 func_8003DB94();
extern s32 register_node();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 func_80069EF8();

extern u8 D_80024710[];
extern u8 D_800DEC70[];

typedef struct S_818C2FAC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818C2FAC_0;   /* (void *)obj in create_random_rotation_effect */

typedef struct S_818C2FAC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818C2FAC_1;   /* work in create_random_rotation_effect */

/* Creates an effect with a selected appearance, random rotation, and a directional offset. */
s32 create_random_rotation_effect(void *data_addr, Copy24 *position_addr, s32 direction)
{
    s32 variant_seed;
    s16 variant;
    s32 biased_seed;
    s32 random_value;
    s32 biased_random;
    s32 y_factor;
    s32 y_offset;
    s32 new_y;
    s64_local position_xy;
    product_pair product_bits;
    s32 quotient;
    s32 position_z;
    s32 position_word_3;
    s32 position_word_4;
    s32 object_type;
    s16 offset_angle;
    uptr effect;
    uptr render_or_radius;
    s16 radius;
    s32 scaled_radius;
    s32 divisor_reciprocal;
    S_818C2FAC_1 *effect_state;

    object_type = 0x212;
    offset_angle = direction;
    effect = (uptr)func_8003FC64(object_type);
    if (effect != NULL) {

        ((S_818C2FAC_0 *)((void *)effect))->unk_10 = D_80024710;
        ((S_818C2FAC_0 *)((void *)effect))->unk_20 = (*(s32 *)((u8 *)((void *)data_addr) + 0));
        effect_state = (u8 *)effect + 0x20;
        effect_state->unk_04 = 0;
        effect_state->unk_06 = 0;

        render_or_radius = (uptr)((S_818C2FAC_0 *)((void *)effect))->unk_0C;
        ((SpriteFrameState *)render_or_radius)->color.c.b = 0x80;
        ((SpriteFrameState *)render_or_radius)->color.c.g = 0x80;
        ((SpriteFrameState *)render_or_radius)->color.c.r = 0x80;
        ((SpriteFrameState *)render_or_radius)->flags |= 0xC;
        ((SpriteFrameState *)render_or_radius)->tpage_abr |= 0x60;
        ((SpriteFrameState *)render_or_radius)->flags |= 0x100;

        variant_seed = (*(s16 *)((u8 *)((void *)data_addr) + 0x12));
        biased_seed = variant_seed;
        variant = variant_seed - ((biased_seed / 4) * 4);

        switch (variant) {
        case 0:
            ((SpriteFrameState *)render_or_radius)->clut = 0x7DCF;
            break;
        case 1:
            ((SpriteFrameState *)render_or_radius)->clut = 0x7E00;
            break;
        case 2:
            ((SpriteFrameState *)render_or_radius)->clut = 0x7E01;
            break;
        case 3:
            ((SpriteFrameState *)render_or_radius)->clut = 0x7E02;
            break;
        }
        {
            s32 render_arg;
            u8 *render_table;
            render_arg = (s32)render_or_radius;
            render_table = D_800DEC70;
            func_8003DB94(render_arg, render_table, 0);
        }
        random_value = func_80069EF8();
        biased_random = random_value;
        ((SpriteFrameState *)render_or_radius)->angle_z = (random_value % 4096);
        ((SpriteFrameState *)render_or_radius)->scale_y = 0x1000;
        ((SpriteFrameState *)render_or_radius)->scale_x = 0x1000;
        register_node((void *)effect, project_sprite_chain);

        data_addr = ((S_818C2FAC_0 *)((void *)effect))->unk_08;
        divisor_reciprocal = (s32)position_addr;
        *(Copy24 *)data_addr = *(Copy24 *)divisor_reciprocal;

        random_value = func_80069EF8();
        divisor_reciprocal = 0x78787879;
        render_or_radius = (uptr)random_value;
        offset_angle = (s16)offset_angle;
        render_or_radius = (uptr)((s32)render_or_radius % 17);
        render_or_radius += 0x20;
        y_factor = func_800644B8(offset_angle) >> 4;
        radius = (s16)render_or_radius;
        {
            s32 x_offset;
            scaled_radius = y_factor * (s32)radius;
            x_offset = scaled_radius << 8;
            (*(s32 *)((u8 *)((void *)data_addr) + 0)) += x_offset;
        }
        {
            y_factor = func_80064584(offset_angle) >> 4;
            scaled_radius = y_factor * (s32)radius;
            y_offset = scaled_radius << 8;
            new_y = (*(s32 *)((u8 *)((void *)data_addr) + 4)) + y_offset;
            (*(s32 *)((u8 *)((void *)data_addr) + 4)) = new_y;
            return (s32)effect;
        }

    }
    {
        s32 result;
        result = 0;
        return result;
    }
}
