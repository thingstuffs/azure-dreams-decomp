#include "common.h"

extern void * town_scene_root;

typedef struct S_80016CCC_0 {
    u8 pad_00[0x18];
    s32 *unk_18;
} S_80016CCC_0;

/* Sets the indexed bit in the current object bitmap unless the index is zero. */
void set_flag_test_indexed_bit(s32 bit_index) {
    s32 *flag_word;
    s32 word_index;
    s32 adjusted_id;
    S_80016CCC_0 *context;

    if (bit_index != 0) {
        context = town_scene_root;
        adjusted_id = bit_index;
        if (bit_index < 0) {
            adjusted_id = bit_index + 0x1F;
        }
        word_index = adjusted_id >> 5;
        flag_word = (s32 *)((word_index * 4) + (long)context->unk_18);
        *flag_word = (1 << (bit_index - (word_index << 5))) | *flag_word;
    }
}
