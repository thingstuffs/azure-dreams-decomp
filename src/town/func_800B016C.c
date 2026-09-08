#include "common.h"

extern s32 func_800AD828(s32 arg0, s32 arg1);
extern s32 D_80082AB8;

/* Store whether the record check returns a nonzero result. */
void func_800AD8CC(void *record) {
    if (func_800AD828(*(s32 *)((u8 *)record + 0x20), *(s32 *)((u8 *)record + 0x18)) != 0) {
        D_80082AB8 = 1;
        return;
    }
    D_80082AB8 = 0;
}
