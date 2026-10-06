#include "shared/town_root.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"


/* Compacts the zero-terminated entry list by removing entries equal to -1. */
void func_80018EA8(void) {
    s8 *entries;
    s32 entry;
    s32 read_index;
    s32 write_index;
    s32 removed_entry;

    write_index = 0;
    entries = (s8 *)D_80016000->unk_38->entries;
    read_index = write_index;
    removed_entry = -1;
    for (; read_index < 0x14; read_index += 1) {
        entry = *(s32 *)(entries + (read_index * 4));
        if (entry == 0) {
            break;
        }
        if (entry != removed_entry) {
            if (read_index != write_index) {
                *(s32 *)(entries + (write_index * 4)) = entry;
            }
            write_index += 1;
        }
    }
    *(s32 *)(entries + (write_index * 4)) = 0;
}
