#include "common.h"
#include "shared/object_flags.h"
#include "town/minigame.h"
#include "town/minigame/state.h"


/* Set object and global flags when the state is zero and subobject bit 3 is set. */
void retire_scene_label_after_exit_flag(TakoLabelBody *object) {
    s16 state = object->state;
    TakoMinigameState *sub = object->parent;

    if (state == 0 && (sub->flags & 8)) {
        ((u16 *)object)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
