#include "common.h"
#include "frontend/libcard.h"

extern void func_804086CC(s32);
extern s32 func_804086BC(s32, s32, s32);
s32 libcard_select_slot(s32 slot) { func_804086CC(slot); return func_804086BC(slot, 0x3F, 0); }
