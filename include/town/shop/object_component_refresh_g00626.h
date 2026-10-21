#ifndef TOWN_SHOP_OBJECT_COMPONENT_REFRESH_G00626_H
#define TOWN_SHOP_OBJECT_COMPONENT_REFRESH_G00626_H
/* Refresh paired object components and their high flags (G00626): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B6EE8. */

#include "common.h"
#include "shared/object_flags.h"

typedef struct S_800B4648_1 {
    u8 pad_00[0x18];
    s32 * unk_18;
    u8 pad_1C[0x2C];
    s32 * unk_48;
} S_800B4648_1;

/* extern */
typedef struct S_800B4648_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800B4648_0;

void func_8004E99C(void *object);
extern void release_null_terminated_entries(void *entries);

/* Functions defined in this translation unit. */
void submit_five_paired_entry_values(S_800B4648_0 *owner);
void refresh_object_components_and_high_flag(u8 *object);

#endif
