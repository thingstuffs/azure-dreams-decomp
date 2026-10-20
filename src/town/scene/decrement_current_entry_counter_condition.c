#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct S_800169F8_1 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800169F8_1;


s32 func_8001894C();                         /* extern */

/* Decrement the current entry counter when condition 0x514 is active. */
void decrement_current_entry_counter_condition(void) {
    u8 counter;
    S_800169F8_1 *entry;

    if (func_8001894C(F_sbs07_pad29) != 0) {
        entry = (D_80016000->unk_08 * 8) + ((s32)D_80016000->unk_40);
        counter = entry->unk_02;
        if (counter != 0) {
            entry->unk_02 = (u8) (counter - 1);
        }
    }
}
