#include "common.h"

extern volatile u16 D_80086BD0[];
extern volatile u16 *D_80079958;
extern s32 D_80079950;
extern volatile s32 D_8007951C;

/* Reads or updates a 24-bit value stored across two words, marking buffered changes. */
u32 func_8005E4C4(s32 mode, u32 value, s32 low_index, s32 high_index)
{
    u32 result;
    s32 dirty_bit;

    {
        register volatile u16 *words ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        u32 high_bits;
        u32 low_word;

        if (D_80079950 & 1) {
            words = D_80086BD0;
        } else {
            words = D_80079958;
        }
        high_bits = (words[high_index] & 0xFF) << 16;
        low_word = words[low_index];
        ASM_USE2_NV(dirty_bit, high_bits);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
        dirty_bit = 1;
        result = low_word | high_bits;
    }

    switch (mode) {
    case 1:
        if (D_80079950 & 1) {
            volatile u16 *words = D_80086BD0;
            words[low_index] |= value;
            words[high_index] |= (value >> 16) & 0xFF;
            D_8007951C |= dirty_bit << ((low_index - 0xC6) >> 1);
        } else {
            volatile u16 *words = D_80079958;
            words[low_index] |= value;
            words[high_index] |= (value >> 16) & 0xFF;
        }
        result |= value & 0xFFFFFF;
        break;

    case 0:
        if (D_80079950 & 1) {
            volatile u16 *words = D_80086BD0;
            words[low_index] &= ~value;
            words[high_index] &= ~((value >> 16) & 0xFF);
            D_8007951C |= dirty_bit << ((low_index - 0xC6) >> 1);
        } else {
            volatile u16 *words = D_80079958;
            words[low_index] &= ~value;
            words[high_index] &= ~((value >> 16) & 0xFF);
        }
        result &= ~(value & 0xFFFFFF);
        break;

    case 8:
        if (D_80079950 & 1) {
            volatile u16 *words = D_80086BD0;
            words[low_index] = value;
            words[high_index] = (value >> 16) & 0xFF;
            D_8007951C |= dirty_bit << ((low_index - 0xC6) >> 1);
        } else {
            volatile u16 *words = D_80079958;
            words[low_index] = value;
            words[high_index] = (value >> 16) & 0xFF;
        }
        result = value & 0xFFFFFF;
        break;
    }
    return result & 0xFFFFFF;
}
