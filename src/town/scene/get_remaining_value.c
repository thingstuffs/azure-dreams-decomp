#include "common.h"

extern s32 func_80017200(void);
s32 get_remaining_value_to_20(void) { return 20 - func_80017200(); }
