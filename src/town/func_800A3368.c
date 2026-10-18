#include "modules/town_door.h"

/* Check interaction conditions, apply the target value, and trigger a positional effect. */
void trigger_door_interaction_effect(void *actor, void *target, void *position) {
    if (*(s16 *)((u8 *)actor + 0x68) == 0) {
        if (check_door_status_inverted(actor) != 0) {
            return;
        }
    } else {
        if (check_door_status_inverted(actor) == 0) {
            return;
        }
    }
    if (check_door_input_and_angle(actor, target) == 0) {
        return;
    }
    change_door_map(actor, *(s32 *)((u8 *)target + 0x48));
    *(void **)((u8 *)actor + 0x50) = &door_no_op;
    initialize_entity_handlers_and_position(*(s16 *)((u8 *)actor + 0x72), *(s16 *)((u8 *)position + 2), *(s16 *)((u8 *)position + 6));
}
