#include "common.h"

typedef struct S_80171A18_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171A18_0;   /* arg3 in func_80171A18 */

typedef struct S_80171A18_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171A18_1;   /* arg2 in func_80171A18 */

typedef struct S_80171A18_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171A18_2;   /* cell in func_80171A18 */

typedef struct S_80171A18_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_80171A18_3;   /* arg0 in func_80171A18 */

typedef struct S_80171A18_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171A18_4;   /* (u8 *)arg3 + ((S_80171A18_0 *)arg3)->unk_8A.s in func_80171A18 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801740E0[];
extern u8 D_801740E8[];

/* Advances the actor along its queued path and updates movement timing. */
void func_80171A18(void *motion, s32 unused, void *actor, void *move_state) {
    void *next_cell;
    u8 *anim_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 occupancy_mask;
    s32 move_offset;
    s32 remaining_offset;

    if (((S_80171A18_0 *)move_state)->unk_71.s <= 0) {
        return;
    }
    if (((S_80171A18_0 *)move_state)->unk_71.u <= ((S_80171A18_0 *)move_state)->unk_8A.s) {
        return;
    }

    anim_table = ((S_80171A18_1 *)actor)->unk_2C;
    if (anim_table != D_801740E0 && anim_table != D_801740E8) {
        (*(u8 * *)((u8 *)actor + 0x2C)) = D_801740E0;
        func_80047784(
            actor,
            D_801740E0[((D_80083228 + ((S_80171A18_0 *)move_state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    next_cell = (u8 *)move_state + ((S_80171A18_0 *)move_state)->unk_8A.s;
    if (((S_80171A18_1 *)actor)->unk_24 == ((S_80171A18_2 *)next_cell)->unk_74 &&
        ((S_80171A18_1 *)actor)->unk_25 == ((S_80171A18_2 *)next_cell)->unk_7C) {
        move_offset = ((S_80171A18_3 *)motion)->unk_92;
        remaining_offset = ((S_80171A18_0 *)move_state)->unk_88;
        ((S_80171A18_3 *)motion)->unk_92 = move_offset + 0x20;
        ((S_80171A18_0 *)move_state)->unk_88 = remaining_offset - 0x20;
        ((S_80171A18_0 *)move_state)->unk_8A.u = ((S_80171A18_0 *)move_state)->unk_8A.u + 1;
        goto finish_move;
    }

    old_x = ((S_80171A18_1 *)actor)->unk_24;
    old_y = ((S_80171A18_1 *)actor)->unk_25;
    occupancy_mask = 0x3000;
    if (((S_80171A18_0 *)move_state)->unk_1C & 0x2000) {
        occupancy_mask = 0x300;
    }
    func_8009A3D0(old_x, old_y, occupancy_mask);

    ((S_80171A18_1 *)actor)->unk_24 = ((S_80171A18_4 *)((u8 *)move_state + ((S_80171A18_0 *)move_state)->unk_8A.s))->unk_74;
    ((S_80171A18_1 *)actor)->unk_25 = ((S_80171A18_4 *)((u8 *)move_state + ((S_80171A18_0 *)move_state)->unk_8A.s))->unk_7C;
    ((S_80171A18_0 *)move_state)->unk_8A.u++;

    new_x = ((S_80171A18_1 *)actor)->unk_24;
    new_y = ((S_80171A18_1 *)actor)->unk_25;
    occupancy_mask = 0x3000;
    if (((S_80171A18_0 *)move_state)->unk_1C & 0x2000) {
        occupancy_mask = 0x300;
    }
    func_8009A21C(new_x, new_y, occupancy_mask);

    ((S_80171A18_0 *)move_state)->unk_2A = func_800A0818(
        old_x, old_y, ((S_80171A18_1 *)actor)->unk_24, ((S_80171A18_1 *)actor)->unk_25,
        (u8 *)motion + 0x98);

finish_move:
    ((S_80171A18_3 *)motion)->unk_9A = 0xF;
    ((S_80171A18_3 *)motion)->unk_8C = 0;
    (*(u32 *)((u8 *)move_state + 0x1C)) |= 0x40000000;

    if (D_80083462 & 0x80) {
        ((S_80171A18_3 *)motion)->unk_96 = 0;
        return;
    }

    ((S_80171A18_3 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((S_80171A18_0 *)move_state)->unk_71.u;
        if (step_count > 0) {
            ((S_80171A18_3 *)motion)->unk_96 = 8 / step_count;
        }
    }
}
