#include "common.h"
#include "m2c_compat.h"

extern void *D_80016000;

typedef struct S_80016D20_0 {
    u8 pad_00[0x18];
    s32 unk_18;
} S_80016D20_0;   /* base in func_80016D20 */

/* Clear the indexed flag unless its identifier is 1. */
void func_80016D20(s32 flag_id) {
    s32 *flag_word;
    s32 word_index;
    s32 adjusted_id;
    S_80016D20_0 *context;

    if (flag_id != 1) {
        context = D_80016000;
        adjusted_id = flag_id;
        if (flag_id < 0) {
            adjusted_id = flag_id + 0x1F;
        }
        word_index = adjusted_id >> 5;
        flag_word = (word_index * 4) + context->unk_18;
        *flag_word &= ~(1 << (flag_id - (word_index << 5)));
    }
}
