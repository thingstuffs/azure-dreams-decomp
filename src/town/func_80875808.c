#include "common.h"
extern s32 *D_80701968;
void func_80701808(s32 flag_id) {
    s32 *flag_word;
    s32 word_index;
    s32 rounded_id;

    if (flag_id != 0) {
        rounded_id = flag_id;
        if (flag_id < 0) {
            rounded_id = flag_id + 0x1F;
        }
        word_index = rounded_id >> 5;
        flag_word = D_80701968 + word_index;
        *flag_word |= 1 << (flag_id - (word_index << 5));
    }
}
