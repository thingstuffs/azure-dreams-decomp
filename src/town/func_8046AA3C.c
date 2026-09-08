#include "common.h"

extern void func_80019730(s32, s32);
extern u8 D_8001601C[];
extern u8 D_80017774[];
extern u8 D_80022E7E[];

/* Select data by mode, calling func_80019730 for mode one. */
void *func_8001BA3C(s32 setup_value, s32 setup_option, s32 mode) {
    if (mode == 1) {
        func_80019730(setup_value, setup_option);
        return D_80022E7E;
    } else if (mode == 4) {
        return D_8001601C;
    } else {
        return D_80017774;
    }
}
