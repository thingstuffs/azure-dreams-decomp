/* Transform state (G00657). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800C520C. */
#include "town/person/transform_state_g00657.h"

/* Returns the address of the indexed 24-byte entry. */
void *get_transform_entry_by_index(s32 entry_index) {
    return (entry_index * 0x18) + &D_800D4FB8;
}

/* Sets the motion page and updates the object state and orientation. */
void update_transform_motion_page(void *object_data, void *motion_data) {
    register DelayMotionZ *motion = motion_data;

    u32 page;

    if (D_8006ADD4 == 0x17000C) {
        motion->unk_08 = 0xFF600000;
    } else {
        motion->unk_08 = 0xFFE00000;
    }
    configure_the_set_mode_n_1(((S_800C2988_1 *)(object_data)), motion, get_transform_entry_by_index(0));
    ((S_800C2988_1 *)(object_data))->unk_50 = &D_800C2A10;
    ((S_800C2988_1 *)(object_data))->unk_16 = (s16) ((((S_800C2988_1 *)(object_data))->unk_72 - 0x800) & 0xFFF);
}

/* Update the object's state value according to whether the pair check returns zero. */
void update_transform_state_value(void *object) {
    s32 result;

    result = low_12_values_within_511(D_800FE4A6, *(s16 *)((s8 *)object + 0x16));
    if (result != 0) {
        *(s32 *)((s8 *)object + 0xC) = get_transform_entry_by_index(0);
    } else {
        *(s32 *)((s8 *)object + 0xC) = get_transform_entry_by_index(1);
    }
}
