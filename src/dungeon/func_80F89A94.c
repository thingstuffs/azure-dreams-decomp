#include "common.h"

typedef struct S_80173294_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_80173294_0;   /* p3 in func_80173294 */

typedef struct S_80173294_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80173294_1;   /* p1 in func_80173294 */

typedef struct S_80173294_2 {
    u8 pad_00[0x96];
    union { s16 s16; u8 u8; u16 u16; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173294_2;   /* p0 in func_80173294 */

typedef struct S_80173294_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173294_3;   /* p2 in func_80173294 */



extern void func_8009A028();
extern void func_8009A3D0();
extern void func_800A2FE0();
extern void func_800A32A4();
extern void func_800A56E0();
extern void func_800ACF88();
extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern s32 D_800814A0;
extern s32 D_80083460;
extern s16 D_8008346A;

/* Advance the object removal animation, fade its sprite, and release it when finished. */
void func_80173294(void *effect_data, void *motion_data, void *sprite_data, void *object_data) {
    s32 direction_offset;
    register s32 direction_x ASM_REG("$4");
    register u8 *direction_y_table ASM_REG("$2");
    s32 direction_y;
    s32 motion_step;
    s32 state;
    s32 motion_value;
    s32 is_low_state;
    register s32 next_state ASM_REG("$2");

    direction_x = (s32)(unsigned long)&D_8006CCD8;
    direction_y_table = &D_8006CCE8;
    direction_offset = (((S_80173294_0 *)object_data)->unk_6A >> 8) & 0xE;
    motion_step = 0xC000;
    direction_x = *(s16 *)(unsigned long)(u32)(direction_offset + direction_x);
    direction_offset += (s32)(unsigned long)direction_y_table;
    ASM_KEEP(motion_step);
    motion_value = ((S_80173294_1 *)motion_data)->unk_14;
    direction_y = *(s16 *)(unsigned long)(u32)direction_offset;
    motion_value += motion_step;
    ((S_80173294_1 *)motion_data)->unk_14 = motion_value;
    state = ((S_80173294_2 *)effect_data)->unk_9B;

    if (state == 1) goto state_1;
    is_low_state = state < 2;
    if (!is_low_state) goto high_states;
    ASM_KEEP(is_low_state);
    if (state == 0) {
        state = 0xFFFE0000;
        goto state_0;
    }
    ASM_SCHED_BARRIER();
    goto done;

high_states:
    if (state == 2) goto state_2;
    if (state == 3) goto state_3;
    goto done;

state_0:
    state |= 0x8000;
    motion_value = direction_x << 16;
    ((S_80173294_1 *)motion_data)->unk_0C = motion_value;
    motion_value = direction_y << 16;
    (*(s32 *)((u8 *)motion_data + 0x10)) = motion_value;
    (*(s32 *)((u8 *)motion_data + 0x14)) = state;
    if (D_8008346A != 0) goto done;
    ((S_80173294_2 *)effect_data)->unk_9B++;

state_1:
    {
        s32 flags;
        s32 object_flags;
        u16 sprite_x;
        u16 sprite_flags;
        u16 status;
        volatile u8 *state_byte;
        register s32 clear_bit_27;
        s32 clear_bit_18;

        flags = ((S_80173294_0 *)object_data)->unk_14;
        if (flags & 0x4000) {
            if (!(flags & 0x20000000)) func_800ACF88(object_data);
        }
        func_800A56E0(0x805);
        clear_bit_27 = 0xF7FFFFFF;
        status = ((S_80173294_2 *)effect_data)->unk_98;
        clear_bit_18 = 0xFFFBFFFF;
        status |= 8;
        ((S_80173294_2 *)effect_data)->unk_98 = status;
        object_flags = ((S_80173294_0 *)object_data)->unk_1C;
        object_flags &= clear_bit_27;
        object_flags &= clear_bit_18;
        ((S_80173294_0 *)object_data)->unk_1C = object_flags;

        ((S_80173294_3 *)sprite_data)->unk_10 = 0x60;
        sprite_x = ((S_80173294_3 *)sprite_data)->unk_12;
        sprite_flags = ((S_80173294_3 *)sprite_data)->unk_14;
        sprite_x -= 0x80;
        sprite_flags |= 0xC;
        ((S_80173294_3 *)sprite_data)->unk_12 = sprite_x;
        ((S_80173294_3 *)sprite_data)->unk_14 = sprite_flags;
        state_byte = (volatile u8 *)((u8 *)effect_data + 0x9B);
        next_state = *state_byte + 1;
        goto store_state;
    }

state_2:
    if (!(((S_80173294_3 *)sprite_data)->unk_14 & 0x6000)) goto done;
    ((S_80173294_2 *)effect_data)->unk_96.s16 = 0x80;
    next_state = ((S_80173294_2 *)effect_data)->unk_9B + 1;
store_state:
    ((S_80173294_2 *)effect_data)->unk_9B = next_state;
    goto done;

state_3:
    {
        u8 brightness;
        u16 fade_level;
        s32 *link_base;
        s32 linked_object;
        s32 flags;
        s32 tile_mask;
        u8 tile_x;
        u8 tile_y;

        ((S_80173294_0 *)object_data)->unk_1C |= 0x10000000;
        brightness = ((S_80173294_2 *)effect_data)->unk_96.u8;
        ((S_80173294_3 *)sprite_data)->unk_0E = brightness;
        ((S_80173294_3 *)sprite_data)->unk_0D = brightness;
        ((S_80173294_3 *)sprite_data)->unk_0C = brightness;
        fade_level = ((S_80173294_2 *)effect_data)->unk_96.u16 - 0x10;
        ((S_80173294_2 *)effect_data)->unk_96.u16 = fade_level;
        if ((s16)fade_level >= 0x10) goto done;
        link_base = &D_80083460;
        linked_object = link_base[4];
        if (linked_object == (s32)(object_data - 0x20)) link_base[4] = linked_object & 0x7FFFFFFF;
        func_800A2FE0(object_data);
        func_800A32A4(object_data);
        flags = ((S_80173294_0 *)object_data)->unk_1C;
        tile_x = ((S_80173294_3 *)sprite_data)->unk_24;
        tile_y = ((S_80173294_3 *)sprite_data)->unk_25;
        tile_mask = 0x3000;
        if (flags & 0x2000) tile_mask = 0x300;
        func_8009A3D0(tile_x, tile_y, tile_mask);
        func_8009A028(object_data);
        (*(u16 *)((u8 *)object_data + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    ASM_KEEP(effect_data);
    return;
}
