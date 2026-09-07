#include "common.h"

#include "common.h"

s32 func_8003C5F0();                                /* extern */

/* Checks whether the indexed table entry has a nonzero first word. */
s32 func_8003C890(s32 unused, s32 entry_index) {
    s32 entry_table;

    if ((entry_index < 0) || (entry_table = func_8003C5F0(), (entry_table == 0))) {
        return 0;
    }
    return (*(s32 *)((u8 *)(entry_table) + ((entry_index) * 8))) != 0;
}
