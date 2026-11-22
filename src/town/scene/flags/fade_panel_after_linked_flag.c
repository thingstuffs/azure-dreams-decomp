#include "common.h"
#include "town/scene/collection.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "town/scene/flags.h"
#include "town/data.h"

/* Advances a delayed fade and sets completion flags when the color reaches its threshold. */
void fade_panel_after_linked_flag(TownCollectionPanel *panel) {
    s16 state;
    s32 color;
    u16 timer;
    TownCollectionSequence *sequence;
    s16 next_state;
    u16 flags;

    state = panel->state;
    sequence = panel->sequence;
    switch (state) {
    case 0:
        timer = panel->timer - 1;
        panel->timer = timer;
        if ((timer << 0x10) <= 0) {
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
            panel->state = state + 1;
            return;
        }
        break;
    case 2:
        color = panel->color + 0xFFF7F7F8;
        panel->color = color;
        if (color <= 0x80808) {
            u16 *node_flags = &NODE_HEADER(panel)->flags;
            *node_flags |= 0x8000;
            scene_object_flags |= 0x8000;
        }
        break;
    }
}
