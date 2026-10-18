#ifndef TOWN_OVL_2D3F0C_H
#define TOWN_OVL_2D3F0C_H

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern void blend_position_and_trace(s32 first_input, s32 second_input, s32 blend_weight, s32 remaining_weight);
void set_fixed_record_parameters(void);
void set_negative_record_parameters(void);
void set_current_record_linked_states(void);

#endif
