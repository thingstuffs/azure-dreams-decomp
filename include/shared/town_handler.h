#ifndef SHARED_TOWN_HANDLER_H
#define SHARED_TOWN_HANDLER_H

#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082D58.h"

struct S_80094A60_0;

/* The third argument is the destination carried through the handler helpers. */
void call_the_handler_selects_nonzero_entry(s32 *entries, Rec_func_80094268_arg0 *record, void *ptr2);
void call_the_selected_nonzero_table_callee_80094_a_38(s32 *values, struct S_80094A60_0 *selector, void *ptr2);
void store_the_in_forwards_field_10_callee_800949_c_4(s32 value, Rec_D_80082D58 *record, void *ptr2);
void apply_a_selected_source_byte_destination_adjusts_sixth_byte(u8 *sourceBytes, s32 selection, u8 *destination);

#endif
