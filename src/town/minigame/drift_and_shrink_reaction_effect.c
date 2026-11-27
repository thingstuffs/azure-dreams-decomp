#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/object_links.h"
#include "town/minigame.h"
#include "town/minigame/tako_child_body.h"

   /* the 0x2 bytes before arg0 in drift_and_shrink_reaction_effect, addressed as arg0[-1] */


/* Advance effect motion and shrink its scale, marking completion at the threshold. */
void drift_and_shrink_reaction_effect(void *effect_arg, ObjectPosition *motion, SpriteFrameState *transform) {
    TakoHitSparkBody *effect = effect_arg;
    ObjectStatusPrefix16 *effect_view = effect_arg;
    u16 scale;
    TakoChildBody *render_state;

    render_state = effect->target;
    motion->x.v = (s32) (motion->x.v + effect->drift_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    render_state->flags = (u16) (render_state->flags | 1);
    scale = transform->scale_y - 0x100;
    transform->scale_y = scale;
    transform->scale_x = scale;
    if ((u32) (scale & 0xFFFF) < 0x201U) {
        render_state->flags = (u16) (render_state->flags & 0xFFFE);
        effect_view[-1].flags = (u16) (effect_view[-1].flags | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
