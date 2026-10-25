#include "dungeon/monster/ghosh.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

typedef union GhoshFadeNode {
    GhoshTrailFade *body;
    ObjectNodeHeader *node;
} GhoshFadeNode;

/* Raise the trail by two units and remove it when its color fade ends. */
void advance_ghosh_trail_fade(GhoshTrailFade *fade, ObjectPosition *position) {
    s16 steps_left;
    GhoshFadeNode view;

    position->z.v += 0x20000;
    fade->scaled.rgb.r = (fade->r * fade->steps.s) / fade->divisor;
    fade->scaled.rgb.g = (fade->g * fade->steps.s) / fade->divisor;
    fade->scaled.rgb.b = (fade->b * fade->steps.s) / fade->divisor;
    steps_left = fade->steps.u - 1;
    fade->steps.s = steps_left;
    fade->color = fade->scaled.word;
    if ((steps_left << 16) <= 0) {
        view.body = fade;
        view.node[-1].flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
