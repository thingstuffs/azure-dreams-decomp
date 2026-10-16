/* Relink of matched dungeon/func_80D90ABC; every changed retail word is a paired relocation. */
#define D_80170E68 D_80164E68
#define D_80173884 D_80167884
#define D_8017388C D_8016788C
#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801722BC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    union { s16 s; u16 u; } unk_A4;   /* accessed as both */
} S_801722BC_0;   /* arg0 in func_801662BC */


typedef struct S_801722BC_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_801722BC_2;   /* arg3 in func_801662BC */


extern void func_80047784(void *, s32, s32);
extern s16 dungeonGetRoundedFacingAndRoundingFlag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void dungeonSetRecordIntegerTileCenter(void *, s32, s32);
extern void dungeonAdvanceStatusTimers(void *);
extern void func_800A9A04(void *);
extern void dungeonReduceActorFoodMeter(void *, s32);
extern s32 dungeonCheckActorFloorTrap(void *, void *);

extern u8 D_80164E68[];
extern u8 D_80167884[];
extern u8 D_8016788C[];

/* Updates airborne movement, landing animation, and actor recovery when the timer expires. */
void func_801662BC(void *anim, void *motion, void *entity, void *actor)
{
    s32 direction_aux;
    s32 move_ticks;
    s32 origin_x;
    s32 origin_y;
    s32 height_offset;
    s32 height;
    s32 arc_ticks;
    s32 target_x;
    s16 next_tick;
    s32 actor_flags;
    u16 remaining_ticks;
    s32 phase;
    DungeonGlobalStatus *counter_base;

    phase = ((S_801722BC_0 *)anim)->unk_9B;
    switch (phase) {
    case 0:
        if (!(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_80167884;
        func_80047784(
            entity,
            D_80167884[((gameWork.view.viewAngle + ((S_801722BC_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801722BC_0 *)anim)->unk_98 |= 8;
        ((S_801722BC_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((EntityRec *)motion)->flags14 = 0xFFF00000;
        ((S_801722BC_0 *)anim)->unk_A0 = 0;
        ((S_801722BC_0 *)anim)->unk_9B++;
    case 1:
        move_ticks = ((S_801722BC_0 *)anim)->unk_A4.s;
        ((S_801722BC_0 *)anim)->unk_90 =
            ((S_801722BC_0 *)anim)->unk_90 - ((S_801722BC_0 *)anim)->unk_A0;
        if (move_ticks != 0) {
            target_x = ((Rec_D_80082E80 *)entity)->unk_24 << 6;
            origin_x = ((EntityRec *)motion)->x.w.i - 0x20;
            origin_y = ((EntityRec *)motion)->y.w.i - 0x20;
            ((EntityRec *)motion)->unk_0C =
                ((target_x - origin_x) << 16) /
                move_ticks;
            ((EntityRec *)motion)->unk_10 =
                (((((Rec_D_80082E80 *)entity)->unk_25 << 6) - origin_y) << 16) /
                (s16)((S_801722BC_0 *)anim)->unk_A4.s;
            arc_ticks = ((S_801722BC_0 *)anim)->unk_A4.s;
            ((EntityRec *)motion)->flags14 += (arc_ticks << 15) + (arc_ticks << 13);
            ((S_801722BC_0 *)anim)->unk_A0 += ((EntityRec *)motion)->flags14;
        }
        height = ((S_801722BC_0 *)anim)->unk_90;
        height_offset = ((S_801722BC_0 *)anim)->unk_A0;
        next_tick = ((S_801722BC_0 *)anim)->unk_A4.u - 1;
        height += height_offset;
        ((S_801722BC_0 *)anim)->unk_A4.s = next_tick;
        ((S_801722BC_0 *)anim)->unk_90 = height;
        if (next_tick < 0) {
            ((S_801722BC_0 *)anim)->unk_90 = 0;
            ((S_801722BC_0 *)anim)->unk_98 &= 0xFFF7;
            ((S_801722BC_2 *)actor)->unk_1C.s |= 0x08000000;
            ((S_801722BC_0 *)anim)->unk_9B++;
        }
    case 2:
        if (((S_801722BC_2 *)actor)->unk_1C.s & 0x08000000) {
            ((S_801722BC_0 *)anim)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25);
            (*(u8 * *)((u8 *)entity + 0x2C)) = D_8016788C;
            func_80047784(
                entity,
                D_8016788C[((gameWork.view.viewAngle + ((S_801722BC_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801722BC_0 *)anim)->unk_9B++;
        }
    }

    remaining_ticks = ((S_801722BC_0 *)anim)->unk_96 - 1;
    ((S_801722BC_0 *)anim)->unk_96 = remaining_ticks;
    if ((remaining_ticks << 16) <= 0) {
        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        dungeonSetRecordIntegerTileCenter(motion, ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25);
        dungeonReduceActorFoodMeter(actor, 4);
        dungeonAdvanceStatusTimers(actor);

        counter_base = &dungeonStatus;
        if (counter_base->unk_08 != 0) {
            (*(u16 *)&counter_base->unk_08)--;
        }

        actor_flags = ((S_801722BC_2 *)actor)->unk_1C.u;
        if (actor_flags & 0x2000) {
            if (((S_801722BC_2 *)actor)->unk_46 & 0x8000) {
                ((S_801722BC_2 *)actor)->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                ((S_801722BC_2 *)actor)->unk_2A = dungeonGetRoundedFacingAndRoundingFlag(
                    ((Rec_D_80082E80 *)entity)->unk_24, ((Rec_D_80082E80 *)entity)->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &direction_aux);
            }
        }

        if ((dungeonCheckActorFloorTrap(entity, actor) << 16) > 0) {
            ((S_801722BC_0 *)anim)->unk_8C = D_80164E68;
            func_800A9A04(actor);
        }
    }
}

/* MECHANISM: Four held arguments naturally give the 0x38 frame and s0/s1/s3/s2 save order.
   Named coordinate/delta and position/offset locals close both load-order residues.
   A guarded v0 timer pin plus a pre-load scheduling fence preserves the mflo nop and shift roles. */
