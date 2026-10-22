#include "common.h"
#include "shared/record_ptrs.h"
#include "dungeon/player.h"


/* Set the indexed object value and its mirrored table entry. */
void set_linked_actor_code_and_mirror(s16 object_index, s8 value) {
    u8 *table_address;
    s32 object_offset = object_index * 4;
    void *object = *(void **)(object_offset + 0xAC + (u8 *)dungeon_actor_ring_anchor);
    *(s8 *)((u8 *)object + 0x12) = value;

    table_address = (u8 *)0x80010000 + (object_index * 2);
    *(s16 *)(table_address + 0x2098) = value & 0xFF;
}
