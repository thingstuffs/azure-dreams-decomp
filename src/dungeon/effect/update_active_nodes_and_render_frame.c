#include "common.h"

typedef struct {
    u8 before_flags[0x1C];
    u32 flags;
} DungeonControl;
extern s32 D_800814A0;
extern u8 D_80080A86;
extern u16 D_80013714;
extern u8 D_80083160[];
extern DungeonControl *D_800814A8;
extern void run_active_node_callbacks(void);
extern void remove_marked_active_nodes(void);
extern void integrate_active_node_vectors(void);
extern void run_view_callbacks(void);
extern void process_current_facing_directions(void);
extern void render_map_cell_mesh(void);
extern void dispatch_object_renderers(void);
extern void append_draw_mode_primitive(void);
extern void queue_framebuffer_strip_quads(void);

void update_active_nodes_and_render_frame(void) {
    u8 *work = D_80083160;
    run_active_node_callbacks();
    if (D_800814A0 & 0x8000) {
        remove_marked_active_nodes();
    }
    D_800814A0 = 0;
    if (D_80080A86 == 0) {
        integrate_active_node_vectors();
        if (D_80013714 & 2) {
            return;
        }
        if (*(s32 *)(work + 0x1DC) != 0) {
            run_view_callbacks();
            process_current_facing_directions();
            if (!(D_800814A8->flags & 0x10)) {
                render_map_cell_mesh();
            }
        }
    }
    dispatch_object_renderers();
    append_draw_mode_primitive();
    queue_framebuffer_strip_quads();
}
