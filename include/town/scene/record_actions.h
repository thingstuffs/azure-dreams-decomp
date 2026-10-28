#ifndef TOWN_SCENE_RECORD_ACTIONS_H
#define TOWN_SCENE_RECORD_ACTIONS_H

#include "common.h"
#include "records/Rec_func_800165F4_arg0.h"

s32 apply_selected_entry_values(Rec_func_800165F4_arg0 *record, s32 entry_index);
s32 check_record_flag_if_unblocked(void *record);
/* Placed entry points for apply_selected_entry_values. */
s32 func_800173CC(Rec_func_800165F4_arg0 *record, s32 entry_index);
s32 func_8001991C(Rec_func_800165F4_arg0 *record, s32 entry_index);
s32 func_80017D80(Rec_func_800165F4_arg0 *record, s32 entry_index);

s32 func_800176B8(Rec_func_800165F4_arg0 *record, s32 entry_index);
s32 func_80018504(Rec_func_800165F4_arg0 *record, s32 entry_index);
void set_indexed_entry_flag(Rec_func_800165F4_arg0 *record, s32 entry_index);

s32 process_context_entry_with_fallback(Rec_func_800165F4_arg0 *record, s32 entry_index);
void dispatch_after_condition_12_c_4(Rec_func_800165F4_arg0 *record, s32 entry_index);
s32 dispatch_if_condition_1463(Rec_func_800165F4_arg0 *record, s32 entry_index);

#endif
