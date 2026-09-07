#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800661B0(); /* extern */
s32 func_80122FA8();                             /* extern */

typedef struct S_801239B8_0 {
    u8 high_byte;
    u8 low_byte;
} S_801239B8_0;   /* var_s0 in func_801239B8 */

/* Processes a zero-terminated sequence of encoded entries and emits each resolved entry at successive positions. */
void func_801239B8(u8 *encoded_entries, s16 initial_position, s16 position_step) {
    s16 current_position;
    s32 resolved_entry;
    u8 *entry_ptr;
    u8 high_byte;
    u8 low_byte;

    entry_ptr = encoded_entries;
    current_position = initial_position;
    if (*entry_ptr != 0) {
        do {
            high_byte = ((S_801239B8_0 *)entry_ptr)->high_byte;
            low_byte = ((S_801239B8_0 *)entry_ptr)->low_byte;
            entry_ptr += 2;
            resolved_entry = func_80122FA8(low_byte | (high_byte << 8));
            if (resolved_entry != 0) {
                func_800661B0(resolved_entry, 0, 0, current_position, (s32) position_step, 0xC, 0x10);
                current_position += 3;
            }
        } while (*entry_ptr != 0);
    }
}
