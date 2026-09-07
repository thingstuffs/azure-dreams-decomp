#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(u32);

extern u8 D_80016000[];
extern u8 D_80017420[];
extern void *D_800174D4[];

void func_806A9100(void) {
    Callback callback;

    callback = FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x20), Callback, 0x28C);
    D_800174D4[0] = D_80017420;
    callback(1);
    FIELD(FIELD(FIELD(D_80016000, void *, 0), void *, 0x20), Callback, 0x290)(1);
}
