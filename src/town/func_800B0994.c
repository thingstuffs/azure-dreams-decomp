#include "common.h"

typedef struct {
    s32 words[17];
} Record68;

extern s32 D_80082A38[];

/* Copy a global state word and a 17-word block into the record. */
void copy_global_state_and_record_block(s32 *record) {
    s32 *base = D_80082A38;

    record[0xC] = base[0x20];
    *(Record68 *)(record + 0xD) = *(Record68 *)(base + 0x32);
}
