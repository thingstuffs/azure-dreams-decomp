#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern void func_80171574() __attribute__((noreturn));
extern void func_80171578() __attribute__((noreturn));
extern void func_801715CC() __attribute__((noreturn));
extern s32 func_80171D3C();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80173C74[];

void func_8017139C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *state ASM_REG("$17") = arg3;
    s32 move_flags;
    s16 action;
    s16 result;
    s32 x;
    s32 y;
    register u16 flags ASM_REG("$2");

    if (FIELD(state, s8, 0x71) <= 0) {
        return;
    }

    if (FIELD(state, u8, 0x71) <= FIELD(state, s16, 0x8A)) {
        return;
    }

    if (FIELD(arg2, u8 *, 0x2C) != D_80173C74) {
        FIELD(arg2, u8 *, 0x2C) = D_80173C74;
        func_80047784(
            arg2,
            D_80173C74[((D_80083228 + FIELD(state, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    x = FIELD(arg2, u8, 0x24);
    y = FIELD(arg2, u8, 0x25);
    move_flags = 0x3000;
    if (FIELD(state, s32, 0x1C) & 0x2000) {
        move_flags = 0x300;
    }
    func_8009A3D0(x, y, move_flags);

    action = func_800A0818(
        x,
        y,
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74),
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C),
        (u8 *)arg0 + 0x98);
    result = func_8009A66C(action, arg2, state, 0x20);

    FIELD(arg2, u8, 0x24) =
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74);
    move_flags = 0x3000;
    FIELD(arg2, u8, 0x25) =
        FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C);
    FIELD(state, u16, 0x8A)++;

    {
        s32 next_x = FIELD(arg2, u8, 0x24);
        s32 next_y = FIELD(arg2, u8, 0x25);

        if (FIELD(state, s32, 0x1C) & 0x2000) {
            move_flags = 0x300;
        }
        func_8009A21C(next_x, next_y, move_flags);
    }

    FIELD(state, s16, 0x2A) = action;
    if (result == 3) {
        if (!(D_80083462 & 0x80) && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
            func_80171D3C(arg0, arg1, arg2, state);
            FIELD(arg0, s32, 0x8C) = 0;
            func_80171578();
            return;
        }
        FIELD(arg0, u8, 0x9A) = 0xF;
        func_80171574();
        return;
    }

    flags = FIELD(arg0, u16, 0x98);
    FIELD(arg0, u8, 0x9A) = 0xF;
    flags &= ~8;
    FIELD(arg0, u16, 0x98) = flags;
    ASM_KEEP(flags);
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(state, s32, 0x1C) |= 0x40000000;
    if (D_80083462 & 0x80) {
        FIELD(arg0, s16, 0x96) = 0;
        func_801715CC();
        return;
    }

    FIELD(arg0, s16, 0x96) = 8;
    {
        s32 count = FIELD(state, u8, 0x71);
        if (count > 0) {
            FIELD(arg0, s16, 0x96) = 8 / count;
        }
    }
    ASM_KEEP(state);
}
