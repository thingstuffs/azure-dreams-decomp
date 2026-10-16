#include "modules/dungeon_ovl_e0365c.h"

void dungeonAdvanceEntityMotionFadeAndRemoval(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    dungeonAdvanceActorRemoval(state, action, source, target);
}

