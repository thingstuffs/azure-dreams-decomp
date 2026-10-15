#ifndef TRANSITION_ABI_VIEWS_H
#define TRANSITION_ABI_VIEWS_H
#include "common.h"
/* The real four-input effect consumes only the low halfwords; the legacy
 * fifth operand is unused. These externs bind that same executable symbol. */
void transition_effect_legacy() __asm__("func_80099C58");
void transition_effect_halfwords(s16 x, s16 y, s16 z, s16 flags, s32 angle) __asm__("func_80099C58");
#endif
