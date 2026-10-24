#include "common.h"
#include "shared/record_ptrs.h"

#include "common.h"
#include "engine/item.h"
#include "slus.h"
extern s32 familiar_record_slots[];
extern int func_80021300(int a0);
extern int consume_pending_event_flag(int a0);
/* Resolves an indexed value and converts it unless its code is 2. */
int resolve_indexed_value(int index)
{
    s32 value;
    s32 value_code;
    if (is_type_twenty(index)) {
        value = *((s32 *) (((u8 *)primary_actor_record) + 0x124));
    }
    else {
        value = familiar_record_slots[index];
    }
    value_code = func_80021300(value);
    if (value_code != 2) {
        value = consume_pending_event_flag(value_code);
    }
    return value;
}
