#include "common.h"

extern s32 set_script_flag_bit();
extern s32 clear_script_flag_bit();

/* Update flags using the record and indexed entry, then return success. */
s32 update_entry_flags(void *record, s32 entry_index) {
    clear_script_flag_bit(*(s16 *)((s8 *)record + 0x18));
    set_script_flag_bit(*(s16 *)((entry_index * 0x10) + *(s32 *)((s8 *)record + 0x10) + 0xC));
    return 1;
}
