#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

typedef struct S_800945C4_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800945C4_0;

typedef struct S_800945C4_1 {
    u8 pad_00[0x46];
    s16 unk_46;
} S_800945C4_1;


/* Store the value with bit 15 set in the indexed entry's linked record. */
void set_linked_actor_pending_halfword(s32 entry_index, s32 value) {
    s32 entry_offset;
    s32 table_base;

    table_base = ((s32)dungeon_actor_ring_anchor);
    entry_offset = (s32) (entry_index << 0x10) >> 0xE;
    ((S_800945C4_1 *)(((S_800945C4_0 *)(entry_offset + table_base))->unk_AC))->unk_46 = (s16) (value | 0x8000);
}
