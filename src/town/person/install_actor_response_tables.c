#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/town_object.h"

/* extern */
extern s32 D_800D55A0[];
extern PersonDescriptor D_800D55A8;
extern s32 D_800D55D0[];
extern TownIndexedHandler D_800D55D4[];



#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
/* Install the actor's response tables and process input when either masked flag is set. */
void install_actor_response_tables(TownObjectRecord *actor, ObjectPosition *context, SpriteFrameState *input) {
    if (input->flags & 0x6000) {
        actor->state_handlers = D_800D55D0;
        actor->indexed_handlers = D_800D55D4;
        actor->animation_tables.as_pv = D_800D55A0;
        actor->descriptor = &D_800D55A8;
        apply_object_setup_and_update(actor, context, input);
    }
}
