#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"

#include "town/person/object/initialize_object_entries_api.h"  /* extern */
#include "shared/vector.h"
#include "town/person.h"
void * create_offset_effect_object(ObjectPosition *source_pos);                     /* extern */
extern M2C_UNK D_800C84B8;
extern s32 D_800D62AC[];


/* Decrement the object's countdown and advance its state when it expires. */
void spawn_effect_after_timeout(TownObjectRecord *object, ObjectPosition *update_context, SpriteFrameState *state_context) {
    u16 ticks_left;

    ticks_left = object->timer - 1;
    object->timer = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        create_offset_effect_object(update_context);
        initialize_object_entries((object), state_context, D_800D62AC);
        object->handler = &D_800C84B8;
        object->timer = 0x15U;
    }
}
