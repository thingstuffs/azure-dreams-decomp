#include "engine/menu/animated_panel.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/object_flags.h"

#include "engine/node.h"
#include "engine/window.h"
#include "engine/graphics.h"
#include "engine/resource.h"
#include "slus/data.h"

/* Allocate and initialize an entity with a resource buffer and position targets. */
AnimatedMenuPanelNode *window_create_animated_content_panel(s32 style_flags, s16 start_x, s16 start_y, s16 target_x,
                                 s16 target_y, s16 width, s32 flags, s32 content_id) {
    AnimatedMenuPanelNode *entity;
    AnimatedMenuPanelBody *state;
    void *buffer_addr;
    void *display_link;
    s32 saved_style_flags = style_flags;
    u16 entity_flags;
    s32 global_flags;
    s32 *global_page;

    entity = allocate_flagged_object_node(0);
    if (entity != 0) {
        state = &entity->body;
        buffer_addr = create_callback_pair_default(0);
        state->template_buffer = buffer_addr;
        if (buffer_addr != 0) {
            state->flags = (u16)flags;
            state->target_x = (s16)(target_x - 0xA0);
            state->target_y = (s16)(target_y - 0x80);
            init_menu_panel(state, saved_style_flags, content_id, (s16)start_x,
                          (s16)start_y,
                          (s16)width);
            display_link = &state->elements[0].link;
            entity->header.sprite = display_link;
            register_node(entity, draw_tinted_node_sprites_scratch);
            entity->header.update_callback = menu_move_the_position_halfway_toward_target_position;
        } else {
            entity_flags = entity->header.flags;
            entity->header.flags = entity_flags | 0x8000;
            global_flags = D_800814A0_load[0];
            entity = 0;
            global_flags |= 0x8000;
            global_page = (s32 *)0x80080000;
            global_page[0x528] = global_flags;
        }
    }
    return entity;
}
