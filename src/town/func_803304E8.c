#include "common.h"
#include "shared/record_ptrs.h"

extern s32 D_80016000_reload[3] __asm__("D_80016000");

/* Sets the indexed bit in the global bitfield, ignoring index zero. */
void func_8001ACE8(s32 bit_index)
{
    s32 value;
    s32 *dst_word;
    s32 *src_word;
    s32 word_index;
    s32 table;
    s32 biased_index;
    u32 bit_mask;

    if (bit_index != 0) {
        value = ((s32)D_80016000);

        biased_index = bit_index;
        word_index = (biased_index / 32);
        table = *(s32 *)(value + 0x18);
        dst_word = (s32 *)(word_index * 4 + table);

        src_word = (s32 *)(*(s32 *)(D_80016000_reload[0] + 0x18) + word_index * 4);

        value = bit_index;
        bit_mask = 1 << (bit_index % 32);
        *dst_word = bit_mask | *src_word;
    }
}
