#include "dungeon/system/submit_control_and_reset_status.h"
#include "dungeon/system/submit_control_and_reset_status.h"

/* Submit D_800DF3DC and reset D_800DCF4D to -1. */
void submit_control_and_reset_status(void) {
    Control_CD(6, &D_800DF3DC, 0);
    D_800DCF4D = -1;
}
#include "dungeon/system/submit_control_and_reset_status.h"

/* Passes D_800DF3E4 to Control_CD with selector 6 and a zero final argument. */
void submit_control_command_six(void) {
    Control_CD(6, &D_800DF3E4, 0);
}
#include "dungeon/system/submit_control_and_reset_status.h"

/* Submit the indexed eight-byte entry and finalize the operation. */
void submit_indexed_entry_and_finalize(s32 entry_index) {
    Control_CD(6, ((s32) (entry_index << 0x10) >> 0xD) + D_800DF3EC, 0);
    drain_cd_command_queue();
}
