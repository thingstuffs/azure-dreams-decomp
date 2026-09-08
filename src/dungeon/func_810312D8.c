#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80172AD8_0 {
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
} S_80172AD8_0;   /* arg0 in func_80172AD8 */




typedef struct S_80172AD8_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80172AD8_4;   /* global_base in func_80172AD8 */

typedef struct S_80172AD8_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172AD8_5;   /* map_base in func_80172AD8 */



extern void func_80047784(void *, s16, s16);
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
extern u8 D_801714B8;
extern u8 D_801760BC;
extern u8 D_801760C4;

/* Updates the actor's hop animation and finishes the timed movement at its destination tile. */
void func_80172AD8(void *action, void *motion, void *sprite, void *actor)
{
    s32 direction_aux;
    s32 state;
    s32 move_frames;
    s32 target_x;
    s32 position_component;
    s32 height;
    s32 height_offset;
    s32 frame_count;
    s32 action_timer;
    s32 actor_flags;
    u8 *global_base;
    u8 *map_base;

    state = ((S_80172AD8_0 *)action)->unk_9B;
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
    if (state == 3) {
        goto state_three;
    }
    goto decrement_timer;

state_zero:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        goto decrement_timer;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = &D_801760BC;
    func_80047784(
        sprite,
        *(&D_801760BC +
          (((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)),
        0);
    ((S_80172AD8_0 *)action)->unk_98 |= 8;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 &= 0xF7FFFFFF;
    ((S_80172AD8_0 *)action)->unk_9E.s = 5;
    ((S_80172AD8_0 *)action)->unk_A4 = 0;
    ((S_80172AD8_0 *)action)->unk_9B++;

state_one:
    ((S_80172AD8_0 *)action)->unk_90 -= ((S_80172AD8_0 *)action)->unk_A4;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at00_s16.v = 0xC00;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at02_s16.v = 0x1400;
    move_frames = ((S_80172AD8_0 *)action)->unk_9E.s;
    if (move_frames != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        position_component = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v;
        target_x <<= 6;
        position_component -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - position_component) << 16) / move_frames;

        position_component = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - position_component) << 16) /
            ((S_80172AD8_0 *)action)->unk_9E.s;
        ((S_80172AD8_0 *)action)->unk_A4 =
            (-func_800644B8(((S_80172AD8_0 *)action)->unk_9E.s * 0x199)) << 9;
    }

    height = ((S_80172AD8_0 *)action)->unk_90;
    height_offset = ((S_80172AD8_0 *)action)->unk_A4;
    frame_count = ((S_80172AD8_0 *)action)->unk_9E.u;
    height += height_offset;
    frame_count -= 1;
    ((S_80172AD8_0 *)action)->unk_9E.u = frame_count;
    ((S_80172AD8_0 *)action)->unk_90 = height;
    if ((frame_count << 16) >= 0) {
        goto state_two;
    }

    ((S_80172AD8_0 *)action)->unk_90 = 0;
    ((S_80172AD8_0 *)action)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 |= 0x08000000;
    ((S_80172AD8_0 *)action)->unk_9B++;

state_two:
    if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x08000000) {
        ((S_80172AD8_0 *)action)->unk_98 &= 0xFFF7;
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
        ((Rec_D_80082E80 *)sprite)->unk_1C.at00_s16.v = 0x1400;
        ((Rec_D_80082E80 *)sprite)->unk_1C.at02_s16.v = 0xC00;
        (*(u8 * *)((u8 *)sprite + 0x2C)) = &D_801760C4;
        func_80047784(
            sprite,
            *(&D_801760C4 +
              (((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7)),
            0);
        ((S_80172AD8_0 *)action)->unk_9B++;
        goto decrement_timer;
    }
    goto decrement_timer;

state_three:
    ((Rec_D_80082E80 *)sprite)->unk_1C.at00_s16.v = 0x1000;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at02_s16.v = 0x1000;

decrement_timer:
    action_timer = ((S_80172AD8_0 *)action)->unk_96 - 1;
    ((S_80172AD8_0 *)action)->unk_96 = action_timer;
    if ((action_timer << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    ((Rec_D_80082E80 *)sprite)->unk_1C.at00_s16.v = 0x1000;
    ((Rec_D_80082E80 *)sprite)->unk_1C.at02_s16.v = 0x1000;
    func_800AD594(actor, 4);
    func_800A4ACC(actor);

    global_base = (u8 *)&D_80083460;
    if (((S_80172AD8_4 *)global_base)->unk_08.s != 0) {
        ((S_80172AD8_4 *)global_base)->unk_08.u--;
    }

    actor_flags = ((Rec_D_800E3D7C *)actor)->unk_1C.as_s32;
    if (actor_flags & 0x2000) {
        if (((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v & 0x8000) {
            ((Rec_D_800E3D7C *)actor)->unk_44.at02_u16.v &= 0x7FFF;
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
    ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 = func_800A0818(
        ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
        ((S_80172AD8_5 *)map_base)->unk_24, ((S_80172AD8_5 *)map_base)->unk_25, &direction_aux);

collision_check:
    if ((func_800AD9B4(sprite, actor) << 16) > 0) {
        ((S_80172AD8_0 *)action)->unk_8C = &D_801714B8;
        func_800A9A04(actor);
    }
}
