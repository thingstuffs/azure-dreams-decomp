#include "common.h"
#include "m2c_compat.h"

extern s32 D_80019184;
/* Sets D_80019184 to one. */
void test_unless_3(void) { D_80019184 = 1; }
