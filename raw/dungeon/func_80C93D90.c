#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    register s16 pos ASM_REG("$18");
    register s16 result ASM_REG("$17");

    if (FIELD(state, s8, 0x71) <= 0) {
        return;
    }
    if (!((s32)FIELD(state, u8, 0x71) > FIELD(state, s16, 0x8A))) {
        return;
    }

    if (FIELD(arg2, u8 *, 0x2C) != D_801752AC) {
        FIELD(arg2, u8 *, 0x2C) = D_801752AC;
        func_80047784(
            arg2,
            D_801752AC[((D_80083228 + FIELD(state, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    x = FIELD(arg2, u8, 0x24);
    y = FIELD(arg2, u8, 0x25);
    mode = 0x3000;
    if (FIELD(state, u32, 0x1C) & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(x, y, mode);

    pos = func_800A0818(
        x,
        y,
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74),
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C),
        (u8 *)arg0 + 0x98);
    result = func_8009A66C(pos, arg2, state, 0x20);

    FIELD(arg2, u8, 0x24) =
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74);
    FIELD(arg2, u8, 0x25) =
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C);
    FIELD(state, u16, 0x8A)++;

    nx = FIELD(arg2, u8, 0x24);
    ny = FIELD(arg2, u8, 0x25);
    mode = 0x3000;
    if (FIELD(state, u32, 0x1C) & 0x2000) {
        mode = 0x300;
    }
    func_8009A21C(nx, ny, mode);
    FIELD(state, s16, 0x2A) = pos;

    if (result == 2) {
        if (D_80083462 & 0x80) {
            goto failure;
        }
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            FIELD(arg0, s8, 0x9A) = 15;
            goto failure_common;
        }
    } else {
        if (result != 3) {
            goto failure;
        }
        if (D_80083462 & 0x80) {
            goto failure;
        }
        if (FIELD(arg2, u16, 0x14) & 0x8000) {
            goto failure;
        }
    }

    func_80171F58(arg0, arg1, arg2, state);
    FIELD(arg0, s16, 0xA4) = result;
    goto failure_common;

failure:
    FIELD(arg0, s8, 0x9A) = 15;
failure_common:
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(state, u32, 0x1C) |= 0x40000000;
    if (D_80083462 & 0x80) {
        FIELD(arg0, s16, 0x96) = 0;
        return;
    }
    FIELD(arg0, s16, 0x96) = 8;
    {
        s32 count = FIELD(state, u8, 0x71);
        if (count > 0) {
            FIELD(arg0, s16, 0x96) = 8 / count;
        }
    }
    return;
}
