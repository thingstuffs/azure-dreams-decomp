/* G00731: Reset event state and dispatch the next eligible event.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8059E8A0, PD:town/ll34_51e000_80016000:80019088.
 * Only the two strong CL/PD gaps are included; complete file edges remain unknown.
 */
#ifndef TOWN_SCENE_EVENT_STATE_DISPATCH_G00731_H
#define TOWN_SCENE_EVENT_STATE_DISPATCH_G00731_H

#include "common.h"
#include "script_symbols.h"
#include "shared/town_pointees.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef struct TownEntry {
    s16 event;
    s16 check;
    s16 enabled;
    s16 pad_06;
} TownEntry;

extern s32 func_80018964(s32);
extern s32 func_800188E4();
extern void func_8001886C(s32);

extern TownEntry D_80019088[7];

/* Functions defined in this translation unit. */
s32 check_town_event_flags_clear(void);
void reset_town_event_state(void);
void advance_town_events_and_dispatch_entry(void);

#endif
