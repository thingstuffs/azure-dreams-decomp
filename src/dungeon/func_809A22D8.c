#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

#define FIELD_U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define FIELD_S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define FIELD_U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define FIELD_S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FIELD_PTR(p, o) (*(void **)((u8 *)(p) + (o)))

extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *actor, void *unused, void *display, u8 *facing_variants);
extern void func_800AD4D0(void *);
extern s32 D_801710EC[];
extern u8 D_80175E90[];

/* Decays motion, then aligns the actor with its grid position. */
void func_80173AD8(void *action, void *motion, void *actor, void *source) {
    s32 state;
    s32 x_velocity;
    s32 z_velocity;
    s32 x_rounding;
    s32 z_rounding;
    s32 tile_coord;
    s32 center_offset;
    s16 motion_frames;
    s32 align_frames;
    s16 next_frames;

    switch (FIELD_U8(action, 0x9B)) {
    case 0:
        func_800AD4D0(source);
        FIELD_U8(action, 0x9B) = FIELD_U8(action, 0x9B) + 1;
        if (FIELD_U8(source, 0x28) == 0) {
            FIELD_S32(motion, 0x14) = 0;
            FIELD_S32(motion, 0x10) = 0;
            FIELD_S32(motion, 0xC) = 0;
            func_800AAA54(action, motion, actor, D_80175E90);
            return;
        }
        if (FIELD_U16(actor, 0x14) & 0x8000) {
            FIELD_S16(action, 0x96) = 0;
            FIELD_U8(action, 0x9B) = 2;
            return;
        }
        FIELD_S32(motion, 0xC) =
            (-*(s16 *)((u8 *)dirStepX + ((FIELD_U16(source, 0x6A) >> 8) & 0xE))) << 15;
        FIELD_S32(motion, 0x10) =
            (-*(s16 *)((u8 *)dirStepY + ((FIELD_U16(source, 0x6A) >> 8) & 0xE))) << 15;
        motion_frames = -1;
        if (FIELD_S32(source, 0x1C) & 0x228) {
            motion_frames = 8;
        }
        FIELD_S16(action, 0x96) = motion_frames;


    case 1:
        x_velocity = FIELD_S32(motion, 0xC);
        x_rounding = x_velocity;
        if (x_velocity < 0) {
            x_rounding = x_velocity + 3;
        }
        z_velocity = FIELD_S32(motion, 0x10);
        FIELD_S32(motion, 0xC) = x_velocity - (x_rounding >> 2);
        z_rounding = z_velocity;
        FIELD_S32(motion, 0x10) = z_velocity - (z_rounding / 4);
        if (FIELD_S16(action, 0x96) > 0) {
            next_frames = FIELD_U16(action, 0x96) - 1;
            FIELD_S16(action, 0x96) = next_frames;
        } else if (FIELD_U16(actor, 0x14) & 0x6000) {
            FIELD_S16(action, 0x96) = 0;
        }
        if (FIELD_S16(action, 0x96) != 0) {
            return;
        }
        if (FIELD_U8(source, 0x28) == 0) {
            FIELD_S32(motion, 0x14) = 0;
            FIELD_S32(motion, 0x10) = 0;
            FIELD_S32(motion, 0xC) = 0;
            func_800AAA54(action, motion, actor, D_80175E90);
            return;
        }
        state = FIELD_U8(action, 0x9B);
        motion_frames = 8;
        FIELD_S16(action, 0x96) = motion_frames;
        FIELD_U8(action, 0x9B) = state + 1;
        return;

    case 2:
        align_frames = FIELD_S16(action, 0x96);
        if (align_frames != 0) {
            tile_coord = FIELD_U8(actor, 0x24);
            do {
                center_offset = FIELD_S16(motion, 2);
            } while (0);
            FIELD_S32(motion, 0xC) = (((tile_coord << 6) - (center_offset -= 0x20)) << 15) /
                                   align_frames;
            center_offset = FIELD_S16(motion, 6) - 0x20;
            FIELD_S32(motion, 0x10) = ((((FIELD_U8(actor, 0x25)) << 6) - center_offset) << 15) /
                                    FIELD_S16(action, 0x96);
        }
        next_frames = (u16)FIELD_S16(action, 0x96) - 1;
        FIELD_S16(action, 0x96) = next_frames;
        if ((next_frames << 16) > 0) {
            return;
        }
        FIELD_S32(motion, 0x14) = 0;
        FIELD_S32(motion, 0x10) = 0;
        FIELD_S32(motion, 0xC) = 0;
        func_800A2B04(motion, FIELD_U8(actor, 0x24), FIELD_U8(actor, 0x25));
        if (((s32)dungeonStatus.unk_10) == (s32)((u8 *)source - 0x20)) {
            *(s32 *)&dungeonStatus.unk_10 &= 0x7FFFFFFF;
        }
        FIELD_PTR(action, 0x8C) = D_801710EC;
        return;

    default:
        return;
    }
}
