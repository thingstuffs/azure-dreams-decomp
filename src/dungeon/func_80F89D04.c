#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonUpdateActorHopAndShrink(void *, s32, void *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void dungeonForwardBankActorCallbackA(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    dungeonUpdateActorHopAndShrink(state, action, source, target);
}

