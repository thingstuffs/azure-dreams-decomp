#include "common.h"

#define FIELD(ptr, type, off) (*(type *)((u8 *)(ptr) + (off)))

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
void func_8016C64C(void *action, void *motion, void *sprite, void *actor)
{
    s16 target_distance;
    s16 frame_count;
    s32 tile_pos;
    s32 offset_pos;
    u8 *anim_table;
    u8 *current_anim;
    u8 *world_state;

    switch (FIELD(action, u8, 0x9B)) {
    case 0:
        FIELD(actor, s16, 0x64) = 0;
        FIELD(action, u8, 0x9B)++;
        D_80175DC1 = 0;
        FIELD(action, s16, 0x96) = 6;
        if (FIELD(action, u8, 0xB0) < 2) {
            return;
        }
        FIELD(actor, s16, 0x2A) = func_800A0818(
            FIELD(sprite, u8, 0x24), FIELD(sprite, u8, 0x25),
            D_80082E80[0x24], D_80082E80[0x25], &target_distance);
        FIELD(action, s16, 0x94) = 1;
        return;

    case 1:
        frame_count = --FIELD(action, u16, 0x96);
        if (frame_count > 0) {
            FIELD(motion, s32, 0xC) =
                FIELD((u8 *)&D_8006CCD8,
                      s16, (FIELD(actor, u16, 0x6A) >> 8) & 0xE) << 18;
            FIELD(motion, s32, 0x10) =
                FIELD((u8 *)&D_8006CCE8,
                      s16, (FIELD(actor, u16, 0x6A) >> 8) & 0xE) << 18;
            return;
        }
        if (frame_count != 0) {
            return;
        }
        FIELD(motion, s32, 0xC) =
            FIELD((u8 *)&D_8006CCD8,
                  s16, (FIELD(actor, u16, 0x6A) >> 8) & 0xE) << 18;
        FIELD(motion, s32, 0x10) =
            FIELD((u8 *)&D_8006CCE8,
                  s16, (FIELD(actor, u16, 0x6A) >> 8) & 0xE) << 18;
        FIELD(action, s16, 0x96) = 8;
        FIELD(action, u8, 0x9B)++;
        return;

    case 2:
        frame_count = FIELD(action, s16, 0x96);
        if (frame_count != 0) {
            tile_pos = FIELD(sprite, u8, 0x24) << 6;
            offset_pos = FIELD(motion, s16, 2);
            offset_pos -= 0x20;
            FIELD(motion, s32, 0xC) =
                ((tile_pos - offset_pos) << 16) / frame_count;
            tile_pos = FIELD(sprite, u8, 0x25) << 6;
            offset_pos = FIELD(motion, s16, 6);
            offset_pos -= 0x20;
            FIELD(motion, s32, 0x10) =
                ((tile_pos - offset_pos) << 16) / FIELD(action, s16, 0x96);
        }
        if (FIELD(action, s16, 0x96)-- > 0) {
            return;
        }
        FIELD(motion, s32, 0x14) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0xC) = 0;
        FIELD(action, u8, 0x9B)++;

        switch (FIELD(action, u8, 0xAC)) {
        case 0:
            anim_table = D_801739A0;
            if (FIELD(sprite, u8 *, 0x2C) == anim_table) {
                return;
            }
            FIELD(sprite, u8 *, 0x2C) = anim_table;
            func_80047784(
                sprite,
                anim_table[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            return;
        case 1:
            current_anim = FIELD(sprite, u8 *, 0x2C);
            anim_table = D_801739A8;
            if (current_anim == anim_table) {
                return;
            }
            FIELD(sprite, u8 *, 0x2C) = anim_table;
            func_80047784(
                sprite,
                anim_table[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            return;
        case 2:
            current_anim = FIELD(sprite, u8 *, 0x2C);
            anim_table = D_801739B0;
            if (current_anim == anim_table) {
                return;
            }
            FIELD(sprite, u8 *, 0x2C) = anim_table;
            func_80047784(
                sprite,
                anim_table[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
            return;
        case 3:
            anim_table = D_801739B8;
            if (FIELD(sprite, u8 *, 0x2C) == anim_table) {
                return;
            }
            FIELD(sprite, u8 *, 0x2C) = anim_table;
            func_80047784(
                sprite,
                anim_table[((D_80083228 + FIELD(actor, s16, 0x2A) + 0x100) >> 9) & 7],
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
            if (FIELD(actor, u8, 0x28) == 0) {
                FIELD(action, s16, 0x96) = 0;
                FIELD(action, u8, 0x9B) += 2;
                return;
            }
            FIELD(action, s16, 0x96) = 0;
            FIELD(action, u8, 0x9B)++;
            func_800A56E0(0x300);
            return;
        }
        FIELD(action, u8, 0x9B) += 2;
        return;

    case 4:
        frame_count = ++FIELD(action, u16, 0x96);
        if (frame_count < 0x50) {
            return;
        }
        FIELD(action, u8, 0x9B)++;
        return;

    case 5:
        if (FIELD(actor, u8, 0x28) == 0) {
            FIELD(motion, s32, 0x14) = 0;
            FIELD(motion, s32, 0x10) = 0;
            FIELD(motion, s32, 0xC) = 0;
            switch (FIELD(action, u8, 0xAC)) {
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

        FIELD(motion, s32, 0x14) = 0;
        FIELD(motion, s32, 0x10) = 0;
        FIELD(motion, s32, 0xC) = 0;
        func_800A2B04(motion, FIELD(sprite, u8, 0x24), FIELD(sprite, u8, 0x25));
        world_state = (u8 *)&D_80083460;
        if (FIELD(world_state, u8 *, 0x10) == (u8 *)actor - 0x20) {
            FIELD(world_state, u32, 0x10) &= 0x7FFFFFFF;
        }
        FIELD(action, u8 *, 0x8C) = D_8016A36C;
        return;
    }
}
