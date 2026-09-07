#include "common.h"

extern s32 func_8008C134(s16 arg0, s16 arg1);
extern s32 func_800C1D20(s32 arg0);
extern void func_8008C1C4(s32 arg0, s32 arg1, s32 arg2, void *arg3);

/* Converts and processes all 128 entries for the given lookup key. */
void func_8008C214(s16 lookup_key, void *context) {
    s32 entry_index;

    for (entry_index = 0; entry_index < 0x80; entry_index++) {
        func_8008C1C4(func_800C1D20(func_8008C134(entry_index, lookup_key) & 0xFFFF), entry_index, 0x80, context);
    }
}
