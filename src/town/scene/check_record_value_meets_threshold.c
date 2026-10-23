#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



extern u32 D_80019438;


/* Check whether the record value meets the threshold in D_80019438. */
s32 check_record_value_meets_threshold(void) {
    return (u32) town_scene_root->town_state->money >= (u32) D_80019438;
}
