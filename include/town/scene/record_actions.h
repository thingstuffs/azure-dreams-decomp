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

s32 process_context_entry_with_fallback(Rec_func_800165F4_arg0 *record, s32 entry_index);
void apply_selected_entry_values_for_mascot1(Rec_func_800165F4_arg0 *record, s32 entry_index);
s32 set_entry_flag_if_s24_door_open(Rec_func_800165F4_arg0 *record, s32 entry_index);

#endif
