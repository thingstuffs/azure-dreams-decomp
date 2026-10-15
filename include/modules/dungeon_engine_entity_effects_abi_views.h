#ifndef ENTITY_EFFECTS_ABI_VIEWS_H
#define ENTITY_EFFECTS_ABI_VIEWS_H
#include "common.h"
/* 64-slot finder returns -1 or 0..63; terrain returns (s16)work->best. */
s16 free_entry_short(void) __asm__("func_800A71F4");
s16 effect_height_short(s32 x, s32 y, s16 minimum) __asm__("func_800BCB04");
#endif
