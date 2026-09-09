#include "common.h"

extern s32 func_800A4ACC();
extern s32 func_800AB1C0();
extern s32 func_800AD594();
extern s32 func_800AD9B4();

extern u16 D_80083462;
extern s32 D_801714D4[];

/* Selects the state table after a successful target check and applies the flagged offset. */
void func_8017276C(void *state, s32 unused, s32 source, s32 target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(source, target) << 16) > 0) {
            do {
                *(s32 **)((u8 *)state + 0x8C) = D_801714D4;
            } while (0);
            goto block_3;
        }
    } else {
block_3:
        if (D_80083462 & 0x80) {
            *(s16 *)((u8 *)state + 0x92) = -0x20;
        }
    }
}
