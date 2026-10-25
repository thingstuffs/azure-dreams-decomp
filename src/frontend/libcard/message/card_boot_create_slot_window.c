#include "common.h"
#include "frontend/libcard.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"

extern void func_80024184(void *object);
extern void func_80023EF4(void *runtime, s32 value);
extern s32 card_boot_link_slot_window_entries(void *value);
extern void card_boot_initialize_slot_window(void *record, s32 setup_value, s32 processing_value);

/* Initialize the indexed object and its runtime state, then return the object. */
void *card_boot_create_slot_window(s32 parent_object, s32 object_index)
{
    ObjectNodeHeader *object;
    u8 *runtime;

    object = D_80029618 + object_index * 0x3E4;
    runtime = ((u8 *)object) + 0x20;
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0xF9);
        register_node(object, card_boot_render_panel_hierarchy);
    } else {
        func_80024184(object);
        object->flags &= 0x7FFF;
        bzero(runtime, 0x3C4);
    }
    func_80023EF4(runtime, 0xA);
    object->sprite = runtime + 0x24C;
    *(s32 *)(runtime + 0x258) = card_boot_link_slot_window_entries(runtime + 0x25C);
    card_boot_initialize_slot_window(runtime, parent_object, object_index);
    object->update_callback = D_80023EC4;
    return object;
}
