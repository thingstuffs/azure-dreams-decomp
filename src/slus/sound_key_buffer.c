/* Buffered SPU voice key changes and paired register-bit updates. */
#include "slus/sound_key_buffer.h"
#include "slus.h"


/* Reads or updates a 24-bit value stored across two words, marking buffered changes. */
u32 modify_spu_register_bit_pair(s32 mode, u32 value, s32 low_index, s32 high_index)
{
    u32 result;
    s32 dirty_bit;

    {
        typedef volatile u16 CacheWord;
        u32 high_bits;
        u32 low_word;

        if (spu_register_buffer_flags & 1) {
            CacheWord *branch_words = spu_register_shadow;
            high_bits = (branch_words[high_index] & 0xFF) << 16;
            low_word = branch_words[low_index];
            result = low_word | high_bits;
        } else {
            CacheWord *branch_words = spu_registers;
            high_bits = (branch_words[high_index] & 0xFF) << 16;
            low_word = branch_words[low_index];
            result = low_word | high_bits;
        }
        dirty_bit = 1;
    }

    switch (mode) {
    case 1:
        if (spu_register_buffer_flags & 1) {
            volatile u16 *words = spu_register_shadow;
            words[low_index] |= value;
            words[high_index] |= (value >> 16) & 0xFF;
            spu_register_dirty_flags |= dirty_bit << ((low_index - 0xC6) >> 1);
        } else {
            u16 *words = spu_registers;
            words[low_index] |= value;
            words[high_index] |= (value >> 16) & 0xFF;
        }
        result |= value & 0xFFFFFF;
        break;

    case 0:
        if (spu_register_buffer_flags & 1) {
            volatile u16 *words = spu_register_shadow;
            words[low_index] &= ~value;
            words[high_index] &= ~((value >> 16) & 0xFF);
            spu_register_dirty_flags |= dirty_bit << ((low_index - 0xC6) >> 1);
        } else {
            u16 *words = spu_registers;
            words[low_index] &= ~value;
            words[high_index] &= ~((value >> 16) & 0xFF);
        }
        result &= ~(value & 0xFFFFFF);
        break;

    case 8:
        if (spu_register_buffer_flags & 1) {
            volatile u16 *words = spu_register_shadow;
            words[low_index] = value;
            words[high_index] = (value >> 16) & 0xFF;
            spu_register_dirty_flags |= dirty_bit << ((low_index - 0xC6) >> 1);
        } else {
            u16 *words = spu_registers;
            words[low_index] = value;
            words[high_index] = (value >> 16) & 0xFF;
        }
        result = value & 0xFFFFFF;
        break;
    }
    return result & 0xFFFFFF;
}

/* Turns selected SPU voices on or off, queuing register writes when enabled. */
void set_spu_voice_keys(s32 key_on, u32 voices)
{
    u16 voices_lo;
    u16 voices_hi;

    voices &= 0xFFFFFF;
    voices_lo = voices;
    voices_hi = voices >> 16;

    switch (key_on) {
    case 1:
        if (spu_register_buffer_flags & 1) {
            spu_keyon_shadow[0] = voices_lo;
            spu_keyon_shadow[1] = voices_hi;
            spu_register_dirty_flags |= 1;
            spu_buffered_voice_mask |= voices;
            if (spu_keyoff_low_shadow & voices) {
                spu_keyoff_low_shadow &= ~voices;
            }
            if (spu_keyoff_high_shadow & voices_hi) {
                spu_keyoff_high_shadow &= ~voices_hi;
            }
        } else {
            s32 active_voices = spu_active_voice_mask;
            ((SpuKeyRegs *)spu_registers)->keyon_lo = voices_lo;
            ((SpuKeyRegs *)spu_registers)->keyon_hi = voices_hi;
            spu_active_voice_mask = active_voices | voices;
        }
        break;

    case 0:
        if (spu_register_buffer_flags & 1) {
            spu_keyoff_low_shadow = voices_lo;
            spu_keyoff_high_shadow = voices_hi;
            spu_register_dirty_flags |= 1;
            spu_buffered_voice_mask &= ~voices;
            if (spu_keyon_shadow[0] & voices) {
                spu_keyon_shadow[0] &= ~voices;
            }
            if (spu_keyon_shadow[1] & voices_hi) {
                spu_keyon_shadow[1] &= ~voices_hi;
            }
        } else {
            ((SpuKeyRegs *)spu_registers)->keyoff_lo = voices_lo;
            ((SpuKeyRegs *)spu_registers)->keyoff_hi = voices_hi;
            spu_active_voice_mask &= ~voices;
        }
        break;
    }
}
