#ifndef TOWN_SCENE_EVENT_START_DISPATCH_EVENT_G01230_H
#define TOWN_SCENE_EVENT_START_DISPATCH_EVENT_G01230_H
/* Start dispatch event. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01230 - CL:town/func_804688AC. */

#include "common.h"
#include "shared/town_event_state.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "script_symbols.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

typedef void (*TownCallback)(s16, s16);

typedef struct S_8001975C_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001975C_0;

extern s32 func_8001E670(s32 id);
extern void func_8001E578(s32 id);
extern void func_8001E5F0(s32 id);
extern s32 find_first_enabled_entry_id(void);
extern s32 count_enabled_town_entries(void);
extern s32 find_first_enabled_paired_entry(void);
extern s32 advance_to_next_enabled_entry(void);

/* Shared import declarations; data casts preserve each measured view. */

/* Functions defined in this translation unit. */
s32 start_dispatch_event(void *init_arg);
s32 dispatch_active_event_27(void);
s32 is_dispatch_state_two(void);
void select_next_event_state(void);

#endif
