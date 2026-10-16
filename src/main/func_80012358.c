#include "common.h"

extern void cardBootBuildSaveDescription(void *, s32);
extern void func_80025FFC(void *, s32);
void func_80025358(void *owner, s32 value) { cardBootBuildSaveDescription(owner, value); func_80025FFC(owner, value); }
