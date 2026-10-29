#include "common.h"
#include "slus.h"
#include "town/map.h"

/* tw_seq_end_chk: check whether sequence 1 has ended. */
s32 tw_seq_end_chk(void) {
    return read_sound_mode_blocking_status(1) == 0;
}
