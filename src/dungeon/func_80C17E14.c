#include "common.h"

typedef struct S_func_80C17E14_0 {
    u8 pad_00[0x96];
    union {
        u8 unk_00_u8;
        u16 unk_00_u16;
    } unk_96;
    u16 unk_98;
    u8 pad_9A[1];
    u8 unk_9B;
} S_func_80C17E14_0;

typedef struct S_func_80C17E14_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_80C17E14_1;

typedef struct S_func_80C17E14_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_func_80C17E14_2;

typedef struct S_func_80C17E14_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[4];
    u32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_func_80C17E14_3;

typedef struct S_func_80C17E14_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_func_80C17E14_4;

typedef s32 M2C_UNK;

M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A2FE0();
M2C_UNK func_800A32A4();
M2C_UNK func_800A56E0();
M2C_UNK func_800ACF88();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_800814A0;
extern s32 D_80083460;
extern s16 D_8008346A;

/* Advances an entity removal animation, fading its sprite before cleanup. */
void func_80173614(S_func_80C17E14_0 *action, S_func_80C17E14_1 *motion, S_func_80C17E14_2 *sprite, S_func_80C17E14_3 *entity) {
    s32 direction_offset;
    s32 offset_x;
    s32 offset_y;
    s32 state;

    direction_offset = (entity->unk_6A >> 8) & 0xE;
    offset_x = *(s16 *)((u8 *)&D_8006CCD8 + direction_offset);
    offset_y = *(s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    state = action->unk_9B;

    if (state == 1) {
        goto start_animation;
    }
    if (state >= 2) {
        goto high_states;
    }
    if (state == 0) {
        goto initialize;
    }
    goto done;

high_states:
    if (state == 2) {
        goto wait_animation;
    }
    if (state == 3) {
        goto fade_out;
    }
    goto done;

initialize:
    *(s32 *)((u8 *)motion + 0xC) = offset_x << 16;
    *(s32 *)((u8 *)motion + 0x10) = offset_y << 16;
    *(s32 *)((u8 *)motion + 0x14) = 0x8000;
    if (D_8008346A != 0) {
        goto done;
    }
    action->unk_9B = action->unk_9B + 1;

start_animation:
    {
        s32 entity_status;
        u32 entity_flags;
        u32 clear_bit_27;
        u32 clear_bit_18;
        u16 action_flags;

        entity_status = entity->unk_14;
        if (!(entity_status & 0x4000)) {
            goto flags_done;
        }
        if (entity_status & 0x20000000) {
            goto flags_done;
        }
        func_800ACF88(entity);
flags_done:
        func_800A56E0(0x805);

        clear_bit_27 = 0xF7FFFFFF;
        action_flags = action->unk_98;
        clear_bit_18 = 0xFFFBFFFF;
        action_flags |= 8;
        action->unk_98 = action_flags;
        entity_flags = entity->unk_1C;
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        entity->unk_1C = entity_flags;
        sprite->unk_10 = 0x60;
        sprite->unk_12 = 0xFF80;
        sprite->unk_14 |= 0xC;
        action->unk_9B = action->unk_9B + 1;
        goto done;
    }

wait_animation:
    if (!(sprite->unk_14 & 0x6000)) {
        goto done;
    }
    action->unk_96.unk_00_u16 = 0x80;
    action->unk_9B = action->unk_9B + 1;
    goto done;

fade_out:
    {
        s32 sound_kind;
        u32 entity_flags;
        u32 sound_x;
        u32 sound_y;
        u16 next_brightness;
        u8 brightness;
        S_func_80C17E14_4 *dungeon_state;

        entity->unk_1C |= 0x10000000;
        brightness = action->unk_96.unk_00_u8;
        sprite->unk_0E = brightness;
        sprite->unk_0D = brightness;
        sprite->unk_0C = brightness;
        next_brightness = action->unk_96.unk_00_u16 - 0x10;
        action->unk_96.unk_00_u16 = next_brightness;
        if ((s16)next_brightness >= 0x10) {
            goto done;
        }

        dungeon_state = (S_func_80C17E14_4 *)&D_80083460;
        if (dungeon_state->unk_10 == (s32)((u8 *)entity - 0x20)) {
            dungeon_state->unk_10 &= 0x7FFFFFFF;
        }
        func_800A2FE0(entity);
        func_800A32A4(entity);

        entity_flags = entity->unk_1C;
        sound_x = sprite->unk_24;
        sound_y = sprite->unk_25;
        sound_kind = 0x3000;
        if (entity_flags & 0x2000) {
            sound_kind = 0x300;
        }
        func_8009A3D0(sound_x, sound_y, sound_kind);
        func_8009A028(entity);
        *(u16 *)((u8 *)entity - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}
