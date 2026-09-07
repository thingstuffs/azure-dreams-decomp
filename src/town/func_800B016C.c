#include "common.h"

extern s32 func_800AD828(s32 arg0, s32 arg1);
extern void func_800AD904(void);
extern s32 D_80082AB8;

void func_800AD8CC(void *arg0) {
    if (func_800AD828(*(s32 *)((u8 *)arg0 + 0x20), *(s32 *)((u8 *)arg0 + 0x18)) != 0) {
        D_80082AB8 = 1;
        func_800AD904();
        return;
    }
    D_80082AB8 = 0;
}
