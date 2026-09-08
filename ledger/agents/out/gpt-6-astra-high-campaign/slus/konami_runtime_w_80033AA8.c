#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x2D70];
    s32 words[0x800];
} MemoryPage;

/* Set the bitmap bit selected by the low 16 bits of the ID, skipping IDs 0 and 1. */
void func_80033AA8(s32 bit_id) {
    u32 bit_value = bit_id;
    u32 bit_index = bit_value & 0xFFFF;

    if (bit_index == 0) {
        return;
    }
    if (bit_index == 1) {
        return;
    }
    ((volatile MemoryPage *)0x80010000)->words[bit_index >> 5] |=
        1U << (bit_value & 0x1F);
}
