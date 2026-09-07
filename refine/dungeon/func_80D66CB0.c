#include "common.h"

typedef struct S_801724B0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_801724B0_0;   /* arg3 in func_801724B0 */

typedef struct S_801724B0_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_801724B0_1;   /* arg2 in func_801724B0 */

typedef struct S_801724B0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x3];
    s16 unk_9E;
} S_801724B0_2;   /* arg0 in func_801724B0 */

typedef struct S_801724B0_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801724B0_3;   /* (u8 *)arg3 + ((S_801724B0_0 *)arg3)->unk_8A.s in func_801724B0 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80172E0C();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800E2348[8];

/* Advance the actor along its queued path and update movement timing. */
void func_801724B0(void *motion, s32 actor_index, void *actor, void *move_data) {
    s32 tile_mask;
    s16 heading;
    s32 move_state;
    s32 x;
    s32 y;

    if ((((S_801724B0_0 *)move_data)->unk_71.s > 0) &&
        (((S_801724B0_0 *)move_data)->unk_71.u > ((S_801724B0_0 *)move_data)->unk_8A.s)) {
        if (((S_801724B0_1 *)actor)->unk_2C != D_800E2348) {
            (*(u8 * *)((u8 *)actor + 0x2C)) = D_800E2348;
            func_80047784(
                actor,
                D_800E2348[((D_80083228 + ((S_801724B0_0 *)move_data)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_801724B0_2 *)motion)->unk_9E = 0;
        }

        x = ((S_801724B0_1 *)actor)->unk_24;
        y = ((S_801724B0_1 *)actor)->unk_25;
        tile_mask = (((S_801724B0_0 *)move_data)->unk_1C & 0x2000) ? 0x300 : 0x3000;
        func_8009A3D0(x, y, tile_mask);

        heading = func_800A0818(
            x,
            y,
            ((S_801724B0_3 *)((u8 *)move_data + ((S_801724B0_0 *)move_data)->unk_8A.s))->unk_74,
            ((S_801724B0_3 *)((u8 *)move_data + ((S_801724B0_0 *)move_data)->unk_8A.s))->unk_7C,
            (u8 *)motion + 0x98);
        move_state = (s16)func_8009A66C(heading, actor, move_data, 0x20);

        ((S_801724B0_1 *)actor)->unk_24 =
            ((S_801724B0_3 *)((u8 *)move_data + ((S_801724B0_0 *)move_data)->unk_8A.s))->unk_74;
        tile_mask = 0x3000;
        ((S_801724B0_1 *)actor)->unk_25 =
            ((S_801724B0_3 *)((u8 *)move_data + ((S_801724B0_0 *)move_data)->unk_8A.s))->unk_7C;
        ((S_801724B0_0 *)move_data)->unk_8A.u++;

        {
            s32 next_x = ((S_801724B0_1 *)actor)->unk_24;
            s32 next_y = ((S_801724B0_1 *)actor)->unk_25;

            if (((S_801724B0_0 *)move_data)->unk_1C & 0x2000) {
                tile_mask = 0x300;
            }
            func_8009A21C(next_x, next_y, tile_mask);
        }

        ASM_KEEP(move_state);   /* MATCH pin: keeps a statement from moving across a call/branch */
        ((S_801724B0_0 *)move_data)->unk_2A = heading;
        if (move_state == 3) {
            if (!(D_80083462 & 0x80) && !(((S_801724B0_1 *)actor)->unk_14 & 0x8000)) {
                func_80172E0C(motion, actor_index, actor, move_data);
                ((S_801724B0_2 *)motion)->unk_8C = 0;
                goto post_state;
            }
        }

        ((S_801724B0_2 *)motion)->unk_9A = 0xF;
        ((S_801724B0_2 *)motion)->unk_8C = 0;

post_state:
        (*(s32 *)((u8 *)move_data + 0x1C)) |= 0x40000000;
        if (D_80083462 & 0x80) {
            ((S_801724B0_2 *)motion)->unk_96 = 0;
            goto end;
        }

        ((S_801724B0_2 *)motion)->unk_96 = 8;
        x = ((S_801724B0_0 *)move_data)->unk_71.u;
        if (x > 0) {
            ((S_801724B0_2 *)motion)->unk_96 = 8 / x;
        }
    }

end:
    return;
}

/* MECHANISM: The four live arguments and two call results naturally produce the retail 0x38 frame and saved-register order.
   A guarded s0 pin holds the signed func_8009A66C result; placing ASM_KEEP before the result store lets that sh fill the bne delay slot.
   Explicit mode initialization plus scoped next-coordinate locals reproduce the post-call load/store and branch emission order. */
