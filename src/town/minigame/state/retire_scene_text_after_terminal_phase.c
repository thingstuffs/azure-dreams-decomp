#include "common.h"
#include "shared/object_flags.h"
#include "town/minigame/state.h"
#include "shared/object_node.h"
#include "town/scene/collection.h"



/* Advances the context state and sets completion flags in response to entity fields. */
void retire_scene_text_after_terminal_phase(TerminalSceneTextObject *context) {
    s16 state;
    TownCollectionSequence *entity;

    state = context->state.s;
    entity = context->owner;
    switch (state) {
    case 0:
        if (entity->state.s == 0xFF) {
            context->flags &= 0xFFFD;
            context->state.u++;
        }
        break;
    case 1:
        if (entity->flags.u & 1) {
            (((ObjectNodeHeader *)context - 1)->flags) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}

/* MECHANISM: Frameless leaf with an explicit dispatch, state 0 before state 1, and a shared return.
   Width-accurate fields keep RMW order. */
