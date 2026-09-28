#include "common.h"
#include "shared/tile_object.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017406C_0 {
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
    s32 unk_A0;
} S_8017406C_0;   /* arg0 in func_8017406C */






extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_801724BC[];

/* Animate movement to the target tile and finalize the actor when the timer expires. */
void func_8017406C(S_8017406C_0 *animation, EntityRec *motion, Rec_D_80082E80 *tile, EntityRec *actor)
{
    s32 state;
    s32 arc_ticks;
    s32 target_x;
    s32 world_x;
    s32 height;
    s32 arc_offset;
    s32 world_y;
    s32 next_arc_ticks;
    s32 ticks_left;
    s32 actor_flags;
    s32 coord_result;
    DungeonGlobalStatus *global_base;

    state = animation->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto decrement_timer;
    }
    if (state == 2) {
        goto state_two;
    }
    goto decrement_timer;

state_zero:
    animation->unk_98 |= 8;
    actor->flags1C &= 0xF7FFFFFF;
    animation->unk_9E.s = 5;
    animation->unk_A0 = 0;
    animation->unk_9B++;

state_one:
    arc_ticks = animation->unk_9E.s;
    animation->unk_90 -= animation->unk_A0;
    if (arc_ticks != 0) {
        target_x = tile->unk_24;
        world_x = motion->x.w.i;
        target_x <<= 6;
        world_x -= 0x20;
        
        motion->unk_0C =
            ((target_x - world_x) << 16) / arc_ticks;

        world_y = motion->y.w.i;
        world_y -= 0x20;
        motion->unk_10 =
            (((tile->unk_25 << 6) - world_y) << 16) /
            animation->unk_9E.s;

        animation->unk_A0 =
            (-func_800644B8(animation->unk_9E.s * 0x199)) << 10;
    }

    height = animation->unk_90;
    arc_offset = animation->unk_A0;
    next_arc_ticks = animation->unk_9E.u;
    height += arc_offset;
    next_arc_ticks -= 1;
    animation->unk_9E.u = next_arc_ticks;
    animation->unk_90 = height;
    if ((next_arc_ticks << 16) >= 0) {
        goto state_two;
    }

    animation->unk_90 = 0;
    animation->unk_98 &= 0xFFF7;
    actor->flags1C |= 0x08000000;
    animation->unk_9B++;

state_two:
    if (actor->flags1C & 0x08000000) {
        animation->unk_98 &= 0xFFF7;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, tile->unk_24, tile->unk_25);
        animation->unk_9B++;
    }

decrement_timer:
    ticks_left = animation->unk_96 - 1;
    animation->unk_96 = ticks_left;
    if ((ticks_left << 16) > 0) {
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, tile->unk_24, tile->unk_25);
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    global_base = &dungeonStatus;
    if (global_base->unk_08 != 0) {
        (*(u16 *)&global_base->unk_08)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->unk_46 & 0x8000) {
            actor->unk_46 &= 0x7FFF;
        }
        goto collision_check;
    }
    if (actor_flags & 0x410) {
        goto collision_check;
    }
    if (!(actor_flags & 0x20000)) {
        goto collision_check;
    }
    actor->facing = func_800A0818(
        tile->unk_24,
        tile->unk_25,
        D_80082E80.tileX,
        D_80082E80.tileY,
        &coord_result);

collision_check:
    if ((func_800AD9B4(tile, actor) << 16) > 0) {
        animation->unk_8C = D_801724BC;
        func_800A9A04(actor);
    }
}
