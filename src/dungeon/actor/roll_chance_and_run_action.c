#include "common.h"

typedef struct S_800C8ABC_0 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800C8ABC_0;   /* held_arg0 in roll_chance_and_run_action */


extern s32 set_or_clear_actor_status_slot();
extern s32 generate_random_value();
extern s32 is_linked_entity_flagged_2000000(void *record);

/* Roll a chance against the record's stride and, on a win, run the action action. */
s32 roll_chance_and_run_action(void *record, s16 chance, s8 action)
{
    s16 saved_chance = chance;
    s8 saved_action = action;
    s32 value;
    s16 divisor;
    s32 remainder;

    if (is_linked_entity_flagged_2000000(record) != 0) {
        return 0;
    }

    value = generate_random_value() & 0xFFFF;
    if (((u8)(((S_800C8ABC_0 *)(record))->unk_03)) != 0) {
        divisor = ((u8)(((S_800C8ABC_0 *)(record))->unk_03));
        remainder = value % divisor;
    } else {
        remainder = 0;
    }
    value = saved_chance;
    divisor = value / 2;
    if ((remainder < divisor) || (value == 0xFF)) {
        if ((s16)set_or_clear_actor_status_slot(((S_800C8ABC_0 *)(record)), 1, saved_action) >= 0) {
            return 1;
        }
    }
    return 0;
}

/* MECHANISM: Pin the three live arguments to retail's s0/s1/s2 roles so the
   0x20 frame and save order match; defer their guarded keeps past the opening
   call for the s2 delay move, and reuse the v0 divisor carrier for chance/2. */
