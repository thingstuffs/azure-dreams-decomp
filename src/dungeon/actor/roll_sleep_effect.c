#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"



#include "dungeon/actor/status.h"
#include "dungeon/actor.h"

/* Roll a chance against the record's stride and, on a win, run the action action. */
s32 roll_sleep_effect(ActorRecord *record, s16 chance, s8 action)
{
    s16 saved_chance = chance;
    s8 saved_action = action;
    s32 value;
    s16 divisor;
    s32 remainder;

    if (has_sleep_protection(record) != 0) {
        return 0;
    }

    value = generate_random_value() & 0xFFFF;
    if (((u8)(record->luck)) != 0) {
        divisor = ((u8)(record->luck));
        remainder = value % divisor;
    } else {
        remainder = 0;
    }
    value = saved_chance;
    divisor = value / 2;
    if ((remainder < divisor) || (value == 0xFF)) {
        if ((s16)set_or_clear_actor_status_slot(record, STATUS_SLEEP, saved_action) >= 0) {
            return 1;
        }
    }
    return 0;
}

