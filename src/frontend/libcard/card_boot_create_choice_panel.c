
struct ObjectNodeHeader;
#include "common.h"
#include "frontend/libcard/message.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"
#include "frontend/libcard.h"



/* Creates or resets the shared object and initializes its data and callbacks. */
void *card_boot_create_choice_panel(s32 init_value, s32 stored_value)
{
    ObjectNodeHeader *object;
    void *data;

    object = D_8002B850;
    data = NODE_BODY(object);
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x45);
        register_node(object, card_boot_render_panel_hierarchy);
    } else {
        card_boot_mark_object_complete(object);
        object->flags &= 0x7FFF;
        bzero(data, 0xF0);
    }
    init_card_choice_nodes(data, 4);
    object->sprite = (u8 *)data + 0x50;
    *(void **)((u8 *)data + 0x5C) = card_boot_link_choice_panel_nodes((u8 *)data + 0x60);
    *(s32 *)((u8 *)data + 0x24) = stored_value;
    card_boot_initialize_paired_choice_panel(data, init_value);
    object->update_callback = advance_card_boot_stream_pair;
    return object;
}
