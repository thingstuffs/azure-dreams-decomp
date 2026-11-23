#include "common.h"
#include "town/scene.h"

struct TownObjectSet;

extern s32 process_checked_entry(struct TownObjectSet *, s32); /* Unprototyped: retail call passes more arguments than the callee reads */
/* Calls set_dispatch_mode_two with object, entry_index and returns its result. */
s32 build_record_state_calling_state(TownObjectSet *object, s32 entry_index) { return process_checked_entry(object, entry_index); }
