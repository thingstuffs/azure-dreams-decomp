#include "common.h"
#include "town/shop.h"
#include "town/shop/state.h"
#include "town/scene/collision.h"
#include "shared/town_object.h"
#include "shared/sprite_frame_state.h"

/*
 * Clears status byte 0x15 and installs move_toward_view_reference with
 * count eight.
 */
void start_move_toward_view_reference(TownObjectRecord *state, ColliderView *collider) {
    collider->enabled = 0;
    state->state_callback.as_pm = &move_toward_view_reference;
    state->timer = 8;
}
