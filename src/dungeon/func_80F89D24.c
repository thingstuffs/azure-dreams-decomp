#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 advance_actor_removal(void *, s32, void *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void forward_bank_actor_callback_b(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    advance_actor_removal(state, action, source, target);
}

