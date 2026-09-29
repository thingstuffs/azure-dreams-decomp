#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_80ADF3AC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    u8 pad_A0[0x4];
    s32 unk_A4;
} S_80ADF3AC_0;   /* arg0 in func_80ADF3AC */






extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern s32 D_80159728;
extern u8 D_8015CDEC[];
extern u8 D_8015CE0C[];
extern u8 D_8015CE14[];

/* Updates movement toward a tile, its animation phases, and action completion. */
void func_80ADF3AC(void *action, EntityRec *motion, void *sprite, EntityRec *entity)
{
    s32 phase;
    s32 frames_left;
    s32 target_x;
    s32 pos_x;
    s32 height;
    s32 height_offset;
    s32 pos_y;
    s32 next_frame;
    s32 action_timer;
    s32 entity_flags;
    s32 target_distance;
    DungeonGlobalStatus *shared_state;
    phase = ((S_80ADF3AC_0 *)action)->unk_9B;
    switch (phase) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8015CE0C;
        func_80047784(
            sprite,
            D_8015CE0C[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        ((S_80ADF3AC_0 *)action)->unk_98 |= 8;
        entity->flags1C &= 0xF7FFFFFF;
        ((S_80ADF3AC_0 *)action)->unk_9E.s = 5;
        ((S_80ADF3AC_0 *)action)->unk_A4 = 0;
        ((S_80ADF3AC_0 *)action)->unk_9B++;
    case 1:
        frames_left = ((S_80ADF3AC_0 *)action)->unk_9E.s;
        ((S_80ADF3AC_0 *)action)->unk_90 -= ((S_80ADF3AC_0 *)action)->unk_A4;
        if (frames_left != 0) {
            target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;
            motion->unk_0C = ((target_x - pos_x) << 16) / frames_left;
            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->unk_10 =
                (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((S_80ADF3AC_0 *)action)->unk_9E.s;
            ((S_80ADF3AC_0 *)action)->unk_A4 =
                (-func_800644B8(((S_80ADF3AC_0 *)action)->unk_9E.s * 0x199)) << 10;
        }
        height = ((S_80ADF3AC_0 *)action)->unk_90;
        height_offset = ((S_80ADF3AC_0 *)action)->unk_A4;
        next_frame = ((S_80ADF3AC_0 *)action)->unk_9E.u;
        height += height_offset;
        next_frame -= 1;
        ((S_80ADF3AC_0 *)action)->unk_9E.u = next_frame;
        ((S_80ADF3AC_0 *)action)->unk_90 = height;
        if ((next_frame << 16) < 0) {
            ((S_80ADF3AC_0 *)action)->unk_90 = 0;
            ((S_80ADF3AC_0 *)action)->unk_98 &= 0xFFF7;
            entity->flags1C |= 0x08000000;
            ((S_80ADF3AC_0 *)action)->unk_9B++;
        }
    case 2:
        if (entity->flags1C & 0x08000000) {
            ((S_80ADF3AC_0 *)action)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8015CE14;
            func_80047784(
                sprite,
                D_8015CE14[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            ((S_80ADF3AC_0 *)action)->unk_9B++;
        }
        break;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == D_8015CDEC) {
            break;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8015CDEC;
        func_80047784(
            sprite,
            D_8015CDEC[((gameWork.view.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
    }
    action_timer = ((S_80ADF3AC_0 *)action)->unk_96 - 1;
    ((S_80ADF3AC_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }
    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(entity, 4);
    func_800A4ACC(entity);
    shared_state = &dungeonStatus;
    if (shared_state->unk_08 != 0) {
        (*(u16 *)&shared_state->unk_08)--;
    }
    entity_flags = entity->flags1C;
    if (entity_flags & 0x2000) {
        if (entity->unk_46 & 0x8000) {
            entity->unk_46 &= 0x7FFF;
        }
    } else if (!(entity_flags & 0x410)) {
        if (entity_flags & 0x20000) {
            entity->facing = func_800A0818(
                ((Rec_D_80082E80 *)sprite)->unk_24,
                ((Rec_D_80082E80 *)sprite)->unk_25,
                D_80082E80.tileX,
                D_80082E80.tileY,
                &target_distance);
        }
    }
    if ((func_800AD9B4(sprite, entity) << 16) > 0) {
        ((S_80ADF3AC_0 *)action)->unk_8C = &D_80159728;
        func_800A9A04(entity);
    }
}
