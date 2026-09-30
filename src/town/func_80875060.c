#include "common.h"

typedef void (*TownCallback)(s32);
typedef struct {
    TownCallback callback[3];
} TownCallbackTable;

extern u8 D_80700000[];
extern u8 D_80700BB4[];
extern s32 *D_80701968[];

/* Dispatch a callback based on the number of consecutive set flags in the list. */
void func_80875060(void) {
    TownCallbackTable callbacks;
    s16 *flag_ids;
    s16 *flag_cursor;
    s32 *flag_words;
    s32 matched_count;
    s32 id;
    s32 bits;
    s32 one;

    callbacks = *(TownCallbackTable *)(D_80700000 + 0xBC8);
    flag_ids = (s16 *)(D_80700BB4 + 8);
    matched_count = 0;
    if (*flag_ids != 0) {
        flag_words = D_80701968[0];
        one = 1;
        flag_cursor = flag_ids;
        do {
            id = *flag_cursor;
            bits = flag_words[id / 32] & (one << (id % 32));
            if (bits == 0) {
                break;
            }
            matched_count++;
            flag_cursor++;
        } while (*flag_cursor != 0);
    }
    callbacks.callback[matched_count](matched_count);
}
