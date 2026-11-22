#include "common.h"
#include "town/scene/collection.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "town/scene/dialogue.h"
#include "town/data.h"

/* Clears panel flag 2 after a delay, then marks the panel for removal when the linked flag is set. */
void advance_delayed_panel_line(TownCollectionPanel *panel) {
    s16 state;
    u16 remaining;
    u16 next_state;
    u16 flags;
    TownCollectionSequence *sequence;

    state = panel->state;
    sequence = panel->sequence;
    switch (state) {
    case 0:
        remaining = panel->timer - 1;
        panel->timer = remaining;
        if ((remaining << 0x10) <= 0) {
            next_state = panel->state;
            flags = panel->flags;
            next_state++;
            flags &= 0xFFFD;
            panel->flags = flags;
            panel->state = next_state;
            return;
        }
        return;
    case 1:
        if (sequence->flags & TOWN_COLLECTION_FINISHED) {
            u16 *node_flags = &NODE_HEADER(panel)->flags;
            *node_flags |= 0x8000;
            scene_object_flags |= 0x8000;
        }
    default:
        return;
    }
}
