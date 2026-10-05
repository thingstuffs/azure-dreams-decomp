#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_8014EC54_0 {
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
} S_8014EC54_0;   /* arg0 in func_8014EC54 */


extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern s32 D_8014D7F4;
extern u8 D_80151988[];
extern u8 D_801519A8[];
extern u8 D_801519B8[];

/* Updates a tile-centering hop animation and completes the entity's timed action. */
void func_8014EC54(void *action, void *motion, void *sprite, void *entity)
{
    s32 state;
    s32 hop_frames;
    s32 target_x;
    s32 pos_x;
    s32 height;
    s32 hop_offset;
    s32 pos_y;
    s32 next_hop_frames;
    s32 action_timer;
    s32 entity_flags;
    s32 direction_aux;
    DungeonGlobalStatus *global_base;

    state = ((S_8014EC54_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801519A8;
        func_80047784(
            sprite,
            D_801519A8[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((S_8014EC54_0 *)action)->unk_98 |= 8;
        ((EntityRec *)entity)->flags1C &= 0xF7FFFFFF;
        ((S_8014EC54_0 *)action)->unk_9E.s = 5;
        ((S_8014EC54_0 *)action)->unk_A4 = 0;
        ((S_8014EC54_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 1:
        hop_frames = ((S_8014EC54_0 *)action)->unk_9E.s;
        ((S_8014EC54_0 *)action)->unk_90 -= ((S_8014EC54_0 *)action)->unk_A4;
        if (hop_frames != 0) {
            target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / hop_frames;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((S_8014EC54_0 *)action)->unk_9E.s;

            ((S_8014EC54_0 *)action)->unk_A4 =
                (-func_800644B8(((S_8014EC54_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height = ((S_8014EC54_0 *)action)->unk_90;
        hop_offset = ((S_8014EC54_0 *)action)->unk_A4;
        next_hop_frames = ((S_8014EC54_0 *)action)->unk_9E.u;
        height += hop_offset;
        next_hop_frames -= 1;
        ((S_8014EC54_0 *)action)->unk_9E.u = next_hop_frames;
        ((S_8014EC54_0 *)action)->unk_90 = height;
        if ((next_hop_frames << 16) < 0) {
            ((S_8014EC54_0 *)action)->unk_90 = 0;
            ((S_8014EC54_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)entity)->flags1C |= 0x08000000;
            ((S_8014EC54_0 *)action)->unk_9B++;
        }
                        /* fallthrough */
    case 2:
        if (((EntityRec *)entity)->flags1C & 0x08000000) {
            ((S_8014EC54_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801519B8;
            func_80047784(
                sprite,
                D_801519B8[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
            ((S_8014EC54_0 *)action)->unk_9B++;
        }
        break;
    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != D_80151988) {
            (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80151988;
            func_80047784(
                sprite,
                D_80151988[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    action_timer = ((S_8014EC54_0 *)action)->unk_96 - 1;
    ((S_8014EC54_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(entity, 4);
    func_800A4ACC(entity);

    global_base = &dungeonStatus;
    if (global_base->unk_08 != 0) {
        (*(u16 *)&global_base->unk_08)--;
    }

    entity_flags = ((EntityRec *)entity)->flags1C;
    if (entity_flags & 0x2000) {
        if (((EntityRec *)entity)->unk_46 & 0x8000) {
            ((EntityRec *)entity)->unk_46 &= 0x7FFF;
        }
    } else {
        if (!(entity_flags & 0x410)) {
            if (entity_flags & 0x20000) {
                ((EntityRec *)entity)->facing = func_800A0818(
                    ((Rec_D_80082E80 *)sprite)->unk_24,
                    ((Rec_D_80082E80 *)sprite)->unk_25,
                    D_80082E80.tileX,
                    D_80082E80.tileY,
                    &direction_aux);
            }
        }
    }

    if ((func_800AD9B4(sprite, entity) << 16) > 0) {
        ((S_8014EC54_0 *)action)->unk_8C = &D_8014D7F4;
        func_800A9A04(entity);
    }
}
