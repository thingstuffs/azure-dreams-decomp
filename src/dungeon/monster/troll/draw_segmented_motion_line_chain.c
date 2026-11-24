#include "common.h"
#include "shared/object_node.h"
#include "dungeon/monster/troll.h"

/* Draw the registered chain of motion line effects in mode zero. */
s32 draw_segmented_motion_line_chain(struct SegmentedLineState *state, ObjectPosition *position, SpriteFrameState *sprite) {
    ObjectNodeHeader *next;

    for (;;) {
        draw_segmented_motion_lines(state, position, sprite, 0);
        next = NODE_HEADER(state)->chain_next;
        if (next == 0) {
            return 0;
        }
        state = NODE_BODY(next);
        position = next->position;
        sprite = next->sprite;
    }
}
