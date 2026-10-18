#include "common.h"
void func_8007C9C8(s32 handle);                         /* extern */

/* Pass each of the four stored values to the shared callback. */
void func_8001A4E4(void) {
    func_8007C9C8(*(s32 *)0x80409270);
    func_8007C9C8(*(s32 *)0x80409274);
    func_8007C9C8(*(s32 *)0x80409278);
    func_8007C9C8(*(s32 *)0x8040927C);
}
