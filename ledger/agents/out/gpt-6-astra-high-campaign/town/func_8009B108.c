#include "common.h"

extern void func_80098834(s32 arg0, s32 arg1, s32 arg2);
extern void func_80098928(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_80093D48;
extern s32 *D_800FE5D8;

/* Run both initialization routines and select D_80093D48 as the active data. */
void func_80098868(s32 record, s32 setup_value, s32 init_value) {
    func_80098834(record, setup_value, init_value);
    func_80098928(record, setup_value, init_value);
    D_800FE5D8 = &D_80093D48;
}
