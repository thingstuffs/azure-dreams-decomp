#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 dungeonCheckNeighborTileBlocking();             /* extern */
s32 dungeonFindValidNearbyPosition();      /* extern */
void *dungeonPrepareDirectionalAttack(); /* extern */
void func_8009CE1C(); /* extern */
u8 func_8009FB34();                           /* extern */
s32 dungeonUpdateActorProximityFlag(); /* extern */
void dungeonSetRecordIntegerTileCenter();              /* extern */
void dungeonBeginActorRandomWarp(); /* extern */
s16 func_800BCB04();                   /* extern */


/* Advance tile movement, handle object contact, and finalize the stopping position. */
s32 dungeonUpdateThrownActorTravel(void *move_state, EntityRec *motion, Rec_D_80082E80 *tile_pos, EntityRec *actor) {
    u16 resolved_x;
    u16 resolved_y;
    s32 contact_tile_mask;
    s32 stop_tile_mask;
    s32 contact_flags;
    s32 stop_flags;
    u8 contact_x;
    u8 contact_y;
    u8 stop_x;
    u8 stop_y;
    s16 move_ticks;
    s32 target_x;
    s32 axis_pos;
    s16 ticks_left;
    s16 ground_height;
    void *hit_object;

    move_ticks = ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16;
    if (move_ticks != 0) {
        target_x = tile_pos->unk_24;
        axis_pos = motion->x.w.i;
        target_x <<= 6;
        axis_pos -= 0x20;
        motion->unk_0C = (s32) ((s32) ((target_x - axis_pos) << 0x10) / move_ticks);
        axis_pos = motion->y.w.i - 0x20;
        motion->unk_10 = (s32) ((s32) (((tile_pos->unk_25 << 6) - axis_pos)
            << 0x10) / (s16) ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16);
    }
    ticks_left = (u16) ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 - 1;
    ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        hit_object = dungeonPrepareDirectionalAttack(actor, tile_pos, ((s16)actor->unk_6A), 0, 0);
        if (hit_object != NULL) {
            func_8009CE1C(actor, 4, 1, 8, (s32) (s16) ((u16) ((s16)actor->unk_6A) + 0x800), 0, 1);
            func_8009CE1C(hit_object, 8, 1, 8, (s32) ((s16)actor->unk_6A), 0, 1);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_98 =
                (u16) (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 0xFFF7);
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            actor->flags1C = (s32) (actor->flags1C | 0x40000000);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_u8 = (u8) tile_pos->unk_26.as_u8;
            tile_pos->unk_26.as_u8 = func_8009FB34(tile_pos->unk_24, tile_pos->unk_25);
            dungeonUpdateActorProximityFlag(tile_pos, actor, 3, 6, move_state + 0x9C);
            if ((dungeonFindValidNearbyPosition(actor, tile_pos->unk_24, tile_pos->unk_25, &resolved_x, &resolved_y) << 0x10) == 0) {
                dungeonSetRecordIntegerTileCenter(motion, tile_pos->unk_24, tile_pos->unk_25);
                dungeonBeginActorRandomWarp(move_state, motion, tile_pos, actor);
                return 0;
            } else {
                tile_pos->unk_24 = resolved_x;
                tile_pos->unk_25 = resolved_y;
                dungeonSetRecordIntegerTileCenter(motion, tile_pos->unk_24, tile_pos->unk_25);
                contact_flags = actor->flags1C;
                contact_x = tile_pos->unk_24;
                contact_y = tile_pos->unk_25;
                contact_tile_mask = 0x3000;
                if (contact_flags & 0x2000) {
                    contact_tile_mask = 0x300;
                }
                func_8009A21C(contact_x, contact_y, contact_tile_mask);
                actor->flags1C = (s32) (actor->flags1C & 0xFFDFFFFF);
                dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
                ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 0;
                actor->unk_71 = 0;
                return 1;
            }
        }
        if ((dungeonCheckNeighborTileBlocking(((s16)actor->unk_6A), motion, tile_pos) << 0x10) != 0 && --actor->unk_8A > 0) {
            tile_pos->unk_24 = (u8) (tile_pos->unk_24 + *(((u16) ((s16)actor->unk_6A) >> 9 & 7) + dirStepX));
            tile_pos->unk_25 = (u8) (tile_pos->unk_25 + *(((u16) ((s16)actor->unk_6A) >> 9 & 7) + dirStepY));
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 2;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_98 =
                (u16) (((Rec_func_800A9E70_arg0 *)move_state)->unk_98 & 0xFFF7);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_9C.as_u8 = (u8) tile_pos->unk_26.as_u8;
            tile_pos->unk_26.as_u8 = func_8009FB34(tile_pos->unk_24, tile_pos->unk_25);
            dungeonUpdateActorProximityFlag(tile_pos, actor, 3, 6, move_state + 0x9C);
            ground_height = func_800BCB04((tile_pos->unk_24 << 6) | 0x20, (tile_pos->unk_25 << 6) | 0x20,
                (s16) (((u16)motion->z.w.i) - 0x20));
            if (ground_height < 0x200) {
                ((Rec_func_800A9E70_arg0 *)move_state)->unk_90.at02_s16.v = 0;
                actor->unk_88 = ground_height;
            }
            dungeonStatus.unk_0A = (u16) (((u16)dungeonStatus.unk_0A) - 1);
            ((Rec_func_800A9E70_arg0 *)move_state)->unk_96.as_s16 = 0;
            actor->flags1C = (s32) ((actor->flags1C | 0x40000000) & 0xFFDFFFFF);
            if ((dungeonFindValidNearbyPosition(actor, tile_pos->unk_24, tile_pos->unk_25, &resolved_x, &resolved_y) << 0x10) == 0) {
                dungeonSetRecordIntegerTileCenter(motion, tile_pos->unk_24, tile_pos->unk_25);
                dungeonBeginActorRandomWarp(move_state, motion, tile_pos, actor);
                return 0;
            } else {
                tile_pos->unk_24 = resolved_x;
                tile_pos->unk_25 = resolved_y;
                dungeonSetRecordIntegerTileCenter(motion, tile_pos->unk_24, tile_pos->unk_25);
                stop_flags = actor->flags1C;
                stop_x = tile_pos->unk_24;
                stop_y = tile_pos->unk_25;
                stop_tile_mask = 0x3000;
                if (stop_flags & 0x2000) {
                    stop_tile_mask = 0x300;
                }
                func_8009A21C(stop_x, stop_y, stop_tile_mask);
                actor->unk_71 = 0;
                return 1;
            }
        }
    }
    return 0;
}
