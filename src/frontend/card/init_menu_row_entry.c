#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

typedef struct S_8001B5B8_0 {
    u8 unk_00;
    s8 unk_01;
    u8 pad_02[0x2];
    s32 unk_04;
    u8 pad_08[0x2];
    s8 unk_0A;
    s8 unk_0B;
} S_8001B5B8_0;   /* arg1 in init_menu_row_entry */

/* Set entry fields for the given row and return the next entry address. */
void *init_menu_row_entry(void *context, void *entry_arg, s32 row_index) {
    S_8001B5B8_0 *entry = entry_arg;

    entry->unk_01 = 0x28;
    entry->unk_0A = (s8) ((row_index * 0xC) + 4);
    entry->unk_0B = 0x15;
    entry->unk_04 = 0x800000;
    entry->unk_00 = (u8) (entry->unk_00 | 0x80);
    return entry_arg + 0xC;
}
