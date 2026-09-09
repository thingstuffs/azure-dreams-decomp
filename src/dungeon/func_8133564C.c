#include "common.h"

typedef struct S_func_8016C64C_0 {
    u8 pad_00[0x8C];
    u8 *unk_8C;
    u8 pad_90[4];
    s16 unk_94;
    union {
        s16 s16_value;
        u16 u16_value;
    } unk_96;
    u8 pad_98[3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
    u8 pad_AD[3];
    u8 unk_B0;
} S_func_8016C64C_0;

typedef struct S_func_8016C64C_1 {
    u8 pad_00[2];
    s16 unk_02;
    u8 pad_04[2];
    s16 unk_06;
    u8 pad_08[4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_func_8016C64C_1;

typedef struct S_func_8016C64C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[6];
    u8 *unk_2C;
} S_func_8016C64C_2;

typedef struct S_func_8016C64C_3 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[1];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[4];
    u16 unk_6A;
} S_func_8016C64C_3;

typedef struct S_func_8016C64C_4 {
    u8 pad_00[0x10];
    union {
        u8 *ptr;
        u32 u32_value;
    } unk_10;
} S_func_8016C64C_4;

typedef struct S_func_8016C64C_5 {
    s16 unk_00;
} S_func_8016C64C_5;

extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern void func_80047784(void *, u8, s32);
extern void func_800A56E0(s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800A2B04(void *, u8, u8);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_8016A36C[];
extern u8 D_801739A0[];
extern u8 D_801739A8[];
extern u8 D_801739B0[];
extern u8 D_801739B8[];
extern u8 D_80173A20[];
extern u8 D_80173A28[];
extern u8 D_80173A30[];
extern u8 D_80173A38[];
extern u8 D_80175DC0;
extern u8 D_80175DC1;

/* Move the actor back to its tile, update its animation, and advance its recovery state. */
void func_8016C64C(S_func_8016C64C_0 *action, S_func_8016C64C_1 *motion, S_func_8016C64C_2 *sprite, S_func_8016C64C_3 *actor)
{
    s16 target_distance;
    s16 frame_count;
    s32 tile_pos;
    s32 offset_pos;
    u8 *anim_table;
    u8 *current_anim;
    S_func_8016C64C_4 *world_state;

    switch (action->unk_9B) {
    case 0:
        actor->unk_64 = 0;
        action->unk_9B++;
        D_80175DC1 = 0;
        action->unk_96.s16_value = 6;
        if (action->unk_B0 < 2) {
            return;
        }
        actor->unk_2A = func_800A0818(
            sprite->unk_24, sprite->unk_25,
            D_80082E80[0x24], D_80082E80[0x25], &target_distance);
        action->unk_94 = 1;
        return;

    case 1:
        frame_count = --action->unk_96.u16_value;
        if (frame_count > 0) {
            motion->unk_0C =
                ((S_func_8016C64C_5 *)((u8 *)&D_8006CCD8 + ((actor->unk_6A >> 8) & 0xE)))->unk_00 << 18;
            motion->unk_10 =
                ((S_func_8016C64C_5 *)((u8 *)&D_8006CCE8 + ((actor->unk_6A >> 8) & 0xE)))->unk_00 << 18;
            return;
        }
        if (frame_count != 0) {
            return;
        }
        motion->unk_0C =
            ((S_func_8016C64C_5 *)((u8 *)&D_8006CCD8 + ((actor->unk_6A >> 8) & 0xE)))->unk_00 << 18;
        motion->unk_10 =
            ((S_func_8016C64C_5 *)((u8 *)&D_8006CCE8 + ((actor->unk_6A >> 8) & 0xE)))->unk_00 << 18;
        action->unk_96.s16_value = 8;
        action->unk_9B++;
        return;

    case 2:
        frame_count = action->unk_96.s16_value;
        if (frame_count != 0) {
            tile_pos = sprite->unk_24 << 6;
            offset_pos = motion->unk_02;
            offset_pos -= 0x20;
            motion->unk_0C =
                ((tile_pos - offset_pos) << 16) / frame_count;
            tile_pos = sprite->unk_25 << 6;
            offset_pos = motion->unk_06;
            offset_pos -= 0x20;
            motion->unk_10 =
                ((tile_pos - offset_pos) << 16) / action->unk_96.s16_value;
        }
        if (action->unk_96.s16_value-- > 0) {
            return;
        }
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        action->unk_9B++;

        switch (action->unk_AC) {
        case 0:
            anim_table = D_801739A0;
            if (sprite->unk_2C == anim_table) {
                return;
            }
            *(u8 **)((u8 *)sprite + 0x2C) = anim_table;
            func_80047784(
                sprite,
                anim_table[((D_80083228 + actor->unk_2A + 0x100) >> 9) & 7],
                0);
            return;
        case 1:
            current_anim = sprite->unk_2C;
            anim_table = D_801739A8;
            if (current_anim == anim_table) {
                return;
            }
            *(u8 **)((u8 *)sprite + 0x2C) = anim_table;
            func_80047784(
                sprite,
                anim_table[((D_80083228 + actor->unk_2A + 0x100) >> 9) & 7],
                0);
            return;
        case 2:
            current_anim = sprite->unk_2C;
            anim_table = D_801739B0;
            if (current_anim == anim_table) {
                return;
            }
            *(u8 **)((u8 *)sprite + 0x2C) = anim_table;
            func_80047784(
                sprite,
                anim_table[((D_80083228 + actor->unk_2A + 0x100) >> 9) & 7],
                0);
            return;
        case 3:
            anim_table = D_801739B8;
            if (sprite->unk_2C == anim_table) {
                return;
            }
            *(u8 **)((u8 *)sprite + 0x2C) = anim_table;
            func_80047784(
                sprite,
                anim_table[((D_80083228 + actor->unk_2A + 0x100) >> 9) & 7],
                0);
            return;
        default:
            return;
        }

    case 3:
        if (D_80175DC1 != 0) {
            if (D_80175DC0 == 0) {
                return;
            }
            if (actor->unk_28 == 0) {
                action->unk_96.s16_value = 0;
                action->unk_9B += 2;
                return;
            }
            action->unk_96.s16_value = 0;
            action->unk_9B++;
            func_800A56E0(0x300);
            return;
        }
        action->unk_9B += 2;
        return;

    case 4:
        frame_count = ++action->unk_96.u16_value;
        if (frame_count < 0x50) {
            return;
        }
        action->unk_9B++;
        return;

    case 5:
        if (actor->unk_28 == 0) {
            motion->unk_14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            switch (action->unk_AC) {
            case 0:
                func_800AAA54(action, motion, sprite, D_80173A20);
                return;
            case 1:
                func_800AAA54(action, motion, sprite, D_80173A28);
                return;
            case 2:
                func_800AAA54(action, motion, sprite, D_80173A30);
                return;
            case 3:
                func_800AAA54(action, motion, sprite, D_80173A38);
                return;
            default:
                return;
            }
        }

        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, sprite->unk_24, sprite->unk_25);
        world_state = (S_func_8016C64C_4 *)&D_80083460;
        if (world_state->unk_10.ptr == (u8 *)actor - 0x20) {
            world_state->unk_10.u32_value &= 0x7FFFFFFF;
        }
        action->unk_8C = D_8016A36C;
        return;
    }
}
