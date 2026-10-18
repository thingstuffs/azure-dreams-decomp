#include "common.h"

void func_800CD158(s32, s32, s32, s32);

/* Forward the state, object, and context to func_800CD158 with a fixed value of -15. */
void move_flag_object_with_step_minus_15(s32 state, s32 object, s32 context) {
    func_800CD158(state, object, context, -15);
}
