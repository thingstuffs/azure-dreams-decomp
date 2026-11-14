#include "common.h"

#include "engine/graphics.h"
#include "engine/effect/fade_manager.h"
#include "engine/node.h"
#include "slus.h"

extern s32 object_render_cancel_switch[];

/* Routes state processing according to the global gate and state flag. */
void update_fade_draw_registration(FadeManagerBody *state, void *context) {
    if (object_render_cancel_switch[0] == 0) {
        if ((u8)state->has_source != 0) {
            register_node_if_unregistered(state, draw_linked_sprites);
            advance_sprite_animation_and_textures(context);
            return;
        }
    }

    unlink_node_if_registered(state);
}
