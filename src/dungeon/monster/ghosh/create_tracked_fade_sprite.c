#include "shared/entity.h"
#include "engine/graphics.h"
#include "common.h"
#include "dungeon/monster/ghosh/tracked_fade.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node/allocation.h"
#include "dungeon/monster/ghosh.h"
#include "engine/node.h"

typedef struct S_80172A14_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80172A14_0;   /* arg0 in create_tracked_fade_sprite */


   /* arg1 in create_tracked_fade_sprite */

extern u8 D_80172874[];
extern u8 D_80174ABC[];

/* Create an effect linked to its owner and initialize its position and rendering. */
/* Creates a black Ghosh effect at the supplied position and links its owner and source position for later
 * updates. */
void create_tracked_fade_sprite(void *owner, MovingPosition *source_pos, void *unused) {
    SpriteFrameState *render_flags;
    ObjectNodeHeader *effect;
    GhoshTrackedFadeBody *effect_state;
    ObjectPosition *effect_pos;

    effect = allocate_list_node(0x12, &((ObjectNodeHeader *)owner - 1)->next);
    if (effect != 0) {
        ((S_80172A14_0 *)owner)->unk_AC = effect;
        effect->update_callback = D_80172874;
        register_node(effect, draw_linked_sprites_clipped);
        effect_state = NODE_BODY(effect);
        effect_state->phase_duration = 5;
        effect_state->owner = owner;
        effect_state->source_position = source_pos;
        render_flags = effect->sprite;
        render_flags->tpage_abr = 0x40;
        render_flags->flags |= 0xC;
        effect_pos = effect->position;
        effect_pos->x.w.i = source_pos->x;
        effect_pos->y.w.i = source_pos->y;
        effect_pos->z.w.i = source_pos->z;
        render_flags = effect->sprite;
        render_flags->scale_y = 0xA00;
        render_flags->scale_x = 0xA00;
        render_flags->color.c.b = 0;
        render_flags->color.c.g = 0;
        render_flags->color.c.r = 0;
        render_flags->source = D_80174ABC;
    }
}
