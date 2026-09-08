#include "common.h"

extern void func_8004437C(s16, s32);
extern void func_80053DA8(s32);

/* tw_sd_sq_ld_call_sub: load a nonzero sequence and submit the flagged load ID. */
s32 func_800C1564(s32 sequence_id, s32 load_id, s32 load_flags) {
    if (sequence_id != 0) {
        func_8004437C(sequence_id, 0);
    }
    if (load_id != 0) {
        func_80053DA8((load_id | load_flags) & 0xFFFF);
    }
    return 1;
}
