#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AB778(void *, s32, void *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void func_80173524(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    func_800AB778(state, action, source, target);
}
