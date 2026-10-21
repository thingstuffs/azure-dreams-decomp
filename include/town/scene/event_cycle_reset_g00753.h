/* G00753: Reset the event buffer and advance the eight step counter.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/ll34_657800_80016000:80019114.
 * Only the strong PD gap is included; complete file edges remain unknown.
 */
#ifndef TOWN_SCENE_EVENT_CYCLE_RESET_G00753_H
#define TOWN_SCENE_EVENT_CYCLE_RESET_G00753_H

#include "common.h"
#include "script_symbols.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

extern s8 D_80018AF8[];
extern u16 D_80019114;
extern s8 *D_80019118;
extern void func_80018548(s32);
extern void func_800185C0(s32);
extern s32 func_80018640(s32);

/* Functions defined in this translation unit. */
void reset_buffer_and_event_flags(void);
void advance_counter_modulo_eight(void);

#endif
