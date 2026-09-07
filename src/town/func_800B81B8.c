#include "common.h"

extern void func_8004E5A0(s32 value, s32 width, u8 *dst);
extern u8 *func_8004E69C(u8 *text);
extern u8 D_80089304[];

typedef struct {
    u8 pad0[2];
    s8 value;
} Input;

u8 *func_800B5918(Input *arg0, u8 *arg1) {
    s8 value;

    memcpy(arg1, D_80089304, 4);
    value = arg0->value;
    if (value != 0) {
        arg1[0] = value > 0 ? 0x6B : 0x6C;
        func_8004E5A0(arg0->value >= 0 ? arg0->value : -arg0->value,
                      2, arg1 + 1);
        func_8004E69C(arg1);
    }
    return arg1;
}
