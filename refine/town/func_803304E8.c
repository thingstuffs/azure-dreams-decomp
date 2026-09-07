#include "common.h"

extern s32 D_80016000[3];
extern s32 D_80016000_reload[3] __asm__("D_80016000");

/* Sets the indexed bit in the global bitfield, ignoring index zero. */
void func_8001ACE8(s32 bit_index)
{
    register s32 value ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 *dst_word;
    s32 *src_word;
    s32 byte_offset;
    s32 biased_index;
    s32 bit_mask;

    if (bit_index != 0) {
        value = D_80016000[0];

        biased_index = bit_index;
        if (bit_index < 0) {
            biased_index = bit_index + 31;
        }
        byte_offset = (biased_index >> 5) * 4;
        value = *(s32 *)(value + 0x18);
        dst_word = (s32 *)(byte_offset + value);

        value = D_80016000_reload[0];
        src_word = (s32 *)(byte_offset + *(s32 *)(value + 0x18));
        ASM_KEEP(src_word);   /* MATCH pin: load-bearing for the whole function shape */

        value = bit_index;
        if (bit_index < 0) {
            value = bit_index + 31;
        }
        bit_mask = 1 << (bit_index - ((value >> 5) << 5));
        ASM_KEEP(bit_mask);   /* MATCH pin: load-bearing for the whole function shape */
        *dst_word = bit_mask | *src_word;
    }
}
