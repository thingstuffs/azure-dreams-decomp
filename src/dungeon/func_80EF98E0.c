#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80EF98E0_0 {
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
} S_80EF98E0_0;   /* arg0 in func_80EF98E0 */

typedef struct S_80EF98E0_1 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80EF98E0_1;   /* arg3 in func_80EF98E0 */





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
extern s32 D_80159CE8;
extern u8 D_8015CEB8[];
extern u8 D_8015CED0[];
extern u8 D_8015CED8[];

/* Updates timed movement and animation, then finalizes the actor's action. */
void func_80EF98E0(void *action, void *motion, void *sprite, void *actor)
{
    s32 direction_aux;
    s32 move_state;
    s32 move_ticks;
    s32 actor_flags;
    s32 target_x;
    s32 position_x;
    s32 position_y;
    s16 next_tick;
    s16 *global_counters;
    u16 action_ticks;
    u8 *anim_table;

    move_state = ((S_80EF98E0_0 *)action)->unk_9B;
    if (move_state == 1) {
        goto state_one;
    }
    if (move_state < 2) {
        if (move_state == 0) {
            goto state_zero;
        }
        goto update_countdown;
    }
    if (move_state == 2) {
        goto state_two;
    }
    if (move_state == 3) {
        goto state_three;
    }
    goto update_countdown;

    state_zero:
    next_tick = ((S_80EF98E0_0 *)action)->unk_9E.s - 1;
    ((S_80EF98E0_0 *)action)->unk_9E.s = next_tick;
    if ((next_tick << 16) != 0) {
        goto update_countdown;
    }

    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8015CED0;
    func_80047784(
        sprite,
        D_8015CED0[((D_80083228 + ((S_80EF98E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80EF98E0_0 *)action)->unk_98 |= 8;
    ((S_80EF98E0_1 *)actor)->unk_1C.s &= 0xF7FFFFFF;
    ((S_80EF98E0_0 *)action)->unk_9E.u = 5;
    ((S_80EF98E0_0 *)action)->unk_A0 = 0;
    ((S_80EF98E0_0 *)action)->unk_9B++;

    state_one:
    move_ticks = ((S_80EF98E0_0 *)action)->unk_9E.u;
    ((S_80EF98E0_0 *)action)->unk_90 -= ((S_80EF98E0_0 *)action)->unk_A0;
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
            ((S_80EF98E0_0 *)action)->unk_9E.u;
        ((S_80EF98E0_0 *)action)->unk_A0 =
            (-func_800644B8(((S_80EF98E0_0 *)action)->unk_9E.u * 0x199)) << 10;
    }

    ((S_80EF98E0_0 *)action)->unk_90 += ((S_80EF98E0_0 *)action)->unk_A0;
    next_tick = ((S_80EF98E0_0 *)action)->unk_9E.s - 1;
    ((S_80EF98E0_0 *)action)->unk_9E.s = next_tick;
    if (next_tick < 0) {
        ((S_80EF98E0_0 *)action)->unk_90 = 0;
        ((S_80EF98E0_0 *)action)->unk_98 &= 0xFFF7;
        ((S_80EF98E0_1 *)actor)->unk_1C.s |= 0x08000000;
        ((S_80EF98E0_0 *)action)->unk_9B++;
    }

    state_two:
    if (((S_80EF98E0_1 *)actor)->unk_1C.s & 0x08000000) {
        ((S_80EF98E0_0 *)action)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_8015CED8;
        func_80047784(
            sprite,
            D_8015CED8[((D_80083228 + ((S_80EF98E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80EF98E0_0 *)action)->unk_9B++;
    }
    goto update_countdown;

    state_three:
    anim_table = D_8015CEB8;
    if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 != anim_table) {
        (*(u8 * *)((u8 *)sprite + 0x2C)) = anim_table;
        func_80047784(
            sprite,
            anim_table[((D_80083228 + ((S_80EF98E0_1 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    update_countdown:
    action_ticks = ((S_80EF98E0_0 *)action)->unk_96 - 1;
    ((S_80EF98E0_0 *)action)->unk_96 = action_ticks;
    if ((s16)action_ticks > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    global_counters = (s16 *)&D_80083460;
    if (global_counters[4] != 0) {
        global_counters[4]--;
    }

    actor_flags = ((S_80EF98E0_1 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((S_80EF98E0_1 *)actor)->unk_46 & 0x8000) {
            ((S_80EF98E0_1 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((S_80EF98E0_1 *)actor)->unk_2A = func_800A0818(
                ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
                D_80082E80[0x24], D_80082E80[0x25], &direction_aux);
        }
    }

    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_80EF98E0_0 *)action)->unk_8C = &D_80159CE8;
        func_800A9A04(actor);
    }
}
