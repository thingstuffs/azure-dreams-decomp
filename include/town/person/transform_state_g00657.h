#ifndef TOWN_PERSON_TRANSFORM_STATE_G00657_H
#define TOWN_PERSON_TRANSFORM_STATE_G00657_H
/* Transform state (G00657). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C520C. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_delay_views.h"

/* motion in update_transform_motion_page */
typedef struct S_800C2988_1 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x38];
    s32 * unk_50;
    u8 pad_54[0x1E];
    u16 unk_72;
} S_800C2988_1;

extern u8 D_800D4FB8;
void configure_the_set_mode_n_1();
/* extern */
extern s32 D_8006ADD4;
extern M2C_UNK D_800C2A10;
extern s16 D_800FE4A6;
extern s32 low_12_values_within_511(s16 value_a, s16 value_b);

/* Functions defined in this translation unit. */
void *get_transform_entry_by_index(s32 entry_index);
void update_transform_motion_page(void *object_data, void *motion_data);
void update_transform_state_value(void *object);

#endif
