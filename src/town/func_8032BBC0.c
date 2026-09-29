#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s32 func_8001ADE0(s32);
extern void func_8001AD60(s32);

typedef struct {
    u8 pad[0x2F8];
    void (*callback)(s32, s32);
} CallbackData;

/* Consume condition 0x3EB and invoke the callback when it is active. */
s32 func_800163C0(void) {
    if (func_8001ADE0(0x3EB) != 0) {
        func_8001AD60(0x3EB);
        ((CallbackData *)D_80016000->unk_20)->callback(0xD, 0x200);
        return 1;
    }
    return 0;
}
