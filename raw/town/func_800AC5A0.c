#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(expr, type, offset) (*(type *)((s8 *)(expr) + (offset)))

extern s32 func_8009368C();
extern s32 func_80093744();
extern s32 func_800C172C();
extern s8 D_800834B8[0x30];

void func_800A9D00(void) {
    s8 *base;
    void *temp_v0;

    base = D_800834B8;
    temp_v0 = base - 0x20;
    if ((func_8009368C(base, FIELD(temp_v0, s32, 8),
                      FIELD(temp_v0, s32, 0xC)) != 0) &&
        (FIELD(base, void *, 0x2C) != NULL) &&
        (FIELD(FIELD(base, void *, 0x2C), u16, 0x4C) == 0xD04)) {
        func_800C172C();
    }
    func_80093744();
}

/* MECHANISM: Hold &D_800834B8 across the first call so it occupies s0,
   while deriving the two pre-base call arguments through a short-lived pointer. */
