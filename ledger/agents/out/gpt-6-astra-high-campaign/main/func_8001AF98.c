#include "common.h"

extern void func_8007C040(s32 *arg0, s32 *arg1, s32 arg2);

extern s32 D_80400114[];
extern s32 D_80400120[];

/* Compute, store, and print the XOR checksum of the game-save work data. */
void func_8001AF98(void *gsw) {
    s32 *save_word;
    s32 word;
    s32 check_sum;
    s32 words_left;

    check_sum = 0;
    save_word = (s32 *)((u8 *)gsw + 0x208);
    words_left = 0x1781;
    do {
        word = *save_word;
        save_word += 1;
        words_left -= 1;
        check_sum ^= word;
    } while (words_left >= 0);
    *(s32 *)((u8 *)gsw + 0x204) = check_sum;
    func_8007C040(D_80400114, D_80400120, check_sum);
}
