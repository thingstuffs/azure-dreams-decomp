#include "common.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/camera.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "engine/scene.h"

extern u8 node_update_mode;

extern s32 D_800814A0;

extern void refresh_state_and_dispatch_angles(void);
extern void render_shaded_map_tiles(void);

/* Runs node callbacks, removes flagged nodes, and updates movement and drawing state. */
void update_active_nodes(void)
{
    GameWork *state = ((GameWork *)&g_game_work);
    s32 mode;
    if ((node_update_mode == 0) && (state->map.cells != 0)) {
        build_screen_outline(&state->view, &state->view.outline_0_x, 0);
        copy_and_scale_screen_outline_points();
    }
    run_active_node_callbacks();
    if (D_800814A0 & 0x8000) {
        remove_marked_active_nodes();
    }
    mode = node_update_mode;
    D_800814A0 = 0;
    if (mode == 0) {
        integrate_active_node_vectors();
        run_view_callbacks();
        if (state->map.cells != 0) {
            refresh_state_and_dispatch_angles();
            render_shaded_map_tiles();
        }
    }
    dispatch_registered_draw_callbacks();
    append_draw_mode_primitive();
}
