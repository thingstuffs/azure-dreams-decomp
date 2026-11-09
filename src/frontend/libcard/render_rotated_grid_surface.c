#include "common.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"
#include "frontend/libcard/message.h"
#include "frontend/libcard_callbacks_api.h"

extern void func_80024EEC(void *object);
extern s32 update_effect_color_rotation_and_motion(void *target); /* Unprototyped: compile_error */
extern void init_card_file_list_panel(CardFileListPanel *panel, s32 selection);



/* Create or reset the shared object and initialize its work area. */
void *render_rotated_grid_surface(s32 parent, s32 context, s32 mode)
{
    ObjectNodeHeader *base;
    CardFileListPanel *work;

    base = card_rotated_grid_object;
    work = NODE_BODY(card_rotated_grid_object);
    if (find_active_list_node(base) == 0) {
        base = initialize_scene_object_in_buffer(0, base, 0x394);
        register_node(base, card_boot_render_panel_hierarchy);
    } else {
        func_80024EEC(base);
        base->flags &= 0x7FFF;
        bzero(work, 0xE30);
    }

    work->selected_slot = context;
    work->mode = mode;
    init_card_file_list_nodes(work, 0x15);
    base->sprite = &work->list_heading;
    work->list_heading.unk_0C = update_effect_color_rotation_and_motion(work->pointers);
    init_card_file_list_panel(work, parent);
    base->update_callback = 0;
    return base;
}
