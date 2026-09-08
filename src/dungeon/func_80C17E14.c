#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((u8 *)(expr) + (offset)))

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
void func_80173614(void *action, void *motion, void *sprite, void *entity) {
    s32 direction_offset;
    s32 offset_x;
    s32 offset_y;
    s32 state;

    direction_offset = (FIELD(entity, u16 *, 0x6A) >> 8) & 0xE;
    offset_x = *(s16 *)((u8 *)&D_8006CCD8 + direction_offset);
    offset_y = *(s16 *)((u8 *)&D_8006CCE8 + direction_offset);
    state = FIELD(action, u8 *, 0x9B);

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
    FIELD(motion, s32 *, 0xC) = offset_x << 16;
    FIELD(motion, s32 *, 0x10) = offset_y << 16;
    FIELD(motion, s32 *, 0x14) = 0x8000;
    if (D_8008346A != 0) {
        goto done;
    }
    FIELD(action, u8 *, 0x9B) = FIELD(action, u8 *, 0x9B) + 1;

start_animation:
    {
        s32 entity_status;
        u32 entity_flags;
        u32 clear_bit_27;
        u32 clear_bit_18;
        u16 action_flags;

        entity_status = FIELD(entity, s32 *, 0x14);
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
        action_flags = FIELD(action, u16 *, 0x98);
        clear_bit_18 = 0xFFFBFFFF;
        action_flags |= 8;
        FIELD(action, u16 *, 0x98) = action_flags;
        entity_flags = FIELD(entity, u32 *, 0x1C);
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        FIELD(entity, u32 *, 0x1C) = entity_flags;
        FIELD(sprite, s16 *, 0x10) = 0x60;
        FIELD(sprite, u16 *, 0x12) = 0xFF80;
        FIELD(sprite, u16 *, 0x14) |= 0xC;
        FIELD(action, u8 *, 0x9B) = FIELD(action, u8 *, 0x9B) + 1;
        goto done;
    }

wait_animation:
    if (!(FIELD(sprite, u16 *, 0x14) & 0x6000)) {
        goto done;
    }
    FIELD(action, u16 *, 0x96) = 0x80;
    FIELD(action, u8 *, 0x9B) = FIELD(action, u8 *, 0x9B) + 1;
    goto done;

fade_out:
    {
        s32 sound_kind;
        u32 entity_flags;
        u32 sound_x;
        u32 sound_y;
        u16 next_brightness;
        u8 brightness;
        s32 *dungeon_state;

        FIELD(entity, u32 *, 0x1C) |= 0x10000000;
        brightness = FIELD(action, u8 *, 0x96);
        FIELD(sprite, u8 *, 0xE) = brightness;
        FIELD(sprite, u8 *, 0xD) = brightness;
        FIELD(sprite, u8 *, 0xC) = brightness;
        next_brightness = FIELD(action, u16 *, 0x96) - 0x10;
        FIELD(action, u16 *, 0x96) = next_brightness;
        if ((s16)next_brightness >= 0x10) {
            goto done;
        }

        dungeon_state = &D_80083460;
        if (FIELD(dungeon_state, s32 *, 0x10) == (s32)((u8 *)entity - 0x20)) {
            FIELD(dungeon_state, s32 *, 0x10) &= 0x7FFFFFFF;
        }
        func_800A2FE0(entity);
        func_800A32A4(entity);

        entity_flags = FIELD(entity, u32 *, 0x1C);
        sound_x = FIELD(sprite, u8 *, 0x24);
        sound_y = FIELD(sprite, u8 *, 0x25);
        sound_kind = 0x3000;
        if (entity_flags & 0x2000) {
            sound_kind = 0x300;
        }
        func_8009A3D0(sound_x, sound_y, sound_kind);
        func_8009A028(entity);
        FIELD(entity, u16 *, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

done:
    return;
}
