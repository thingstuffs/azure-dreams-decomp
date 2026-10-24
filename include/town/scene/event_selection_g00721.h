/* G00721: Initialize and resolve event selection with a fallback entry.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8046AC60, CL:town/func_8046AC98.
 * Only the two strong CL gaps are included; complete file edges remain unknown.
 */
#ifndef TOWN_SCENE_EVENT_SELECTION_G00721_H
#define TOWN_SCENE_EVENT_SELECTION_G00721_H

#include "common.h"
#include "shared/town_event_state.h"
#include "script_symbols.h"
#include "shared/town_root.h"
#include "shared/record_ptrs.h"

typedef struct {
    u8 value[8];
} LocalValues;

typedef s32 (*GetIndex)(s32);

typedef void (*UseValue)(s16, s32);

typedef void (*CallPair)(s32, s32);

typedef s16 *(*GetHalfword)(s32, s32);

typedef struct S_8001BD20_0 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_8001BD20_0;

extern s32 find_first_enabled_entry_id(void);
extern s32 check_event_value_in_list(s32);
extern s32 town_selected_valid_entry[];
s32 count_enabled_town_entries(void);
u8 reset_event_selection_and_advance(void);
extern LocalValues D_80019164;
extern s8 D_8001F2D4[];
extern s32 func_8001E670(s32);

/* Functions defined in this translation unit. */
s32 choose_valid_entry_or_fallback(s32 candidate);
void initialize_event_selection_state(s32 unused, s32 unused_second);
s32 handle_event_or_fallback(s32 fallback_first, s32 fallback_second);

#endif
