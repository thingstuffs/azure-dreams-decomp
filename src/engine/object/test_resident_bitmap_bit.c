#include "common.h"

#include "common.h"
#include "engine/object.h"

typedef struct {
    u8 pad[0x2D70];
    u32 words[0x800];
} MemoryPage;

/* Test an indexed bit, treating indices zero and one as constant false and true. */
s32 test_resident_bitmap_bit(s32 bit_id) {
    u32 bit_index = bit_id & 0xFFFF;
    u32 bit_value = 1;

    if (bit_index == 0) {
        return 0;
    }
    if (bit_index == bit_value) {
        return bit_value;
    }
    return ((((MemoryPage *)0x80010000)->words[bit_index >> 5]) &
            (bit_value << (bit_id & 0x1F))) != 0;
}
