#ifndef TOWN_SHOP_STATE_SET_LSHOP_SPECIAL_FLAG_G00699_H
#define TOWN_SHOP_STATE_SET_LSHOP_SPECIAL_FLAG_G00699_H
/* Set lshop special flag. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8032E634, CL:town/func_8032E6A8, CL:town/func_8032E9EC. */

#include "common.h"
#include "script_symbols.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"

/* extern */
typedef struct S_800191EC_0 {
    u8 unk_00;
    u8 unk_01;
} S_800191EC_0;

extern void release_lshop_entry(s32);
extern void compact_lshop_entry_list(void);

/* Functions defined in this translation unit. */
void set_water_medal_sold_flag(S_800191EC_0 *record);
void apply_shop_transaction(void *entries, s32 entry_mode);
void buy_flagged_entries(void *entries);
void sell_flagged_entries(u8 *entries);

#endif
