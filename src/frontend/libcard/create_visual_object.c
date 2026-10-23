
struct ObjectNodeHeader;
#include "common.h"
#include "shared/object_node.h"
#include "engine/node.h"
#include "engine/scene.h"
#include "main/data.h"
#include "sdk/libc.h"
#include "slus.h"

extern void card_boot_mark_object_complete(struct ObjectNodeHeader *object);
extern void func_80026DF0(void *ptr, s32 value);
extern s32 card_boot_link_paired_choice_display_entries(void *nodes);
extern void card_boot_initialize_paired_choice_panel(s8 *record, s32 initial_value);

extern u8 menu_backdrop_tag[];

/* Creates or resets the shared object and initializes its data and callbacks. */
void *create_visual_object(s32 init_value, s32 stored_value)
{
    ObjectNodeHeader *object;
    void *data;

    object = D_8002B850;
    data = (u8 *)object + 0x20;
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x45);
        register_node(object, menu_backdrop_tag);
    } else {
        card_boot_mark_object_complete(object);
        object->flags &= 0x7FFF;
        bzero(data, 0xF0);
    }
    func_80026DF0(data, 4);
    object->sprite = (u8 *)data + 0x50;
    *(s32 *)((u8 *)data + 0x5C) = card_boot_link_paired_choice_display_entries((u8 *)data + 0x60);
    *(s32 *)((u8 *)data + 0x24) = stored_value;
    card_boot_initialize_paired_choice_panel(data, init_value);
    object->update_callback = D_80026AE4;
    return object;
}
