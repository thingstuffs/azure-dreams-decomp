#include "common.h"

extern s32 func_8001764C(s32);
s32 invoke_callback_and_set_shared_pointer(void) { return (func_8001764C(1) == 0); }
