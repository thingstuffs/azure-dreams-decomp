#include "common.h"

extern void func_8004437C(s16, s32);
extern void SD_Call(s32);

/* tw_sd_sq_ld_call_sub: load a nonzero sequence and submit the flagged load ID. */
s32 tw_sd_sq_ld_call_sub(s32 sequence_id, s32 load_id, s32 load_flags) {
    if (sequence_id != 0) {
        func_8004437C(sequence_id, 0);
    }
    if (load_id != 0) {
        SD_Call((load_id | load_flags) & 0xFFFF);
    }
    return 1;
}
