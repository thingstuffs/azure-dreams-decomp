#include "common.h"

extern s32 get_player_homerank();
extern u8 D_8008910C[];

/* Returns the first four-byte table entry whose first two bytes match the keys. */
u8 *func_8009F77C(s32 first_key, s32 second_key) {
    u8 last_indices[4];
    u8 *entry;
    u8 *scan_base;
    s32 index;
    s32 last_index;

    memcpy(last_indices, D_8008910C, 4);
    last_index = last_indices[get_player_homerank()];
    index = 0;
    if (last_index <= -1) {
        goto no_match;
    }
    entry = (u8 *) 0x80011F80;
    scan_base = (u8 *) 0x80010000;
loop:
    if ((scan_base[0x1F80] != first_key) || (scan_base[0x1F81] != second_key)) {
        entry += 4;
        index++;
        scan_base += 4;
        if (last_index < index) {
            goto no_match;
        }
        goto loop;
    }
    return entry;
no_match:
    return 0;
}
