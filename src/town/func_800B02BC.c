#include "common.h"

extern void func_8004DD2C(s32 arg0);
extern void func_80053DA8(s32 arg0);
extern void func_800AD7F8(void *arg0);
extern void func_800AD8CC(void *arg0);
extern s32 func_800AD99C(void *arg0);
extern void func_800ADAF0(void) __attribute__((noreturn));
extern void func_800AE30C(void *arg0);
extern void func_800B17E4(s32 arg0);

extern s32 D_800D1558;
extern s32 D_800D155C;

void func_800ADA1C(s32 *arg0) {
    u8 *entry;

    entry = (u8 *) (arg0[1] * 4 + arg0[8]);
    if (entry[1] != 0x16) {
        if (!(entry[3] & 0x80)) {
            if (func_800AD99C(arg0) != 0) {
                func_80053DA8(0x503);
                func_800AD7F8(arg0);
                func_800B17E4(arg0[10]);
                func_800ADAF0();
                return;
            }
            func_80053DA8(0x506);
            func_8004DD2C(D_800D1558);
            func_800ADAF0();
            return;
        }
        func_80053DA8(0x506);
        if (arg0[6] == 1) {
            func_8004DD2C(D_800D155C);
            func_800ADAF0();
        }
    } else {
        func_800AE30C((s8 *) arg0 - 0x20);
        func_800AD8CC(arg0);
    }
}
