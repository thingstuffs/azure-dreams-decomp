#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef s32 M2C_UNK;

extern void *D_80170858[];
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();
s16 func_800BCB04();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0[3];
extern M2C_UNK D_80083460;
extern s16 D_8008346A;


typedef struct S_801731FC_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_801731FC_0;   /* arg0 in func_801731FC */

typedef struct S_801731FC_1_pre {
    u16 unk_00;
} S_801731FC_1_pre;   /* the 0x2 bytes before arg3 in func_801731FC, addressed as arg3[-1] */

typedef struct S_801731FC_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_801731FC_1;   /* arg3 in func_801731FC */

typedef struct S_801731FC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801731FC_2;   /* arg1 in func_801731FC */

typedef struct S_801731FC_3 {
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
} S_801731FC_3;   /* arg2 in func_801731FC */

typedef struct S_801731FC_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_801731FC_4;   /* global_ptr in func_801731FC */

/* Advance an entity through motion, fading, and removal. */
void func_801731FC(S_801731FC_0 *state, S_801731FC_2 *motion, S_801731FC_3 *sprite, void *entity) {
    static void *const phase_labels[] = { &&start_motion, &&wait_motion, &&start_effect, &&wait_effect, &&fade_out };
    M2C_UNK sound_flags;
    s32 velocity_x;
    s32 velocity_y;
    s32 direction_offset;
    s32 status_flags;
    u16 next_brightness;
    u32 phase;
    u32 sound_x;
    u32 sound_y;
    u8 brightness;
    S_801731FC_4 *entity_tracker;

    phase = state->unk_9B;
    direction_offset = ((u16) ((S_801731FC_1 *)entity)->unk_6A >> 8) & 0xE;
    velocity_x = *(s16 *)((u8 *)&D_8006CCD8 + direction_offset);
    velocity_y = *(s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    if (phase >= 5U) {
        goto done;
    }
    (void)phase_labels;
    goto *D_80170858[(u32)phase];
start_motion:
    {
        u32 clear_bit_27 = 0xF7FFFFFF;
        u32 clear_bit_18;
        u32 entity_flags;
        u16 state_flags;

        state_flags = state->unk_98;
        clear_bit_18 = 0xFFFBFFFF;
        state_flags |= 8;
        state->unk_98 = state_flags;
        entity_flags = ((S_801731FC_1 *)entity)->unk_1C.u;
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        ((S_801731FC_1 *)entity)->unk_1C.u = entity_flags;
        motion->unk_0C = velocity_x << 0x10;
        motion->unk_10 = velocity_y << 0x10;
        motion->unk_14 = 0xFFF40000;
        state->unk_9B = state->unk_9B + 1;
    }
wait_motion:
    motion->unk_14 += 0x1C000;
    if (func_800BCB04(motion->unk_02, motion->unk_06,
                      motion->unk_0A, velocity_y) < 0x200) {
        goto check_motion_done;
    }
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
check_motion_done:
    if (D_8008346A != 0) {
        goto done;
    }
    state->unk_9B = state->unk_9B + 1;
start_effect:
    status_flags = ((S_801731FC_1 *)entity)->unk_14;
    if (!(status_flags & 0x4000)) {
        goto configure_effect;
    }
    if (status_flags & 0x20000000) {
        goto configure_effect;
    }
    func_800ACF88(entity);
configure_effect:
    func_800A56E0(0x805);
    sprite->unk_10 = 0x20;
    sprite->unk_14 |= 0xC;
    sprite->unk_12 -= 0x80;
    state->unk_9B = state->unk_9B + 1;
wait_effect:
    motion->unk_14 += 0x1C000;
    if (!(sprite->unk_14 & 0x6000)) {
        goto done;
    }
    state->unk_96 = 0x80U;
    state->unk_9B = state->unk_9B + 1;
    return;
fade_out:
    ((S_801731FC_1 *)entity)->unk_1C.s |= 0x10000000;
    brightness = (u8)state->unk_96;
    sprite->unk_0E = brightness;
    sprite->unk_0D = brightness;
    sprite->unk_0C = brightness;
    next_brightness = state->unk_96 - 0x18;
    state->unk_96 = next_brightness;
    if ((s16)next_brightness >= 0x18) {
        goto done;
    }
    entity_tracker = &D_80083460;
    if (entity_tracker->unk_10 != (entity - 0x20)) {
        goto remove_entity;
    }
    entity_tracker->unk_10 &= 0x7FFFFFFF;
remove_entity:
    func_800A2FE0(entity, phase, velocity_x, velocity_y);
    func_800A32A4(entity);
    sound_x = sprite->unk_24;
    sound_y = sprite->unk_25;
    sound_flags = 0x3000;
    if (!(((S_801731FC_1 *)entity)->unk_1C.s & 0x2000)) {
        goto play_sound;
    }
    sound_flags = 0x300;
play_sound:
    func_8009A3D0(sound_x, sound_y, sound_flags);
    func_8009A028(entity);
    ((S_801731FC_1_pre *)entity)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
done:
    return;
}
