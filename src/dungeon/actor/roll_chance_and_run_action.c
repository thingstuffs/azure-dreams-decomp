#include "shared/actor_status_ids.h"
#include "common.h"



#include "dungeon/actor/status.h"
#include "dungeon/actor.h"
extern s32 generate_random_value(void);

/* Roll a chance against the record's stride and, on a win, run the action action. */
s32 roll_chance_and_run_action(void *record_arg, s16 chance, s8 action)
{
    ActorRecord *record = record_arg;
    s16 saved_chance = chance;
    s8 saved_action = action;
    s32 value;
    s16 divisor;
    s32 remainder;

    if (is_linked_entity_flagged_2000000(record_arg) != 0) {
        return 0;
    }

    value = generate_random_value() & 0xFFFF;
    if (((u8)(record->unk_00[3])) != 0) {
        divisor = ((u8)(record->unk_00[3]));
        remainder = value % divisor;
    } else {
        remainder = 0;
    }
    value = saved_chance;
    divisor = value / 2;
    if ((remainder < divisor) || (value == 0xFF)) {
        if ((s16)set_or_clear_actor_status_slot(record_arg, STATUS_SLEEP, saved_action) >= 0) {
            return 1;
        }
    }
    return 0;
}

