#ifndef TOWN_SHOP_RESOURCE_ENTRY_INITIALIZATION_G00617_H
#define TOWN_SHOP_RESOURCE_ENTRY_INITIALIZATION_G00617_H
/* Resource entry initialization declarations (G00617). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B5204. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B2964_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2964_0;

/* extern */
struct TownB4C60;

/* extern */
typedef struct S_800B29D0_0 {
    u8 pad_00[0x38];
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
} S_800B29D0_0;

s32 create_callback_pair_default();
void get_zero_based_group_index(struct TownB4C60 *);
/* extern */
s32 get_mode_selected_value();

/* Functions defined in this translation unit. */
void collect_enabled_entry_pointers(s32 *entries, s32 entry_count);
s32 count_nonzero_entries(s32 *entries);
s32 acquire_resource_and_initialize_state(void *state);

#endif
