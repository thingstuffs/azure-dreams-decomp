#include "modules/town_door.h"

/* Set the entity effect and emit it at the supplied position when the checks pass. */
void emit_door_position_effect(S800A3088Arg0 *entity, s32 action, S800A3088Arg2 *position) {
    if (entity->unk68 == 0) {
        if (check_door_status_inverted(entity) != 0) {
            return;
        }
    } else if (check_door_status_inverted(entity) == 0) {
        return;
    }
    if (check_door_input_and_angle(entity, action) != 0) {
        entity->unk50 = open_door_to_target;
        action = position->unk2;
        initialize_player_entity_callbacks(entity->unk72, action, position->unk6);
    }
}
