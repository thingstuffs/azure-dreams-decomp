#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "town/scene/effect.h"
#include "town/scene/score_sprite_data.h"
#include "town/data.h"

/* Advance motion and reduce scale, marking the effect complete at the scale threshold. */
void advance_effect_and_reduce_scale(RisingScoreChild *effect, ObjectPosition *motion, SpriteFrameState *scale) {
    u16 *flags;
    u16 next_scale;
    RisingScorePanel *panel;

    panel = effect->panel;
    motion->x.v += effect->step_x;
    motion->y.v += motion->velocity_y;
    panel->flags |= 1;
    next_scale = scale->scale_y - 0x100;
    scale->scale_x = next_scale;
    scale->scale_y = next_scale;
    if (scale->scale_x < 0x201U) {
        panel->flags &= 0xFFFE;
        flags = &NODE_HEADER(effect)->flags;
        *flags |= 0x8000;
        scene_object_flags |= 0x8000;
    }
}
