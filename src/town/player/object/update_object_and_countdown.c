#include "common.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "town/player/object.h"

#include "town/player/initialize_record_with_handler_table_api.h"     /* extern */
#include "town/person/position.h"


/* Update the object and its countdown, dispatching expiry handling when it runs out. */
void update_object_and_countdown(TownObjectRecord *state, ObjectPosition *object, SpriteFrameState *sprite) {
    u16 ticks_left;

    object->z.w.i = query_lowered_transform_position(object);
    ticks_left = ((u16)state->unk_0A) - 1;
    state->unk_0A = ticks_left;
    if ((s16) ticks_left < 0) {
        initialize_record_with_handler_table(state, (object), sprite);
        return;
    }
    object->y.v = (s32) (object->y.v + 0xFFFE0000);
}
