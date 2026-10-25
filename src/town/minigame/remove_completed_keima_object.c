#include "town/minigame/keima.h"
#include "shared/object_flags.h"

typedef union KeimaExitNode {
    KeimaExitState *body;
    ObjectNodeHeader *node;
} KeimaExitNode;

void remove_completed_keima_object(KeimaExitState *effect) {
    KeimaState *owner;
    KeimaExitNode view;

    owner = effect->owner;
    if (effect->phase == 0 && (owner->flags & NODE_REMOVE)) {
        view.body = effect;
        view.node[-1].flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
