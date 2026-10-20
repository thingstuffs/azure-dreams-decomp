#include "script_symbols.h"
#include "common.h"

extern s32 func_80017798(s32);
s32 store_supplied_values(void) { return (func_80017798(F_sbs18_pad05) != 0); }
