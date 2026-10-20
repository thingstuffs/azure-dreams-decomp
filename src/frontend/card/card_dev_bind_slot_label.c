#include "common.h"

s32 func_80051B50(s32, void *, s32);
extern s32 D_80408D6C;

/* Passes the object's data at offset 0x7C to func_80051B50 with D_80408D6C. */
void card_dev_bind_slot_label(s32 object_addr) {
    func_80051B50(object_addr + 0x7C, &D_80408D6C, 1);
}
