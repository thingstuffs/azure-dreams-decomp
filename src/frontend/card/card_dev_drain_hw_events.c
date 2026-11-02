#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

/* Pass each of the four stored values to the shared callback. */
void card_dev_drain_hw_events(void) {
    func_8007C9C8(*(s32 *)0x80409270);
    func_8007C9C8(*(s32 *)0x80409274);
    func_8007C9C8(*(s32 *)0x80409278);
    func_8007C9C8(*(s32 *)0x8040927C);
}
