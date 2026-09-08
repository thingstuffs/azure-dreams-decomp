#include "common.h"

extern void func_800540A8(void);
extern void func_8004425C(s32 arg0);
extern s16 func_80053DA8(s32 arg0);

/* tw_sd_se_ld_call: prepare sound loading and process the nonzero sound and sequence IDs. */
s32 func_800C1464(s32 sound_id, s32 sequence_id) {
    func_800540A8();
    if (sound_id != 0) {
        func_8004425C((s16)sound_id);
    }
    if (sequence_id != 0) {
        func_80053DA8(sequence_id & 0xFFFF);
    }
    return 1;
}
