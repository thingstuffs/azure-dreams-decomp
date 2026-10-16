#ifndef TOWN_OVL_2D3F0C_H
#define TOWN_OVL_2D3F0C_H

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern void townBlendPositionAndTrace(s32 first_input, s32 second_input, s32 blend_weight, s32 remaining_weight);
void townSetFixedRecordParameters(void);
void townSetNegativeRecordParameters(void);
void townSetCurrentRecordLinkedStates(void);

#endif
