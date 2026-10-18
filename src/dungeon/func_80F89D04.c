#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 update_actor_hop_and_shrink(void *, s32, void *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void forward_bank_actor_callback_a(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    update_actor_hop_and_shrink(state, action, source, target);
}

