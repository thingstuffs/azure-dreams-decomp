#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_8014F0E0_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { u16 s; s16 u; } unk_9E;   /* accessed as both */
    s32 unk_A0;
} S_8014F0E0_0;   /* arg0 in func_8014F0E0 */

typedef struct S_8014F0E0_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_8014F0E0_1;   /* arg3 in func_8014F0E0 */





extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);
extern s32 func_800AD9B4(void *, void *);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern s32 D_8014DCE8;
extern u8 D_80150EB8[];
extern u8 D_80150ED0[];
extern u8 D_80150ED8[];

/* Updates a timed hop to the actor's tile and restores its idle animation. */
void func_8014F0E0(void *action, void *motion, void *sprite, void *actor)
{
    s32 facing_aux;
    s32 phase;
    s32 move_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 position_x;
    s32 position_y;
    s16 phase_timer;
    s16 *action_counters;
    u16 action_timer;
    u8 *idle_anims;

    phase = ((S_8014F0E0_0 *)action)->unk_9B;
    if (phase == 1) {
        goto hop;
    }
    if (phase < 2) {
        if (phase == 0) {
            goto wait_to_hop;
        }
        goto update_countdown;
    }
    if (phase == 2) {
        goto land;
    }
    if (phase == 3) {
        goto idle;
    }
    goto update_countdown;

wait_to_hop:
    phase_timer = ((S_8014F0E0_0 *)action)->unk_9E.s - 1;
    ((S_8014F0E0_0 *)action)->unk_9E.s = phase_timer;
    if ((phase_timer << 16) != 0) {
        goto update_countdown;
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80150ED0;
    func_80047784(
        sprite,
        D_80150ED0[((D_80083228 + ((S_8014F0E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_8014F0E0_0 *)action)->unk_98 |= 8;
    ((S_8014F0E0_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
    ((S_8014F0E0_0 *)action)->unk_9E.u = 5;
    ((S_8014F0E0_0 *)action)->unk_A0 = 0;
    ((S_8014F0E0_0 *)action)->unk_9B++;

hop:
    move_ticks = ((S_8014F0E0_0 *)action)->unk_9E.u;
    ((S_8014F0E0_0 *)action)->unk_90 -= ((S_8014F0E0_0 *)action)->unk_A0;
    if (move_ticks != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        position_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v;
        target_x <<= 6;
        position_x -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - position_x) << 16) / move_ticks;

        position_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v;
        position_y -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - position_y) << 16) /
            ((S_8014F0E0_0 *)action)->unk_9E.u;
        ((S_8014F0E0_0 *)action)->unk_A0 =
            (-func_800644B8(((S_8014F0E0_0 *)action)->unk_9E.u * 0x199)) << 10;
    }

    ((S_8014F0E0_0 *)action)->unk_90 += ((S_8014F0E0_0 *)action)->unk_A0;
    phase_timer = ((S_8014F0E0_0 *)action)->unk_9E.s - 1;
    ((S_8014F0E0_0 *)action)->unk_9E.s = phase_timer;
    if (phase_timer < 0) {
        ((S_8014F0E0_0 *)action)->unk_90 = 0;
        ((S_8014F0E0_0 *)action)->unk_98 &= 0xFFF7;
        ((S_8014F0E0_1 *)actor)->unk_1C.s |= 0x08000000;
        ((S_8014F0E0_0 *)action)->unk_9B++;
    }

land:
    if (((S_8014F0E0_1 *)actor)->unk_1C.s & 0x08000000) {
        ((S_8014F0E0_0 *)action)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80150ED8;
        func_80047784(
            sprite,
            D_80150ED8[((D_80083228 + ((S_8014F0E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_8014F0E0_0 *)action)->unk_9B++;
    }
    goto update_countdown;

idle:
    idle_anims = D_80150EB8;
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != idle_anims) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = idle_anims;
        func_80047784(
            sprite,
            idle_anims[((D_80083228 + ((S_8014F0E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

update_countdown:
    action_timer = ((S_8014F0E0_0 *)action)->unk_96 - 1;
    ((S_8014F0E0_0 *)action)->unk_96 = action_timer;
    if ((s16)action_timer > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    action_counters = (s16 *)&D_80083460;
    if (action_counters[4] != 0) {
        action_counters[4]--;
    }

    actor_flags = ((S_8014F0E0_1 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((S_8014F0E0_1 *)actor)->unk_46 & 0x8000) {
            ((S_8014F0E0_1 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((S_8014F0E0_1 *)actor)->unk_2A = func_800A0818(
                ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                D_80082E80[0x24], D_80082E80[0x25], &facing_aux);
        }
    }

    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_8014F0E0_0 *)action)->unk_8C = &D_8014DCE8;
        func_800A9A04(actor);
    }
}
