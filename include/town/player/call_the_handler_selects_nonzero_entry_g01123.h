#ifndef TOWN_PLAYER_CALL_THE_HANDLER_SELECTS_NONZERO_ENTRY_G01123_H
#define TOWN_PLAYER_CALL_THE_HANDLER_SELECTS_NONZERO_ENTRY_G01123_H
/* call the handler selects nonzero entry g01123. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_80097264, CL:town/func_80097300. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "records/Rec_D_80082D58.h"

extern u8 animation_tick_scale;

/* Functions defined in this translation unit. */
void call_the_handler_selects_nonzero_entry(s32 *entries, TownObjectRecord *record, void *ptr2);
void apply_a_selected_source_byte_destination_adjusts_sixth_byte(u8 *sourceBytes, s32 selection, u8 *destination);
void store_the_in_forwards_field_10_callee_800949_c_4(s32 value, Rec_D_80082D58 *record, void *destination);
void call_the_selected_nonzero_table_callee_80094_a_38(s32 *values, TownObjectRecord *selector, void *ptr2);

#endif
