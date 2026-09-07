#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern s8 D_80016000[];

void func_8001A854(void *arg0, s32 arg1) {
    FIELD(FIELD(FIELD(D_80016000, void **, 0), void **, 0x20), void (**)(s32), 0x258)(arg1);
    FIELD(arg0, u16 *, 0) = FIELD(FIELD(FIELD(D_80016000, void **, 0), void **, 0x1C), u16 *, 4);
    FIELD(arg0, u16 *, 2) = FIELD(FIELD(FIELD(D_80016000, void **, 0), void **, 0x1C), u16 *, 8);
}
