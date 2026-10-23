#include "common.h"
extern s32 *devkit_state_slots;
/* Clears a bit in the shared flag bitmap, leaving flag ID 1 unchanged. */
void clear_indexed_flag_bit(s32 flag_id) {
    s32 *flag_word;
    s32 word_index;
    s32 rounded_id;

    if (flag_id != 1) {
        rounded_id = flag_id;
        if (flag_id < 0) {
            rounded_id = flag_id + 0x1F;
        }
        word_index = rounded_id >> 5;
        flag_word = devkit_state_slots + word_index;
        *flag_word &= ~(1 << (flag_id - (word_index << 5)));
    }
}
