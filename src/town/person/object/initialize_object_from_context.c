#include "common.h"
#include "m2c_compat.h"

extern s32 scale_random_to_unsigned_halfword_limit();
extern void initialize_object_entries();
#include "records/Rec_func_80094268_arg0.h"
void count_down_and_select_next_setup(Rec_func_80094268_arg0 *object, s32 request_data, s32 request_param, s32 check_param);
extern M2C_UNK D_800D7284;

// Initializes an object with shared data and a generated value scaled in units of 21.
void initialize_object_from_context(void *object, s32 unusedArg, s32 initValue) {
    initialize_object_entries(object, initValue, &D_800D7284);
    *(s32 **)((u8 *)object + 0x50) = &count_down_and_select_next_setup;
    *(s16 *)((u8 *)object + 0x6C) = (s16)(((scale_random_to_unsigned_halfword_limit(4) & 0xFFFF) * 0x15) + 0x15);
}
