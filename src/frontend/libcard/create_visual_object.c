#include "common.h"

extern s32 find_active_list_node(void *ptr);
extern void *initialize_scene_object_in_buffer(s32 value, void *ptr1, s32 value2);
extern void register_node(void *entry, void *registration_id);
extern void card_boot_mark_object_complete(void *object);
extern void bzero(void *ptr, s32 size);
extern void func_80026DF0(void *ptr, s32 value);
extern s32 card_boot_link_paired_choice_display_entries(void *nodes);
extern void card_boot_initialize_paired_choice_panel(s8 *record, s32 initial_value);

extern u8 D_8002B850[];
extern u8 D_80027DD0[];
extern u8 D_80026AE4[];

/* Creates or resets the shared object and initializes its data and callbacks. */
void *create_visual_object(s32 init_value, s32 stored_value)
{
    void *object;
    void *data;

    object = D_8002B850;
    data = (u8 *)object + 0x20;
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0x45);
        register_node(object, D_80027DD0);
    } else {
        card_boot_mark_object_complete(object);
        *(u16 *)((u8 *)object + 0x1E) &= 0x7FFF;
        bzero(data, 0xF0);
    }
    func_80026DF0(data, 4);
    *(void **)((u8 *)object + 0xC) = (u8 *)data + 0x50;
    *(s32 *)((u8 *)data + 0x5C) = card_boot_link_paired_choice_display_entries((u8 *)data + 0x60);
    *(s32 *)((u8 *)data + 0x24) = stored_value;
    card_boot_initialize_paired_choice_panel(data, init_value);
    *(void **)((u8 *)object + 0x10) = D_80026AE4;
    return object;
}
