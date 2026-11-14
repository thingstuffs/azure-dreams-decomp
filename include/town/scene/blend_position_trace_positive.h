#ifndef TOWN_OVL_2D3F0C_H
#define TOWN_OVL_2D3F0C_H

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern void blend_position_and_trace(s32 first_input, s32 second_input, s32 blend_weight, s32 remaining_weight);
void blend_position_trace_positive(void);
void blend_position_trace_negative(void);
void set_player_position_to_tile(void);

#endif
