#include "common.h"

extern void func_800B2D00(s32, void *, s32);

/* Forwards a value and the record's fields to func_800B2D00. */
void func_800B4720(s32 value, u8 **record_ref) {
    u8 *record = *record_ref;
    func_800B2D00(value, record + 0x2C, *(s32 *)(record + 0x40));
}
