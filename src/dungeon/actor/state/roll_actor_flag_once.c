#include "dungeon/actor/state.h"
#include "shared/entity.h"

extern s32 generate_random_value(void);

/* Once per actor, roll flag 0x100 using its divisor. */
void roll_actor_flag_once(void *actor_data, s32 divisor) {
    ActorRecord *object;
    s32 state_flags;
    u16 result_flags;

    object = actor_data;
    state_flags = object->flags14;
    if (!(state_flags & 0x8000)) {
        object->flags14 = (s32) (state_flags | 0x8000);
        if (((s32) (generate_random_value() & 0xFFFF) % divisor) != 0) {
            result_flags = object->action_state_flags;
            result_flags = (u16) (result_flags & 0xFEFF);
        } else {
            result_flags = object->action_state_flags;
            result_flags = (u16) (result_flags | 0x100);
        }
        object->action_state_flags = result_flags;
    }
}
