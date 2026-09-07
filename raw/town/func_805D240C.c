#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((s8 *)(ptr) + (offset)))

extern s8 D_80016000[];
extern s32 D_80019AFC;

s32 func_80018618(void);

s32 func_8001640C(void) {
    void **page;
    s32 result;

    page = (void **)D_80016000;
    D_80019AFC = FIELD(
        (FIELD(FIELD(page, void *, 0), s32, 8) * 8) +
            FIELD(FIELD(page, void *, 0), s32, 0x40),
        u8, 4);
    result = func_80018618();
    if (result != 0) {
        FIELD(
            (FIELD(FIELD(page, void *, 0), s32, 8) * 8) +
                FIELD(FIELD(page, void *, 0), s32, 0x40),
            s8, 4) = 0;
    }
    return result;
}

/* MECHANISM: A pointer to the D_80016000 pointer slot stays live in s0 across
   the call, giving the bare page lui and 0x6000 loads with no asm barrier;
   direct nested field expressions retain region-specific coloring. */
