#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct S_80173A08_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x4];
    s32 unk_A0;
    u8 pad_A4[0xC];
    union { s16 s; u16 u; } unk_B0;   /* accessed as both */
} S_80173A08_0;   /* arg0 in func_80173A08 */




typedef struct S_80173A08_4 {
    u8 pad_00[0x8];
    union { s16 s; u16 u; } unk_08;   /* accessed as both */
} S_80173A08_4;   /* global_base in func_80173A08 */

typedef struct S_80173A08_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173A08_5;   /* map_base in func_80173A08 */



extern void func_80047784(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800A2B04(void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A9A04(void *);
extern void func_800AD594(void *, s32);

extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171058[];
extern u8 D_801748A0[];
extern u8 D_801748A8[];
extern u8 D_801748B0[];

/* Advance a timed movement animation, snap the entity to its tile, and finish the action. */
void func_80173A08(void *action, void *motion, void *sprite, void *entity)
{
    s32 direction_work[2];
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 world_x;
    s32 arc_base;
    s32 arc_offset;
    s32 world_y;
    s32 height_offset;
    s32 next_move_ticks;
    s32 entity_mask;
    s32 action_ticks;
    s32 entity_flags;
    s32 facing_index;
    u8 *global_base;
    u8 *map_base;

    state = ((S_80173A08_0 *)action)->unk_9B;
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
    if (state == 3) {
        goto state_three;
    }
    goto tick;

state_zero:
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        goto tick;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801748A0;
    facing_index = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(sprite, D_801748A0[facing_index & 7], 0);
    ((S_80173A08_0 *)action)->unk_98 |= 8;
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 &= 0xF7FFFFFF;
    ((S_80173A08_0 *)action)->unk_B0.s = 5;
    ((S_80173A08_0 *)action)->unk_A0 = 0;
    ((S_80173A08_0 *)action)->unk_9B++;
    goto tick;

state_one:
    ((S_80173A08_0 *)action)->unk_90 += 0xC0000;
    if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
        goto tick;
    }
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801748A8;
    facing_index = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(sprite, D_801748A8[facing_index & 7], 0);
    ((S_80173A08_0 *)action)->unk_98 |= 8;
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 &= 0xF7FFFFFF;
    ((S_80173A08_0 *)action)->unk_B0.s = 5;
    ((S_80173A08_0 *)action)->unk_A0 = 0;
    ((S_80173A08_0 *)action)->unk_90 -= 0x400000;
    ((S_80173A08_0 *)action)->unk_9B++;

state_two:
    move_ticks = ((S_80173A08_0 *)action)->unk_B0.s;
    ((S_80173A08_0 *)action)->unk_90 -= ((S_80173A08_0 *)action)->unk_A0;
    if (move_ticks != 0) {
        target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
        world_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v;
        target_x <<= 6;
        world_x -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = ((target_x - world_x) << 16) / move_ticks;

        world_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v;
        world_y -= 0x20;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - world_y) << 16) /
            ((S_80173A08_0 *)action)->unk_B0.s;

        arc_base = (0 - func_800644B8(((S_80173A08_0 *)action)->unk_B0.s * 0x199)) << 10;
        ((S_80173A08_0 *)action)->unk_A0 = arc_base + (arc_base >> 1);
    }

    height_offset = ((S_80173A08_0 *)action)->unk_90;
    arc_offset = ((S_80173A08_0 *)action)->unk_A0;
    next_move_ticks = ((S_80173A08_0 *)action)->unk_B0.u;
    height_offset += arc_offset;
    next_move_ticks -= 1;
    ((S_80173A08_0 *)action)->unk_B0.u = next_move_ticks;
    ((S_80173A08_0 *)action)->unk_90 = height_offset;
    if ((next_move_ticks << 16) >= 0) {
        goto state_three;
    }

    entity_mask = 0x08000000;
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_80173A08_0 *)action)->unk_90 = 0;
    ((S_80173A08_0 *)action)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 |= entity_mask;
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801748B0;
    facing_index = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(sprite, D_801748B0[facing_index & 7], 0);
    ((S_80173A08_0 *)action)->unk_9B++;

state_three:
    if (!(((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x08000000)) {
        goto tick;
    }
    ((S_80173A08_0 *)action)->unk_98 &= 0xFFF7;
    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    (*(u8 * *)((u8 *)sprite + 0x2C)) = D_801748B0;
    facing_index = (D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9;
    func_80047784(sprite, D_801748B0[facing_index & 7], 0);
    ((S_80173A08_0 *)action)->unk_9B++;

tick:
    action_ticks = ((S_80173A08_0 *)action)->unk_96 - 1;
    ((S_80173A08_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
    ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
    ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
    func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    func_800AD594(entity, 4);
    func_800A4ACC(entity);

    global_base = (u8 *)&D_80083460;
    if (((S_80173A08_4 *)global_base)->unk_08.s != 0) {
        ((S_80173A08_4 *)global_base)->unk_08.u--;
    }

    entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32;
    if (entity_flags & 0x2000) {
        if (((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v & 0x8000) {
            ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v &= 0x7FFF;
        }
        goto finish;
    }
    if (entity_flags & 0x410) {
        goto finish;
    }
    if (entity_flags & 0x20000) {
        map_base = D_80082E80;
        ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 = func_800A0818(
            ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25,
            ((S_80173A08_5 *)map_base)->unk_24, ((S_80173A08_5 *)map_base)->unk_25, direction_work);
    }

finish:
    ((S_80173A08_0 *)action)->unk_8C = D_80171058;
    func_800A9A04(entity);
}
