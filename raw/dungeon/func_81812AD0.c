#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} RECT;

extern s32 func_800499E8();
extern RECT D_80025034[2];
extern s8 D_80080B54[];

void func_80027AD0(void *arg0, s32 arg1, s32 arg2) {
    RECT rect;

    rect = D_80025034[0];
    rect.h = ((s32) (arg1 * 0x90) / arg2) + 4;
    func_800499E8(*(s32 *)((s8 *)arg0 + 0x4C) + 0x18, &rect, D_80080B54);
}
