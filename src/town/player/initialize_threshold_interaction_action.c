#include "common.h"
#include "town/player.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

/* Install the airborne handler and clear the player timer. */
void initialize_threshold_interaction_action(TownPlayerRecord *record, ObjectPosition *unused_entity, s32 unused_context) {
    record->unk_00 = update_airborne_object_with_land_timer;
    record->timer = 0;
}
