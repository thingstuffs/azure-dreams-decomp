#include "common.h"
#include "town/player.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"


/* Update flags using the record and indexed entry, then return success. */
s32 update_entry_flags(void *record, s32 entry_index) {
    clear_script_flag_bit(*(s16 *)((s8 *)record + 0x18));
    set_script_flag_bit(*(s16 *)((entry_index * 0x10) + *(s32 *)((s8 *)record + 0x10) + 0xC));
    return 1;
}
