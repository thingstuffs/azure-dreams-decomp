#include "common.h"

s32 func_800CD158(s32, s32, s32, s32);

/* Forward three inputs to func_800CD158 with a fixed fourth argument of -10. */
void move_flag_object_with_step_minus_10(s32 input_first, s32 input_second, s32 input_third) {
    func_800CD158(input_first, input_second, input_third, -0xA);
}
