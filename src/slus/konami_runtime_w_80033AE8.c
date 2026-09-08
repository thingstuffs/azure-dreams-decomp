#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x2D70];
    s32 words[0x800];
} MemoryPage;

/* Clears the indexed bit in the fixed flag array, except for indices zero and one. */
void func_80033AE8(s32 flag_id) {
    u32 flag_value = flag_id;
    u32 flag_index = flag_value & 0xFFFF;
    u32 bit_mask = 1;

    if (flag_index == 0) {
        return;
    }
    if (flag_index == bit_mask) {
        return;
    }
    ((volatile MemoryPage *)0x80010000)->words[flag_index >> 5] &=
        ~(bit_mask << (flag_value & 0x1F));
}
