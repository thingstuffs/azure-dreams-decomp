#include "frontend/libcard.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"

extern void prepare_save_heading_layout(CardHeadingDrawState *work_state, s32 init_value);

extern u8 menu_backdrop_tag[];

/* Creates or resets the shared object and initializes its work state. */
void *create_save_heading(s32 init_value)
{
    ObjectNodeHeader *object;
    CardHeadingDrawState *work_state;

    object = card_save_heading_object;
    work_state = card_save_heading_object + 0x20;
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x68);
        register_node(object, menu_backdrop_tag);
    } else {
        process_nonzero(object);
        object->flags &= 0x7FFF;
        bzero(work_state, 0x180);
    }

    initialize_save_heading_draw_state(work_state, 4);
    object->sprite = work_state->pad_E0;
    work_state->chain = link_save_heading_draw_nodes(work_state->links);
    prepare_save_heading_layout(work_state, init_value);
    return object;
}
