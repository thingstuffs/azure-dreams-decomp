#include "common.h"
#include "town/scene.h"

struct TownObjectSet;

extern s32 func_80017D48(struct TownObjectSet *, s32);
/* Calls func_80017D48 with object, entry_index and returns its result. */
s32 initialize_context_entry_tables_variant_1(TownObjectSet *object, s32 entry_index) { return func_80017D48(object, entry_index); }
