#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

typedef struct S_80094548_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80094548_0;

typedef struct S_80094548_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80094548_1;


/* Store the value scaled by 512 in the indexed object's field. */
void set_linked_actor_octant_facing(s32 index, s32 value) {
    s32 entry_offset;
    s32 table_base;

    table_base = ((s32)dungeon_actor_ring_anchor);
    entry_offset = (s32) (index << 0x10) >> 0xE;
    ((S_80094548_1 *)(((S_80094548_0 *)(entry_offset + table_base))->unk_AC))->unk_2A = (s16) (value << 9);
}
