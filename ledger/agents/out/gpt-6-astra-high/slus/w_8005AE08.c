#include "common.h"

/* Sound driver "sequence slot" table; 8 entries, 12 bytes each. */
typedef struct S_80086C00 {
    s16 field_0;   /* 0x0: -1 == free slot */
    s16 field_2;   /* 0x2: type/status */
    s32 field_4;   /* 0x4: data pointer / word value */
    u16 field_8;   /* 0x8 */
    u16 field_A;   /* 0xA */
} S_80086C00;

extern S_80086C00 D_80086C00[8];

/* Registers a recognized sequence header in the first free slot, returning its index or -1 on failure. */
s16 func_8005AE08(void *header, s32 sequence_id)
{
    u32 magic = *(u32 *)header;
    S_80086C00 *slot;
    s32 slot_index;
    s32 free_id;

    if (magic == 0x53455170 || magic == 0x6468544D || magic == 0x2054444B) {
        goto search;
    }
    return -1;

found:
    slot->field_4 = (s32)header;
    slot->field_0 = sequence_id;
    slot->field_2 = 2;
    return slot_index;

search:
    slot_index = 0;
    free_id = -1;
    slot = D_80086C00;
loop:
    if (slot->field_0 == free_id) {
        goto found;
    }
    slot_index++;
    slot++;
    if (slot_index < 8) {
        goto loop;
    }
    return -1;
}
