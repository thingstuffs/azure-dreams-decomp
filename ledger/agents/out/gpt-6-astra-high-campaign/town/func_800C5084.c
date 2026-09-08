#include "common.h"

extern void func_8008FD48(void *arg0, s32 arg1, void *arg2);
extern void *D_800D4F88[];
extern s32 D_800C283C[];

/* Initialize the object with its indexed resource and set its flag and data pointer. */
void func_800C27E4(void *object, s32 setup_value, s32 unused) {
    u8 *obj = (u8 *)object;

    func_8008FD48(object, setup_value, D_800D4F88[obj[0x94]]);
    obj[0x14] = 1;
    *(void **)(obj + 0x50) = D_800C283C;
}
