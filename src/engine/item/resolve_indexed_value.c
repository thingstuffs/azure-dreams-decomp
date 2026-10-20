#include "common.h"
#include "shared/record_ptrs.h"

#include "common.h"
extern s32 D_800E3DF0[];
extern int func_80049280(int index);
extern int func_80021300(int a0);
extern int consume_pending_event_flag(int a0);
/* Resolves an indexed value and converts it unless its code is 2. */
int resolve_indexed_value(int index)
{
    s32 value;
    s32 value_code;
    if (func_80049280(index)) {
        value = *((s32 *) (((u8 *) ((s32)D_800814A8)) + 0x124));
    }
    else {
        value = D_800E3DF0[index];
    }
    value_code = func_80021300(value);
    if (value_code != 2) {
        value = consume_pending_event_flag(value_code);
    }
    return value;
}
