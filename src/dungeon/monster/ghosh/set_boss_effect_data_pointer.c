#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/monster/ghosh.h"

#include "shared/entity.h"





/* Set the object's data pointer and clear the flag owner's high flag bit. */
void set_boss_effect_data_pointer(ActorRecord *object, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *flag_owner) {
    object->unk_8C.handler = &update_boss_actor_action;
    flag_owner->action_flags = (u16) (flag_owner->action_flags & 0x7FFF);
}
