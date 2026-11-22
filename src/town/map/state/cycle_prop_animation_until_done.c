#include "modules/town_map_props.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/sprite_source.h"
#include "town/map/state.h"
#include "engine/script.h"

/* Cycles a town prop's animations as its script-controlled trigger becomes active or inactive. */
void cycle_prop_animation_until_done(TownPropAnimationActor *self, ObjectPosition *unused_position, SpriteFrameState *destination) {
    s32 state;
    SpriteSourceEntry *callValue;

    advance_sprite_animation_and_textures(destination);
    state = self->state;
    switch (state) {
    case 0:
        if (service_script_controller() && check_town_target_and_callback(self)) {
            callValue = self->sources[1];
            select_record_entry_and_value(destination, callValue, 0);
            self->state++;
            return;
        }
        return;
    case 1:
        if (destination->flags & 0x6000) {
            callValue = self->sources[2];
            select_record_entry_and_value(destination, callValue, 0);
            self->state++;
            return;
        }
        return;
    case 2:
        if (service_script_controller() && check_town_target_and_callback(self)) {
            return;
        }
        self->state++;
        return;
    case 3:
        if (!(service_script_controller() && check_town_target_and_callback(self))) {
            return;
        }
        callValue = self->sources[0];
        select_record_entry_and_value(destination, callValue, 0);
        self->state++;
        return;
    case 4:
        if (service_script_controller()) {
            if (check_town_target_and_callback(self)) {
                return;
            }
        }
        self->state = 0;
    }
}
