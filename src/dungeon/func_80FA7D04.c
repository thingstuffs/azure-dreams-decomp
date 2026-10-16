/* Relink of matched dungeon/func_80F89D04; every changed retail word is a paired relocation. */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 dungeonUpdateActorHopAndShrink(void *, s32, void *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void func_80155504(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    dungeonUpdateActorHopAndShrink(state, action, source, target);
}

