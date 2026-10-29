#include "modules/town_map_props.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/sprite_source.h"
#include "town/map/state.h"

typedef struct TownPropAnimationActor {
    char pad0[0x68];
    s16 state;   /* 0x68 */
    char pad6A[0xA0 - 0x6A];
    SpriteSourceEntry *fieldA0; /* 0xA0 */
    SpriteSourceEntry *fieldA4; /* 0xA4 */
    SpriteSourceEntry *fieldA8; /* 0xA8 */
} S0;



/* Cycles a town prop's animations as its script-controlled trigger becomes active or inactive. */
void copy_record_state_to_destination(S0 *self, s32 unused_value, SpriteFrameState *destination) {
    S0 *obj = self;
    SpriteFrameState *dst= destination;
    s32 state;
    SpriteSourceEntry *callValue;

    advance_sprite_animation_and_textures(dst);
    state = obj->state;
    switch (state) {
    case 0:
        if (service_script_controller() && check_transform_identifier_and_hook(obj)) {
            callValue = obj->fieldA4;
            select_record_entry_and_value(dst, callValue, 0);
            obj->state = (u16)obj->state + 1;
            return;
        }
        return;
    case 1:
        if (dst->flags & 0x6000) {
            callValue = obj->fieldA8;
            select_record_entry_and_value(dst, callValue, 0);
            obj->state = (u16)obj->state + 1;
            return;
        }
        return;
    case 2:
        if (service_script_controller() && check_transform_identifier_and_hook(obj)) {
            return;
        }
        obj->state = (u16)obj->state + 1;
        return;
    case 3:
        if (!(service_script_controller() && check_transform_identifier_and_hook(obj))) {
            return;
        }
        callValue = obj->fieldA0;
        select_record_entry_and_value(dst, callValue, 0);
        obj->state = (u16)obj->state + 1;
        return;
    case 4:
        if (service_script_controller()) {
            if (check_transform_identifier_and_hook(obj)) {
                return;
            }
        }
        obj->state = 0;
    }
}
