#include "common.h"

#include "common.h"

extern void func_80048660(u8 *, s32);
extern void func_80048870(u8 *, s32, s32);

/* Apply selected operations to eligible records in a terminated list. */
void func_800488F0(u8 *records, s32 *shared_value, s32 operation_flags)
{
    u8 *record;
    s32 *value_ptr;
    s32 *prior_value;
    s32 apply_value;
    s32 apply_pair;

    record = records;
    value_ptr = shared_value;
    prior_value = (s32 *)record;
    apply_value = operation_flags & 2;
    apply_pair = operation_flags & 1;
    while (1) {
        if ((*record & 0x60) == 0) {
            prior_value = (s32 *)((s8 *)prior_value - 4);
            if (apply_value != 0) {
                func_80048660(record, *value_ptr);
            }
            if (apply_pair != 0) {
                func_80048870(record, *value_ptr, *prior_value);
            }
        }
        if ((*record & 0x80) != 0) {
            record += 0xC;
            break;
        }
        record += 0xC;
    }
}
