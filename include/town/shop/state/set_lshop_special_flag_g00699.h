#ifndef TOWN_SHOP_STATE_SET_LSHOP_SPECIAL_FLAG_G00699_H
#define TOWN_SHOP_STATE_SET_LSHOP_SPECIAL_FLAG_G00699_H
/* Set lshop special flag. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00699 - CL:town/func_8032E634, CL:town/func_8032E6A8, CL:town/func_8032E9EC. */

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
extern void append_town_item(void *);

/* Functions defined in this translation unit. */
void set_lshop_special_flag(S_800191EC_0 *record);
void process_lshop_entries(void *entries, s32 entry_mode);
void process_lshop_value(void *entries);
void process_lshop_value_plus_four(u8 *entries);

#endif
