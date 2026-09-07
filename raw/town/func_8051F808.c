#include "common.h"

typedef s32 (*Callback)(s32);

extern s8 D_80016000[];

s32 func_80017008(void) {
    s8 *base;
    void *object;

    base = D_80016000;
    (*(Callback *)((s8 *)*(void **)((s8 *)*(void **)base + 0x20) + 0x248))(1);
    (*(Callback *)((s8 *)*(void **)((s8 *)*(void **)base + 0x20) + 0x244))(1);

    object = *(void **)((s8 *)*(void **)base + 0x1C);
    if (*(s32 *)object != 0) {
        return 0;
    }
    *(s32 *)((s8 *)object + 8) += 0x20;
    return 1;
}
