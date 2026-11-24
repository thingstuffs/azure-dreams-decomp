#include "town/minigame/state.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "town/scene/collection.h"

/* Clear the display flag after the delay and remove the text when the linked sequence finishes. */
void retire_delayed_scene_text_on_completion(TownCollectionText *object) {
    s16 state;
    TownCollectionSequence *status_data;
    u16 ticks_left;
    u16 flags;
    u16 next_state;

    state = object->state;
    status_data = object->sequence;
    switch (state) {
    case 0:
        ticks_left = object->timer - 1;
        object->timer = ticks_left;
        if ((ticks_left << 16) > 0) {
            return;
        }
        flags = object->flags;
        next_state = object->state;
        flags &= 0xFFFD;
        next_state++;
        object->flags = flags;
        object->state = next_state;
        break;
    case 1:
        if (status_data->flags & TOWN_COLLECTION_FINISHED) {
            NODE_HEADER(object)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
