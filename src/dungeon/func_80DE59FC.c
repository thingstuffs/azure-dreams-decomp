#include "modules/dungeon_ovl_e0365c.h"

void advance_entity_motion_fade_and_removal(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    advance_actor_removal(state, action, source, target);
}

