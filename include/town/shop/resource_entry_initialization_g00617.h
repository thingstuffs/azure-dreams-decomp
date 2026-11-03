#ifndef TOWN_SHOP_RESOURCE_ENTRY_INITIALIZATION_G00617_H
#define TOWN_SHOP_RESOURCE_ENTRY_INITIALIZATION_G00617_H
/* Resource entry initialization declarations (G00617). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5204. */

#include "common.h"
#include "m2c_compat.h"
#include "town/shop/group_index.h"

typedef struct S_800B2964_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2964_0;

/* extern */

s32 create_callback_pair_default();
/* extern */

struct UA32;
struct ItemMenuInputObject;

/* Functions defined in this translation unit. */
void collect_enabled_entry_pointers(struct UA32 **entries, s32 entry_count);
s32 count_nonzero_entries(s32 *entries);
struct UA32 **acquire_resource_and_initialize_state(struct ItemMenuInputObject *state);

#endif
