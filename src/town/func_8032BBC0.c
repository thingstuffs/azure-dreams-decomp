#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 func_8001ADE0(s32);
extern void func_8001AD60(s32);

/* Consume condition 0x3EB and invoke the callback when it is active. */
s32 func_800163C0(void) {
    if (func_8001ADE0(0x3EB) != 0) {
        func_8001AD60(0x3EB);
        D_80016000->unk_20->callback_2F8(0xD, 0x200);
        return 1;
    }
    return 0;
}
