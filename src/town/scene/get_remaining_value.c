#include "common.h"
#include "town/scene.h"

extern s32 func_80017200(void);
/* Returns 20 minus the result of func_80017200. */
s32 get_remaining_value_to_20(void) { return 20 - func_80017200(); }
