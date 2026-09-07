#include "common.h"

extern void func_8008FD48(void *arg0, s32 arg1, void *arg2);
extern void *D_800D4F88[];
extern s32 D_800C283C[];

void func_800C27E4(void *arg0, s32 arg1, s32 arg2) {
    u8 *obj = (u8 *)arg0;

    func_8008FD48(arg0, arg1, D_800D4F88[obj[0x94]]);
    obj[0x14] = 1;
    *(void **)(obj + 0x50) = D_800C283C;
}
