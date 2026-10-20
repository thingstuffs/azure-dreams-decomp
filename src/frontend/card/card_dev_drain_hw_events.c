#include "common.h"
void func_8007C9C8(s32 handle);                         /* extern */

/* Pass each of the four stored values to the shared callback. */
void card_dev_drain_hw_events(void) {
    func_8007C9C8(*(s32 *)0x80409270);
    func_8007C9C8(*(s32 *)0x80409274);
    func_8007C9C8(*(s32 *)0x80409278);
    func_8007C9C8(*(s32 *)0x8040927C);
}
