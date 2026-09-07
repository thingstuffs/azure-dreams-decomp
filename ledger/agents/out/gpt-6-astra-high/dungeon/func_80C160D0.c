#include "common.h"

typedef struct S_801718D0_0 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_801718D0_0;   /* arg3 in func_801718D0 */

typedef struct S_801718D0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801718D0_1;   /* arg2 in func_801718D0 */

typedef struct S_801718D0_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0xD];
    s16 unk_A8;
} S_801718D0_2;   /* arg0 in func_801718D0 */

typedef struct S_801718D0_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801718D0_3;   /* (u8 *)arg3 + ((S_801718D0_0 *)arg3)->unk_8A.s in func_801718D0 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174494[];
extern u8 D_8017449C[];

/* Advances the entity along its path and updates occupancy, facing, and movement timing. */
void func_801718D0(void *motion, s32 unused, void *entity, void *path_state)
{
    u8 *direction_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 occupancy_mask;

    if (((S_801718D0_0 *)path_state)->unk_71.s <= 0) {
        return;
    }
    if (((S_801718D0_0 *)path_state)->unk_71.u <= ((S_801718D0_0 *)path_state)->unk_8A.s) {
        return;
    }

    direction_table = ((S_801718D0_1 *)entity)->unk_2C;
    if (direction_table != D_80174494 && direction_table != D_8017449C) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_8017449C;
        func_80047784(
            entity,
            D_8017449C[((D_80083228 + ((S_801718D0_0 *)path_state)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_801718D0_2 *)motion)->unk_A8 = 0;
    }

    old_x = ((S_801718D0_1 *)entity)->unk_24;
    old_y = ((S_801718D0_1 *)entity)->unk_25;
    occupancy_mask = 0x3000;
    if (((S_801718D0_0 *)path_state)->unk_1C.s & 0x2000) {
        occupancy_mask = 0x300;
    }
    func_8009A3D0(old_x, old_y, occupancy_mask);

    ((S_801718D0_1 *)entity)->unk_24 =
        ((S_801718D0_3 *)((u8 *)path_state + ((S_801718D0_0 *)path_state)->unk_8A.s))->unk_74;
    ((S_801718D0_1 *)entity)->unk_25 =
        ((S_801718D0_3 *)((u8 *)path_state + ((S_801718D0_0 *)path_state)->unk_8A.s))->unk_7C;
    ((S_801718D0_0 *)path_state)->unk_8A.u++;

    new_x = ((S_801718D0_1 *)entity)->unk_24;
    new_y = ((S_801718D0_1 *)entity)->unk_25;
    occupancy_mask = 0x3000;
    if (((S_801718D0_0 *)path_state)->unk_1C.s & 0x2000) {
        occupancy_mask = 0x300;
    }
    func_8009A21C(new_x, new_y, occupancy_mask);

    ((S_801718D0_0 *)path_state)->unk_2A = func_800A0818(
        old_x, old_y, ((S_801718D0_1 *)entity)->unk_24, ((S_801718D0_1 *)entity)->unk_25,
        (u8 *)motion + 0x98);
    ((S_801718D0_0 *)path_state)->unk_1C.u |= 0x40000000;
    ((S_801718D0_2 *)motion)->unk_9A = 0xF;
    (*(s32 *)((u8 *)motion + 0x8C)) = 0;

    if (D_80083462 & 0x80) {
        ((S_801718D0_2 *)motion)->unk_96 = 0;
        return;
    }

    ((S_801718D0_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((S_801718D0_0 *)path_state)->unk_71.u;
        if (step_count > 0) {
            ((S_801718D0_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
}
