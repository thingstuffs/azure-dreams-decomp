#include "common.h"

typedef struct {
    u8 pad28[0x28];
    u8 value;
    u8 limit;
    u8 pad2a[0x3A];
    s16 delta;
} FuncState;

extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_800AD534(void);

#ifndef NON_MATCHING
register volatile s32 value_v1 ASM_REG("$3");
#endif

void func_800AD4D0(void *arg0) {
    FuncState *state = (FuncState *)arg0;
#ifdef NON_MATCHING
    s32 value_v1;
#endif

    if ((state->delta < 0) && ((func_80042900(arg0, 0x1D) << 16) != 0)) {
        state->delta = 0;
    }

    value_v1 = state->value;
    value_v1 += state->delta;
    if (value_v1 < 0) {
        func_800AD534();
        value_v1 = 0;
        return;
    }
    if (value_v1 >= 0x100) {
        value_v1 = 0xFF;
    }
    state->value = (u8)value_v1;
    value_v1 = state->limit;
    state->delta = 0;
    if ((u32)value_v1 < state->value) {
        state->value = (u8)value_v1;
    }
}
