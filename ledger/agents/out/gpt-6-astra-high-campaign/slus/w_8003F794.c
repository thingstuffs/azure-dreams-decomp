#include "common.h"

typedef struct S_80083120 {
    s16 field_0;
    s16 field_2;
    s16 field_4;
    s16 field_6;
} S_80083120;

extern S_80083120 D_80083120[8];

/* Initializes the last free slot and returns its index, or -1 if all eight slots are occupied. */
s16 func_8003F794(s16 slot_id, s16 slot_value)
{
    s32 slot_index;
    u32 last_slot_index;
    S_80083120 *slot;

    slot_index = 7;
    last_slot_index = 7;
    slot = &D_80083120[last_slot_index];
loop:
    if (slot->field_0 == 0)
        goto found;
    slot_index--;
    slot--;
    if (slot_index >= 0)
        goto loop;
    return -1;
found:
    slot->field_0 = slot_id;
    slot->field_2 = 0;
    slot->field_4 = slot_value;
    slot->field_6 = 0;
    return slot_index;
}
