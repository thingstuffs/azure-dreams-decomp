/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

extern s8 D_80016000[];

typedef struct S_80018EA8_0 {
    u8 pad_00[0x38];
    s32 unk_38;
} S_80018EA8_0;   /* *(s8 **)D_80016000 in func_80018EA8 */

/* Compacts the zero-terminated entry list by removing entries equal to -1. */
void func_80018EA8(void) {
    s8 *entries;
    s32 entry;
    s32 read_index;
    s32 write_index;
    s32 removed_entry;

    write_index = 0;
    entries = (s8 *)((S_80018EA8_0 *)(*(s8 **)D_80016000))->unk_38 + 0x29C;
    read_index = write_index;
    removed_entry = -1;
scan_entry:
    entry = *(s32 *)(entries + (read_index * 4));
    if (entry != 0) {
        if (entry != removed_entry) {
            if (read_index != write_index) {
                *(s32 *)(entries + (write_index * 4)) = entry;
            }
            write_index += 1;
        }
        read_index += 1;
        if (read_index < 0x14) {
            goto scan_entry;
        }
    }
    *(s32 *)(entries + (write_index * 4)) = 0;
}
