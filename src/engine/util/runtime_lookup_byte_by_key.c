#include "common.h"
#include "engine/util.h"
#include "slus/data.h"

/* Returns the byte mapped to the low 16 bits of key, or the zero-terminator entry if absent. */
u8 runtime_lookup_byte_by_key(s32 key)
{
    s32 key_index;

    key_index = 0;
    while (resident_byte_lookup_keys[key_index] != 0) {
        if (resident_byte_lookup_keys[key_index] == (u16)key) {
            break;
        }
        key_index++;
    }
    return resident_byte_lookup_values[key_index];
}
