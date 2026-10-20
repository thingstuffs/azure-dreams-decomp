#include "common.h"

s32 func_8007C9C8(s32);

/* Clears the state flag and processes the four stored handles. */
void card_dev_drain_sw_events(void) {
    *(s32 *)0x80409504 = 0;
    func_8007C9C8(*(s32 *)0x80409280);
    func_8007C9C8(*(s32 *)0x80409284);
    func_8007C9C8(*(s32 *)0x80409288);
    func_8007C9C8(*(s32 *)0x8040928C);
}
