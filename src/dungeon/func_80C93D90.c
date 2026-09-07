#include "common.h"

typedef struct S_80171590_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171590_0;   /* state in func_80171590 */

typedef struct S_80171590_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171590_1;   /* arg2 in func_80171590 */

typedef struct S_80171590_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x9];
    s16 unk_A4;
} S_80171590_2;   /* arg0 in func_80171590 */

typedef struct S_80171590_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171590_3;   /* (u8 *)state + ((S_80171590_0 *)state)->unk_8A.s in func_80171590 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80171F58();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801752AC[];

void func_80171590(void *p0, s32 p1, void *p2, void *p3) {
    void *arg0 = p0;
    s32 arg1 = p1;
    void *arg2 = p2;
    void *state = p3;
    s32 mode;
    s32 x;
    s32 y;
    s32 nx;
    s32 ny;
    register s16 pos ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    register s16 result ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */

    if (((S_80171590_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (!((s32)((S_80171590_0 *)state)->unk_71.u > ((S_80171590_0 *)state)->unk_8A.s)) {
        return;
    }

    if (((S_80171590_1 *)arg2)->unk_2C != D_801752AC) {
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_801752AC;
        func_80047784(
            arg2,
            D_801752AC[((D_80083228 + ((S_80171590_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((S_80171590_1 *)arg2)->unk_24;
    y = ((S_80171590_1 *)arg2)->unk_25;
    mode = 0x3000;
    if (((S_80171590_0 *)state)->unk_1C & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(x, y, mode);

    pos = func_800A0818(
        x,
        y,
        ((S_80171590_3 *)((u8 *)state + ((S_80171590_0 *)state)->unk_8A.s))->unk_74,
        ((S_80171590_3 *)((u8 *)state + ((S_80171590_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)arg0 + 0x98);
    result = func_8009A66C(pos, arg2, state, 0x20);

    ((S_80171590_1 *)arg2)->unk_24 =
        ((S_80171590_3 *)((u8 *)state + ((S_80171590_0 *)state)->unk_8A.s))->unk_74;
    ((S_80171590_1 *)arg2)->unk_25 =
        ((S_80171590_3 *)((u8 *)state + ((S_80171590_0 *)state)->unk_8A.s))->unk_7C;
    ((S_80171590_0 *)state)->unk_8A.u++;

    nx = ((S_80171590_1 *)arg2)->unk_24;
    ny = ((S_80171590_1 *)arg2)->unk_25;
    mode = 0x3000;
    if (((S_80171590_0 *)state)->unk_1C & 0x2000) {
        mode = 0x300;
    }
    func_8009A21C(nx, ny, mode);
    ((S_80171590_0 *)state)->unk_2A = pos;

    if (result == 2) {
        if (D_80083462 & 0x80) {
            goto failure;
        }
        if (((S_80171590_1 *)arg2)->unk_14 & 0x8000) {
            ((S_80171590_2 *)arg0)->unk_9A = 15;
            goto failure_common;
        }
    } else {
        if (result != 3) {
            goto failure;
        }
        if (D_80083462 & 0x80) {
            goto failure;
        }
        if (((S_80171590_1 *)arg2)->unk_14 & 0x8000) {
            goto failure;
        }
    }

    func_80171F58(arg0, arg1, arg2, state);
    ((S_80171590_2 *)arg0)->unk_A4 = result;
    goto failure_common;

failure:
    ((S_80171590_2 *)arg0)->unk_9A = 15;
failure_common:
    ((S_80171590_2 *)arg0)->unk_8C = 0;
    (*(u32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_80171590_2 *)arg0)->unk_96 = 0;
        return;
    }
    ((S_80171590_2 *)arg0)->unk_96 = 8;
    {
        s32 count = ((S_80171590_0 *)state)->unk_71.u;
        if (count > 0) {
            ((S_80171590_2 *)arg0)->unk_96 = 8 / count;
        }
    }
    return;
}
