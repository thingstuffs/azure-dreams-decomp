#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017670;
void townRunSceneCallbacksWithValueShift(s32 value) { D_80017670 = value; }
