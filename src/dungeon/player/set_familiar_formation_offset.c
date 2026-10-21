#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

typedef struct S_8009456C_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8009456C_0;

typedef struct S_8009456C_1 {
    u8 pad_00[0x45];
    s8 unk_45;
} S_8009456C_1;


/* Set the byte at offset 0x45 in the object referenced by the selected entry. */
void set_familiar_formation_offset(s32 entry_index, s8 value) {
    s32 entry_offset;
    s32 table_base;

    table_base = ((s32)dungeon_actor_ring_anchor);
    entry_offset = (s32) (entry_index << 0x10) >> 0xE;
    ((S_8009456C_1 *)(((S_8009456C_0 *)(entry_offset + table_base))->unk_AC))->unk_45 = value;
}
