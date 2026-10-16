/* Relink of matched dungeon/func_80F89D24 at file 0xFA9D24; imports and data use paired retail relocations. */
#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern s32 func_800AA430(void *, s32, void *, void *);

/* Forward all four bank callback arguments to the resident handler. */
void func_8015FE6C(void *state, s32 action, SpriteFrameState *source, EntityRec *target)
{
    func_800AA430(state, action, source, target);
}

