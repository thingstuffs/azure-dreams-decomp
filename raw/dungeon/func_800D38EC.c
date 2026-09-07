#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_8003DB94(void *, void *, s32);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800D910C(void *, void *, void *);
extern void func_800D9240(void);
extern void func_800D9298(void);
extern void func_800D9820(void *, s32, void *, void *);

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800E260C[];

void func_800D904C(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register void *state ASM_REG("$17") = arg3;
    void *current;
    s32 mode;
    s16 first_result;
    s16 second_result;
    s32 old_x;
    s32 old_y;
    s32 count;
    void *entry;

    if ((FIELD(state, s8, 0x71) > 0) &&
        ((s32)FIELD(state, u8, 0x71) > FIELD(state, s16, 0x8A))) {
        current = FIELD(arg2, void *, 0x2C);
        if (current != D_800E260C) {
            register void *dispatch ASM_REG("$2");

            FIELD(arg2, void *, 0x2C) = D_800E260C;
            dispatch = D_800E260C +
                (((D_80083228 + FIELD(state, s16, 0x2A) + 0x100) >> 7) & 0x1C);
            ASM_TAILSLOT_PIN(dispatch);
            func_800D910C(arg2, D_800E260C, current);
            return;
        }

        if (FIELD(arg2, u16, 0x14) & 0x6000) {
            func_8003DB94(
                arg2,
                *(void **)(D_800E260C +
                    (((D_80083228 + FIELD(state, s16, 0x2A) + 0x100) >> 7) & 0x1C)),
                0);
        }

        old_x = FIELD(arg2, u8, 0x24);
        old_y = FIELD(arg2, u8, 0x25);
        mode = 0x3000;
        if (FIELD(state, s32, 0x1C) & 0x2000) {
            mode = 0x300;
        }
        func_8009A3D0(old_x, old_y, mode);

        entry = (u8 *)state + FIELD(state, s16, 0x8A);
        first_result = func_800A0818(old_x, old_y,
                                    FIELD(entry, u8, 0x74),
                                    FIELD(entry, u8, 0x7C),
                                    (u8 *)arg0 + 0x98);
        second_result = func_8009A66C(first_result, arg2, state, 0x20);

        FIELD(arg2, u8, 0x24) =
            FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x74);
        mode = 0x3000;
        FIELD(arg2, u8, 0x25) =
            FIELD((u8 *)state + FIELD(state, s16, 0x8A), u8, 0x7C);
        FIELD(state, s16, 0x8A) = (u16)FIELD(state, s16, 0x8A) + 1;

        {
            s32 nx = FIELD(arg2, u8, 0x24);
            s32 ny = FIELD(arg2, u8, 0x25);
            if (FIELD(state, s32, 0x1C) & 0x2000) {
                mode = 0x300;
            }
            func_8009A21C(nx, ny, mode);
        }

        FIELD(state, s16, 0x2A) = first_result;
        if ((second_result == 3) &&
            ((D_80083462 & 0x80) || (FIELD(arg2, u16, 0x14) & 0x8000))) {
            FIELD(arg0, u8, 0x9A) = 0xF;
            func_800D9240();
            return;
        }

        func_800D9820(arg0, arg1, arg2, state);
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(state, s32, 0x1C) |= 0x40000000;
        if (D_80083462 & 0x80) {
            FIELD(arg0, s16, 0x96) = 0;
            func_800D9298();
            return;
        }

        FIELD(arg0, s16, 0x96) = 8;
        count = FIELD(state, u8, 0x71);
        if (count > 0) {
            FIELD(arg0, s16, 0x96) = 8 / count;
        }
    }
}
