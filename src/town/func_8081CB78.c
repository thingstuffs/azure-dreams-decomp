#include "common.h"

typedef struct {
    u8 pad0[0x1A];
    u16 flags;
} S_8081CB78_sub;

typedef struct {
    s16 state;
    u8 pad2[0xA];
    S_8081CB78_sub *sub;
} S_8081CB78;

extern int D_800814A0[];

void func_80026B78(S_8081CB78 *arg0) {
    s16 state = arg0->state;
    S_8081CB78_sub *sub = arg0->sub;

    if (state == 0 && (sub->flags & 8)) {
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
