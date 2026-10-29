#ifndef TOWN_EVENT_ENTRY_KIND_FILTERS_G00589_H
#define TOWN_EVENT_ENTRY_KIND_FILTERS_G00589_H
/* inferred-strong G00589: entry_kind_filters_g00589; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC118, CL:town/func_800AC278, CL:town/func_800AC2D8, CL:town/func_800AC37C. */

#include "common.h"
#include "script_symbols.h"
#include "engine/object/test_resident_bitmap_bit_api.h"

#define FIELD_U8(p, off) (*(u8 *)((u8 *)(p) + (off)))

extern s32 get_item_sell_money(void *entry);
extern s8 town_query_item_types[];
extern s32 town_query_sell_price_limits[];
extern s32 find_sentinel_table_value_index(s32 target_value);
extern u8 D_8006BC7A;
extern s32 *D_800D1038[];

/* Functions defined in this translation unit. */
s32 classify_listed_entry_type(u8 *entry);
s32 filter_entry_by_kind(s32 unused, u8 *entry);
s32 get_group_record_table_entry(s32 group_id, void *record);

#endif
