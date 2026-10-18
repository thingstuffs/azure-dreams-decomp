#include "modules/dungeon_cd_control.h"

/* Submit the indexed eight-byte entry and finalize the operation. */
void submit_indexed_entry_and_finalize(s32 entry_index) {
    Control_CD(6, ((s32) (entry_index << 0x10) >> 0xD) + D_800DF3EC, 0);
    drain_cd_command_queue();
}
