#include "common.h"
#include "m2c_compat.h"

typedef struct S_801725F0_0 {
    u8 pad_00[0xBA];
    u8 unk_BA;
} S_801725F0_0;   /* D_80174CE0 in check_boss_effect_threshold */


extern S_801725F0_0 *ghosh_scripted_actor;

/* Check whether the stored byte meets the threshold. */
s32 check_boss_effect_threshold(s32 threshold) {
    return (s32) ghosh_scripted_actor->unk_BA >= threshold;
}
