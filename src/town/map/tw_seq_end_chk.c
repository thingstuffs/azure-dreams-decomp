#include "common.h"

s32 read_sound_mode_blocking_status(s32);                         /* extern */

/* tw_seq_end_chk: check whether sequence 1 has ended. */
s32 tw_seq_end_chk(void) {
    return read_sound_mode_blocking_status(1) == 0;
}
