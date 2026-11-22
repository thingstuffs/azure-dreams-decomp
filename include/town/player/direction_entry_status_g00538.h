#ifndef TOWN_PLAYER_DIRECTION_ENTRY_STATUS_G00538_H
#define TOWN_PLAYER_DIRECTION_ENTRY_STATUS_G00538_H
/* shared declarations for direction entry status. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0464, PD:town/engine:800D046C. */

#include "common.h"
#include "shared/game_work.h"
#include "town/scene/collision.h"
#include "records/Rec_D_800CFCB4.h"

extern s16 D_800D0464[4];
extern s32 D_800D046C[4];
extern s32 input_angle_with_offset(s32 unused, s32 angle_offset);

/* Functions defined in this translation unit. */
s32 select_entry_by_input_direction(struct ColliderView *record);
s32 get_status_active_entry_matching_direction(struct ColliderView *entries);

#endif
