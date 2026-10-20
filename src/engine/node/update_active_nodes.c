#include "common.h"
#include "shared/game_work.h"

#include "common.h"

extern u8 D_80080A86;

extern s32 D_800814A0;



extern void build_screen_outline(void *a0, void *a1, s32 a2);
extern void func_8003BFE4(void);
extern void run_active_node_callbacks(void);
extern void remove_marked_active_nodes(void);
extern void integrate_active_node_vectors(void);
extern void run_view_callbacks(void);
extern void refresh_state_and_dispatch_angles(void);
extern void render_shaded_map_tiles(void);
extern void dispatch_registered_draw_callbacks(void);
extern void append_draw_mode_primitive(void);

/* Runs node callbacks, removes flagged nodes, and updates movement and drawing state. */
void update_active_nodes(void)
{
    GameWork *state = ((GameWork *)&g_game_work);
    s32 mode;
    if ((D_80080A86 == 0) && (state->map.cells != 0)) {
        build_screen_outline(&state->view, &state->view.unk_008, 0);
        func_8003BFE4();
    }
    run_active_node_callbacks();
    if (D_800814A0 & 0x8000) {
        remove_marked_active_nodes();
    }
    mode = D_80080A86;
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
