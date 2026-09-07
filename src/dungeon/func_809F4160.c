#include "common.h"

typedef struct S_80171960_0 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171960_0;   /* arg3 in func_80171960 */

typedef struct S_80171960_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171960_1;   /* arg2 in func_80171960 */

typedef struct S_80171960_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 pad_9B[0xD];
    s16 unk_A8;
} S_80171960_2;   /* arg0 in func_80171960 */

typedef struct S_80171960_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171960_3;   /* (u8 *)arg3 + ((S_80171960_0 *)arg3)->unk_8A.s in func_80171960 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80175140[];
extern u8 D_80175148[];

void func_80171960(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    u8 *table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 mode;

    if (((S_80171960_0 *)arg3)->unk_71.s <= 0) {
        return;
    }
    if (((S_80171960_0 *)arg3)->unk_71.u <= ((S_80171960_0 *)arg3)->unk_8A.s) {
        return;
    }

    table = ((S_80171960_1 *)arg2)->unk_2C;
    if (table != D_80175140 && table != D_80175148) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_80175140;
        func_80047784(
            arg2,
            D_80175140[((D_80083228 + ((S_80171960_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((S_80171960_2 *)arg0)->unk_A8 = 0;
    }

    old_x = ((S_80171960_1 *)arg2)->unk_24;
    old_y = ((S_80171960_1 *)arg2)->unk_25;
    mode = 0x3000;
    if (((S_80171960_0 *)arg3)->unk_1C.s & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(old_x, old_y, mode);

    ((S_80171960_1 *)arg2)->unk_24 =
        ((S_80171960_3 *)((u8 *)arg3 + ((S_80171960_0 *)arg3)->unk_8A.s))->unk_74;
    ((S_80171960_1 *)arg2)->unk_25 =
        ((S_80171960_3 *)((u8 *)arg3 + ((S_80171960_0 *)arg3)->unk_8A.s))->unk_7C;
    ((S_80171960_0 *)arg3)->unk_8A.u++;

    new_x = ((S_80171960_1 *)arg2)->unk_24;
    new_y = ((S_80171960_1 *)arg2)->unk_25;
    mode = 0x3000;
    if (((S_80171960_0 *)arg3)->unk_1C.s & 0x2000) {
        mode = 0x300;
    }
    func_8009A21C(new_x, new_y, mode);

    ((S_80171960_0 *)arg3)->unk_2A = func_800A0818(
        old_x, old_y, ((S_80171960_1 *)arg2)->unk_24, ((S_80171960_1 *)arg2)->unk_25,
        (u8 *)arg0 + 0x98);
    ((S_80171960_0 *)arg3)->unk_1C.u |= 0x40000000;
    ((S_80171960_2 *)arg0)->unk_9A = 0xF;
    (*(s32 *)((u8 *)arg0 + 0x8C)) = 0;

    if (D_80083462 & 0x80) {
        ((S_80171960_2 *)arg0)->unk_96 = 0;
        return;
    }

    ((S_80171960_2 *)arg0)->unk_96 = 8;
    {
        s32 hp = ((S_80171960_0 *)arg3)->unk_71.u;
        if (hp > 0) {
            ((S_80171960_2 *)arg0)->unk_96 = 8 / hp;
        }
    }
}

/* MECHANISM:
 * Mirror the byte-exact movement-family source shape: keep the dead a1 ABI
 * slot, hold old coordinates in s3/s4, and use a signed-word tail count.
 * The 0x80171B04 jump is the local early-return epilogue.
 */
