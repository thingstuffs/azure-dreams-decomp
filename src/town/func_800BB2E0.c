#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B8A40_0 {
    u8 pad_00[0x3608];
    u8 unk_3608;
    u8 pad_3609[0x1];
    u8 unk_360A;
} S_800B8A40_0;   /* temp_v0_2 in func_800B8A40 */

/* Apply and clear pending byte updates, then copy two additional state bytes. */
void func_800B8A40(void) {
    volatile u8 *entry_base;
    s32 entry_index;
    s32 byte_index;
    u8 pending_value;
    u8 source_value;
    S_800B8A40_0 *byte_record;

    entry_index = 0;
    entry_base = (u8 *)0x80010000;
    do {
        pending_value = entry_base[0x33A5];
        if (pending_value != 0) {
            entry_base[0x33A4] = pending_value;
            entry_base[0x33A5] = 0;
        }
        entry_index += 1;
        entry_base += 2;
    } while (entry_index < 0x22);
    byte_index = 0;
    do {
        byte_record = byte_index + 0x80010000;
        source_value = byte_record->unk_360A;
        byte_index += 1;
        byte_record->unk_3608 = source_value;
    } while (byte_index < 2);
}
