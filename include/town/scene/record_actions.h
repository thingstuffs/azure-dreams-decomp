#ifndef TOWN_SCENE_RECORD_ACTIONS_H
#define TOWN_SCENE_RECORD_ACTIONS_H

#include "common.h"
#include "records/Rec_func_800165F4_arg0.h"
struct TownObjectSet;

s32 apply_selected_entry_values(struct TownObjectSet *record, s32 entry_index);
s32 check_record_flag_if_unblocked(const struct TownObjectSet *record);
/* Placed entry points for apply_selected_entry_values. */
s32 func_800173CC(struct TownObjectSet *record, s32 entry_index);
s32 func_8001991C(struct TownObjectSet *record, s32 entry_index);
s32 func_80017D80(struct TownObjectSet *record, s32 entry_index);

s32 func_800176B8(Rec_func_800165F4_arg0 *record, s32 entry_index);
s32 func_80018504(struct TownObjectSet *record, s32 entry_index);

s32 process_context_entry_with_fallback(struct TownObjectSet *record, s32 entry_index);
s32 apply_selected_entry_values_for_mascot1(struct TownObjectSet *entry, s32 entry_index);
s32 set_entry_flag_if_s24_door_open(struct TownObjectSet *record, s32 entry_index);

struct TownRecord;
struct TownRecord *populate_records_and_normalize_kind(void);

#endif
