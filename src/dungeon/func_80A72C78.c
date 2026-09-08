#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172478_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    s32 unk_A4;
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
} S_80172478_0;   /* arg0 in func_80172478 */


typedef struct S_80172478_2 {
    u8 pad_00[0x1C];
    union { u32 s; s32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
} S_80172478_2;   /* arg3 in func_80172478 */


typedef struct S_80172478_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172478_4;   /* global_base in func_80172478 */

typedef struct S_80172478_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172478_5;   /* map_base in func_80172478 */



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
extern u8 D_80170E54;
extern u8 D_80174160[];
extern u8 D_80174168[];

/* Updates the hop toward the target tile and finishes the action when its timer expires. */
void func_80172478(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 direction_aux;
    u8 *global_base;
    u8 *map_base;

    state = ((S_80172478_0 *)action)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto tick;
    }
    if (state == 2) {
        goto state_two;
    }
    goto tick;

state_zero:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        goto tick;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174160;
    func_80047784(
        sprite,
        D_80174160[((D_80083228 + ((S_80172478_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
        0);
    ((S_80172478_0 *)action)->unk_98 |= 8;
    ((S_80172478_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
    ((S_80172478_0 *)action)->unk_A8.s = 5;
    ((S_80172478_0 *)action)->unk_A4 = 0;
    ((S_80172478_0 *)action)->unk_9B++;

state_one:
    move_ticks = ((S_80172478_0 *)action)->unk_A8.s;
    ((S_80172478_0 *)action)->unk_90 -= ((S_80172478_0 *)action)->unk_A4;
    if (move_ticks != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        pos_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v;
        target_x <<= 6;
        pos_x -= 0x20;
        
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - pos_x) << 16) / move_ticks;

        pos_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v;
        pos_y -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - pos_y) << 16) /
            ((S_80172478_0 *)action)->unk_A8.s;

        ((S_80172478_0 *)action)->unk_A4 =
            (-func_800644B8(((S_80172478_0 *)action)->unk_A8.s * 0x199)) << 10;
    }

    height_offset = ((S_80172478_0 *)action)->unk_90;
    arc_offset = ((S_80172478_0 *)action)->unk_A4;
    next_move_ticks = ((S_80172478_0 *)action)->unk_A8.u;
    height_offset += arc_offset;
    next_move_ticks -= 1;
    ((S_80172478_0 *)action)->unk_A8.u = next_move_ticks;
    ((S_80172478_0 *)action)->unk_90 = height_offset;
    if ((next_move_ticks << 16) >= 0) {
        goto tick;
    }

    ((S_80172478_0 *)action)->unk_90 = 0;
    ((S_80172478_0 *)action)->unk_98 &= 0xFFF7;
    ((S_80172478_2 *)actor)->unk_1C.s |= 0x08000000;
    goto advance_state;

state_two:
    if (((S_80172478_2 *)actor)->unk_1C.s & 0x08000000) {
        ((S_80172478_0 *)action)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        (*(u8 * *)((u8 *)sprite + 0x2C)) = D_80174168;
        func_80047784(
            sprite,
            D_80174168[((D_80083228 + ((S_80172478_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);

advance_state:
        ((S_80172478_0 *)action)->unk_9B++;
    }

tick:
    action_ticks = ((S_80172478_0 *)action)->unk_96 - 1;
    ((S_80172478_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    global_base = (u8 *)&D_80083460;
    if (((S_80172478_4 *)global_base)->unk_08.s != 0) {
        ((S_80172478_4 *)global_base)->unk_08.u--;
    }

    actor_flags = ((S_80172478_2 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((S_80172478_2 *)actor)->unk_46 & 0x8000) {
            ((S_80172478_2 *)actor)->unk_46 &= 0x7FFF;
        }
        goto collision_check;
    }
    if (actor_flags & 0x410) {
        goto collision_check;
    }
    if (!(actor_flags & 0x20000)) {
        goto collision_check;
    }
    map_base = D_80082E80;
    ((S_80172478_2 *)actor)->unk_2A = func_800A0818(
        ((Rec_D_80082E80 *)sprite)->unk_24,
        ((Rec_D_80082E80 *)sprite)->unk_25,
        ((S_80172478_5 *)map_base)->unk_24,
        ((S_80172478_5 *)map_base)->unk_25,
        &direction_aux);

collision_check:
    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_80172478_0 *)action)->unk_8C = &D_80170E54;
        func_800A9A04(actor);
    }
}
