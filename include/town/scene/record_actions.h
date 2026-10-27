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

#endif
