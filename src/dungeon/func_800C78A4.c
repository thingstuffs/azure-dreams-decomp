#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800CD004_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800CD004_0_pre;   /* the 0x14 bytes before arg0 in func_800CD004, addressed as arg0[-1] */

typedef struct S_800CD004_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xF];
    u8 unk_13;
    u8 pad_14[0x74];
    u16 unk_88;
} S_800CD004_0;   /* arg0 in func_800CD004 */

typedef struct S_800CD004_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800CD004_1;   /* object in func_800CD004 */

typedef struct S_800CD004_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CD004_2;   /* map in func_800CD004 */

typedef struct S_800CD004_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD004_3;   /* quad in func_800CD004 */

typedef struct S_800CD004_4 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0xA];
    s16 unk_1C;
    s16 unk_1E;
} S_800CD004_4;   /* sprite in func_800CD004 */

typedef struct S_800CD004_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800CD004_5;   /* tail in func_800CD004 */

typedef struct S_800CD004_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800CD004_6;   /* counter in func_800CD004 */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s32 func_80069EF8(s32);
extern void func_800A56E0(s32);
extern void func_800A6508(s32, s32, s32, s32);
extern s32 func_800A6D30(void *, s32, s32, s32);

extern u8 D_80045340;
extern u8 D_80083460[];
extern u8 D_800CCDA0;
extern u8 D_800DDC40[];
extern u8 D_800DFD0C[];
extern u8 D_800DFD30[];
extern u8 D_800E3D40;

/* Spawn a sprite effect for the source or invoke its fallback action. */
s32 func_800CD004(void *source, s32 rng_arg_1, s32 rng_arg_2, s32 rng_arg_3)
{
    s32 random_value;
    s32 random_low;
    register s32 roll_modulus ASM_REG("$2");
    register s32 roll_remainder ASM_REG("$3");
    register s32 roll_or_data ASM_REG("$2");
    s32 roll_range;
    s32 tile_x;
    void *effect;
    S_800CD004_3 *quad;
    S_800CD004_5 *effect_state;
    S_800CD004_4 *sprite;
    S_800CD004_2 *map;
    void *texture;
    s32 color;
    s32 variant;
    register s32 height_offset ASM_REG("$3");
    s32 height_delta;
    u8 *counter;
    register void *init_effect ASM_REG("$4");

    if (D_800E3D40 == 0) {
        random_value = func_800A6D30(source, rng_arg_1, rng_arg_2, rng_arg_3);
        roll_range = ((S_800CD004_0 *)source)->unk_03;
        if (roll_range != 0) {
            random_low = (u16)random_value;
            roll_modulus = roll_range;
            ASM_KEEP(random_low);
            roll_remainder = random_low % roll_modulus;
            roll_or_data = roll_remainder;
        } else {
            roll_or_data = 0;
        }
    } else {
        roll_or_data = 0;
    }

    if (roll_or_data < 0x30) {
        effect = func_8003FC64(2);
        if (effect == NULL) {
            goto return_object;
        }
        init_effect = effect;
        roll_or_data = (s32)&D_800CCDA0;
        ((S_800CD004_1 *)effect)->unk_10 = (void *)roll_or_data;
        func_8004491C(init_effect, &D_80045340);

        map = ((S_800CD004_0_pre *)source)[-1].unk_00;
        tile_x = map->unk_24;
        ASM_KEEP(tile_x);
        quad = ((S_800CD004_1 *)effect)->unk_08;
        ASM_KEEP(quad);
        quad->unk_02 = (tile_x << 6) + 0x20;
        quad->unk_06 = (map->unk_25 << 6) + 0x20;
        quad->unk_0A = ((S_800CD004_0 *)source)->unk_88 - 0x200;

        sprite = ((S_800CD004_1 *)effect)->unk_0C;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        color = 0x808080;
        ASM_KEEP(color);
        sprite->unk_0C = color;

        variant = func_80069EF8(color);
        if (variant & 3) {
            texture = D_800DFD0C;
        } else {
            texture = D_800DFD30;
        }
        sprite->unk_08 = texture;
        sprite->unk_10 = 0x20;

        height_offset = D_800DDC40[((S_800CD004_0 *)source)->unk_13];
        height_delta = ((S_800CD004_0 *)source)->unk_88 - height_offset;
        effect_state = (u8 *)effect + 0x20;
        ASM_KEEP(effect_state);
        effect_state->unk_0A = height_delta;
        ((S_800CD004_1 *)effect)->unk_20 = source;
        effect_state->unk_06 = 0xC;

        counter = D_80083460;
        ((S_800CD004_6 *)counter)->unk_0A = ((S_800CD004_6 *)counter)->unk_0A + 1;
        func_800A56E0(0x50D);
        goto return_object;
    }

    if (((S_800CD004_0 *)source)->unk_13 == 0) {
        s32 fallback_arg_0;
        s32 fallback_arg_1;
        s32 fallback_arg_2;
        s32 fallback_arg_3;

        ASM_SET(fallback_arg_0);
        ASM_SET(fallback_arg_1);
        ASM_SET(fallback_arg_2);
        ASM_SET(fallback_arg_3);
        func_800A6508(fallback_arg_0, fallback_arg_1, fallback_arg_2, fallback_arg_3);
    }
    return 1;

return_object:
    return effect != NULL;
}
