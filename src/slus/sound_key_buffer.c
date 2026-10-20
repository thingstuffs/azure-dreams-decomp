#include "slus/sound_key_buffer.h"


/* Reads or updates a 24-bit value stored across two words, marking buffered changes. */
u32 func_8005E4C4(s32 mode, u32 value, s32 low_index, s32 high_index)
{
    u32 result;
    s32 dirty_bit;

    {
        typedef volatile u16 CacheWord;
        u32 high_bits;
        u32 low_word;

        if (D_80079950 & 1) {
            CacheWord *branch_words = D_80086BD0;
            high_bits = (branch_words[high_index] & 0xFF) << 16;
            low_word = branch_words[low_index];
            result = low_word | high_bits;
        } else {
            CacheWord *branch_words = D_80079958;
            high_bits = (branch_words[high_index] & 0xFF) << 16;
            low_word = branch_words[low_index];
            result = low_word | high_bits;
        }
        dirty_bit = 1;
    }

    switch (mode) {
    case 1:
        if (D_80079950 & 1) {
            volatile u16 *words = D_80086BD0;
            words[low_index] |= value;
            words[high_index] |= (value >> 16) & 0xFF;
            D_8007951C |= dirty_bit << ((low_index - 0xC6) >> 1);
        } else {
            u16 *words = D_80079958;
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
            u16 *words = D_80079958;
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
            u16 *words = D_80079958;
            words[low_index] = value;
            words[high_index] = (value >> 16) & 0xFF;
        }
        result = value & 0xFFFFFF;
        break;
    }
    return result & 0xFFFFFF;
}

/* Turns selected SPU voices on or off, queuing register writes when enabled. */
void func_8005E97C(s32 key_on, u32 voices)
{
    u16 voices_lo;
    u16 voices_hi;

    voices &= 0xFFFFFF;
    voices_lo = voices;
    voices_hi = voices >> 16;

    switch (key_on) {
    case 1:
        if (D_80079950 & 1) {
            D_80086D58[0] = voices_lo;
            D_80086D58[1] = voices_hi;
            D_8007951C |= 1;
            D_80079518 |= voices;
            if (D_80086D5C & voices) {
                D_80086D5C &= ~voices;
            }
            if (D_80086D5E & voices_hi) {
                D_80086D5E &= ~voices_hi;
            }
        } else {
            s32 active_voices = D_800794F0;
            ((SpuKeyRegs *)D_80079958)->keyon_lo = voices_lo;
            ((SpuKeyRegs *)D_80079958)->keyon_hi = voices_hi;
            D_800794F0 = active_voices | voices;
        }
        break;

    case 0:
        if (D_80079950 & 1) {
            D_80086D5C = voices_lo;
            D_80086D5E = voices_hi;
            D_8007951C |= 1;
            D_80079518 &= ~voices;
            if (D_80086D58[0] & voices) {
                D_80086D58[0] &= ~voices;
            }
            if (D_80086D58[1] & voices_hi) {
                D_80086D58[1] &= ~voices_hi;
            }
        } else {
            ((SpuKeyRegs *)D_80079958)->keyoff_lo = voices_lo;
            ((SpuKeyRegs *)D_80079958)->keyoff_hi = voices_hi;
            D_800794F0 &= ~voices;
        }
        break;
    }
}
