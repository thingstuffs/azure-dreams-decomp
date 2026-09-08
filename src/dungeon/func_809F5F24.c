#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern void *D_801708A0[];
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0[3];
extern M2C_UNK D_80083460;
extern s16 D_8008346A;


typedef struct S_80173724_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173724_0;   /* arg0 in func_80173724 */

typedef struct S_80173724_1_pre {
    u16 unk_00;
} S_80173724_1_pre;   /* the 0x2 bytes before arg3 in func_80173724, addressed as arg3[-1] */

typedef struct S_80173724_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_80173724_1;   /* arg3 in func_80173724 */

typedef struct S_80173724_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173724_2;   /* arg1 in func_80173724 */

typedef struct S_80173724_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173724_3;   /* arg2 in func_80173724 */

typedef struct S_80173724_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80173724_4;   /* global_ptr in func_80173724 */

/* Advance an entity through directional motion, fading, and removal. */
void func_80173724(void *anim_state, void *motion, void *sprite, void *entity) {
    static void *const state_labels[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    M2C_UNK sound_flags;
    s32 direction_x;
    s32 direction_y;
    s32 direction_offset;
    s32 status_flags;
    u16 next_brightness;
    u32 phase;
    u32 sound_x;
    u32 sound_y;
    u8 brightness;
    void *world_state;

    phase = ((S_80173724_0 *)anim_state)->unk_9B;
    direction_offset = ((u16) ((S_80173724_1 *)entity)->unk_6A >> 8) & 0xE;
    direction_x = *(s16 *)((u8 *)&D_8006CCD8 + direction_offset);
    direction_y = *(s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    if (phase >= 5U) {
        goto block_20;
    }
    (void)state_labels;
    goto *D_801708A0[(u32)phase];
jt_c0:
    {
        u32 clear_bit_27 = 0xF7FFFFFF;
        u32 clear_bit_18;
        u32 entity_flags;
        u16 anim_flags;

        anim_flags = ((S_80173724_0 *)anim_state)->unk_98;
        clear_bit_18 = 0xFFFBFFFF;
        anim_flags |= 8;
        ((S_80173724_0 *)anim_state)->unk_98 = anim_flags;
        entity_flags = ((S_80173724_1 *)entity)->unk_1C.u;
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        ((S_80173724_1 *)entity)->unk_1C.u = entity_flags;
        ((S_80173724_2 *)motion)->unk_0C = direction_x << 0x10;
        ((S_80173724_2 *)motion)->unk_10 = direction_y << 0x10;
        ((S_80173724_2 *)motion)->unk_14 = 0xFFF40000;
        func_800A56E0(0x805);
        ((S_80173724_0 *)anim_state)->unk_9B = ((S_80173724_0 *)anim_state)->unk_9B + 1;
    }
jt_c1:
    (*(s32 *)((u8 *)motion + (0x14))) += 0x1C000;
    if (D_8008346A != 0) {
        goto block_20;
    }
    ((S_80173724_0 *)anim_state)->unk_9B = ((S_80173724_0 *)anim_state)->unk_9B + 1;
jt_c2:
    status_flags = ((S_80173724_1 *)entity)->unk_14;
    if (!(status_flags & 0x4000)) {
        goto block_10;
    }
    if (status_flags & 0x20000000) {
        goto block_10;
    }
    func_800ACF88(entity);
block_10:
    ((S_80173724_3 *)sprite)->unk_10 = 0x60;
    ((S_80173724_3 *)sprite)->unk_14 |= 0xC;
    ((S_80173724_0 *)anim_state)->unk_9B = ((S_80173724_0 *)anim_state)->unk_9B + 1;
jt_c3:
    ((S_80173724_2 *)motion)->unk_14 += 0x1C000;
    if (!(((S_80173724_3 *)sprite)->unk_14 & 0x6000)) {
        goto block_20;
    }
    ((S_80173724_0 *)anim_state)->unk_96 = 0x80U;
    ((S_80173724_0 *)anim_state)->unk_9B = ((S_80173724_0 *)anim_state)->unk_9B + 1;
    return;
jt_c4:
    ((S_80173724_1 *)entity)->unk_1C.s |= 0x10000000;
    ((S_80173724_2 *)motion)->unk_14 += 0x20000;
    brightness = (u8)((S_80173724_0 *)anim_state)->unk_96;
    ((S_80173724_3 *)sprite)->unk_0E = brightness;
    ((S_80173724_3 *)sprite)->unk_0D = brightness;
    ((S_80173724_3 *)sprite)->unk_0C = brightness;
    next_brightness = ((S_80173724_0 *)anim_state)->unk_96 - 0x18;
    ((S_80173724_0 *)anim_state)->unk_96 = next_brightness;
    if ((s16)next_brightness >= 0x18) {
        goto block_20;
    }
    world_state = &D_80083460;
    if (((S_80173724_4 *)world_state)->unk_10 != (entity - 0x20)) {
        goto block_17;
    }
    ((S_80173724_4 *)world_state)->unk_10 &= 0x7FFFFFFF;
block_17:
    func_800A2FE0(entity, phase, direction_x, direction_y);
    func_800A32A4(entity);
    sound_x = ((S_80173724_3 *)sprite)->unk_24;
    sound_y = ((S_80173724_3 *)sprite)->unk_25;
    sound_flags = 0x3000;
    if (!(((S_80173724_1 *)entity)->unk_1C.s & 0x2000)) {
        goto block_19;
    }
    sound_flags = 0x300;
block_19:
    func_8009A3D0(sound_x, sound_y, sound_flags);
    func_8009A028(entity);
    ((S_80173724_1_pre *)entity)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
block_20:
    return;
}
