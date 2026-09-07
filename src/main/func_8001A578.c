#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8007C9C8();                         /* extern */

void func_8001A578(void) {
    *(s32 *)0x80409504 = 0;
    func_8007C9C8(*(s32 *)0x80409280);
    func_8007C9C8(*(s32 *)0x80409284);
    func_8007C9C8(*(s32 *)0x80409288);
    func_8007C9C8(*(s32 *)0x8040928C);
}
