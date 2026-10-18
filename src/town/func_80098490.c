#include "common.h"

extern s16 query_offset_position_minus_x(s32 vector, s32 entries, s32 entry_index);
extern s32 D_800D0414;

/* Call query_offset_position_minus_x with the input, D_800D0414, and parameter. */
s16 call_callee_8008_c_570_global_800_d_0414_parameter(s32 input_value, s32 parameter) {
    return query_offset_position_minus_x(input_value, D_800D0414, parameter);
}
