#include "common.h"

#include "common.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "slus.h"

typedef struct {
    u8 pad[4];
    u8 flag;
} State;

extern s32 object_render_cancel_switch[];

/* Routes state processing according to the global gate and state flag. */
void update_node_registration(void *state, void *context) {
    if (object_render_cancel_switch[0] == 0) {
        if (((State *)state)->flag != 0) {
            register_node_if_unregistered(state, draw_linked_sprites);
            advance_sprite_animation_and_textures(context);
            return;
        }
    }

    unlink_node_if_registered(state);
}
