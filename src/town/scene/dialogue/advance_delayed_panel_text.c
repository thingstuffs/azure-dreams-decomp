#include "common.h"
#include "town/scene/collection.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "town/scene/dialogue.h"
#include "town/data.h"

/* Clears text flag 2 after a delay, then marks the text node for removal when the linked flag is set. */
void advance_delayed_panel_text(TownCollectionText *text) {
    s16 state;
    s32 remaining;
    u16 next_state;
    u16 flags;
    TownCollectionSequence *sequence;

    state = text->state;
    sequence = text->sequence;
    switch (state) {
    case 0:
        remaining = text->timer - 1;
        text->timer = remaining;
        if ((s16)remaining <= 0) {
            next_state = text->state;
            flags = text->flags;
            next_state++;
            flags &= 0xFFFD;
            text->flags = flags;
            text->state = next_state;
            return;
        }
        return;
    case 1:
        if (sequence->flags & TOWN_COLLECTION_FINISHED) {
            u16 *node_flags = &NODE_HEADER(text)->flags;
            *node_flags |= NODE_REMOVE;
            scene_object_flags |= OBJECT_REMOVE_PENDING;
        }
        /* fall through */
    default:
        return;
    }
}
