#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern void func_8001A554(s32);
/* Calls func_8001A554 with F_sbs32_pad12. */
void get_lookup_indexed_entry_byte(void) { func_8001A554(F_sbs32_pad12); }
