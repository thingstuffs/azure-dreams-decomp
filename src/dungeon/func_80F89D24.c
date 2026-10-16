#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonAdvanceActorRemoval(void *, s32, void *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void dungeonForwardBankActorCallbackB(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    dungeonAdvanceActorRemoval(state, action, source, target);
}

