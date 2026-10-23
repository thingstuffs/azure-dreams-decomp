#include "common.h"
#include "shared/def_table.h"
#include "engine/entity.h"

/*
 * Test whether the table byte XOR its upper nibble has its lowest two bits clear.
 *
 * Look up a byte field (offset 0x10) in a 20-byte-per-entry table indexed by a signed 16-bit id,
 * then test a 2-bit hash of (val ^ (val>>4)) for zero.
 */
s32 runtime_test_table_byte_pattern(s16 entry_id) {
    u32 value = item_action_definitions[entry_id].unk_10;
    return ((value ^ (value >> 4)) & 3) == 0;
}
