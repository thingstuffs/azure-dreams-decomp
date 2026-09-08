#include "common.h"

extern s32 func_8001ACE8();
extern s32 func_8001AD60();

/* Update flags using the record and indexed entry, then return success. */
s32 func_80019988(void *record, s32 entry_index) {
    func_8001AD60(*(s16 *)((s8 *)record + 0x18));
    func_8001ACE8(*(s16 *)((entry_index * 0x10) + *(s32 *)((s8 *)record + 0x10) + 0xC));
    return 1;
}
