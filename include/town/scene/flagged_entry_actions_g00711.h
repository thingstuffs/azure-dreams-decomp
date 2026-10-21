#ifndef TOWN_SCENE_FLAGGED_ENTRY_ACTIONS_G00711_H
#define TOWN_SCENE_FLAGGED_ENTRY_ACTIONS_G00711_H
/* Process flagged entries and clear scene history (G00711). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80471198. */

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "script_symbols.h"
#include "shared/town_event_buffer.h"

s8 *func_80018824(s8 *, s32);
void func_8001844C(s32 entry_code);
void func_8001A418(s32 code);

/* Functions defined in this translation unit. */
void clear_state_history_and_head_indices(void);
void process_flagged_type_0x18_entries(void);

#endif
