#include "common.h"

extern s32 func_800352FC(void *, s32, s32, s32);
extern s32 func_800C2A60(void *arg0);
extern void func_8008F134(void *arg0);
extern s32 D_800814A0;

/* Process the object and set its header and global flags when both checks pass. */
void func_800C26C0(void *object, s32 check_value_1, s32 check_value_2, s32 check_value_3) {
    if ((func_800352FC(object, check_value_1, check_value_2, check_value_3) != 0) && (func_800C2A60(object) != 0)) {
        func_8008F134(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
