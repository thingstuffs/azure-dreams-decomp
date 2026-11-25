#include "frontend/libcard/slot_list.h"
#include "common.h"
#include "frontend/libcard.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"
#include "frontend/libcard/message.h"

extern void func_80024184(void *object);

/* Initialize the indexed object and its runtime state, then return the object. */
struct ObjectNodeHeader *card_boot_create_slot_window(struct ObjectNodeHeader *parent_object, s32 object_index)
{
    ObjectNodeHeader *object;
    CardSlotWindow *runtime;

    object = D_80029618 + object_index * 0x3E4;
    runtime = NODE_BODY(object);
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0xF9);
        register_node(object, card_boot_render_panel_hierarchy);
    } else {
        func_80024184(object);
        object->flags &= 0x7FFF;
        bzero(runtime, 0x3C4);
    }
    init_card_slot_list_nodes(runtime, 0xA);
    object->sprite = &runtime->frame;
    /* The display frame stores the chain head in an address word. */
    runtime->frame.unk_0C = (s32)(unsigned long)card_boot_link_slot_window_entries(
        (struct S_800491F4 **)runtime->pointers);
    card_boot_initialize_slot_window(runtime, parent_object, object_index);
    object->update_callback = card_boot_stop_slot_window_updates;
    return object;
}
