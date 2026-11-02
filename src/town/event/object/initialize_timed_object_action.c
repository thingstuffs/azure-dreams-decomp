#include "common.h"
#include "town/event/object_setup.h"
#include "town/event/object.h"
#include "shared/sprite_frame_state.h"

extern s32 D_800F8B6C[];

/* Initialize the record, clear its counter, and set its flags. */
void initialize_timed_object_action(TownObjectRecord *context, ObjectPosition *source, SpriteFrameState *record) {
    initialize_actor_action_with_defaults(context, source, record, &D_800F8B6C[0]);
    record->tpage_abr = 0;
    record->flags = record->flags | 0x1C;
}
