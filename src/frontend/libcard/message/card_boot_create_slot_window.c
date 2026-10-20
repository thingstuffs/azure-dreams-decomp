#include "common.h"

extern u8 D_80023EC4[];
extern u8 D_80027DD0[];
extern u8 D_80029618[];

extern s32 find_active_list_node(void *target_node);
extern void *initialize_scene_object_in_buffer(s32 node_flags, void *node_buffer, s32 word_count);
extern void register_node(void *entry, void *registration_id);
extern void func_80024184(void *object);
extern void func_80069EC8(void *destination, s32 byte_count);
extern void func_80023EF4(void *runtime, s32 value);
extern s32 card_boot_link_slot_window_entries(void *value);
extern void card_boot_initialize_slot_window(void *record, s32 setup_value, s32 processing_value);

/* Initialize the indexed object and its runtime state, then return the object. */
void *card_boot_create_slot_window(s32 parent_object, s32 object_index)
{
    u8 *object;
    u8 *runtime;

    object = D_80029618 + object_index * 0x3E4;
    runtime = object + 0x20;
    if (find_active_list_node(object) == 0) {
        object = initialize_scene_object_in_buffer(0, object, 0xF9);
        register_node(object, D_80027DD0);
    } else {
        func_80024184(object);
        *(u16 *)(object + 0x1E) &= 0x7FFF;
        func_80069EC8(runtime, 0x3C4);
    }
    func_80023EF4(runtime, 0xA);
    *(void **)(object + 0xC) = runtime + 0x24C;
    *(s32 *)(runtime + 0x258) = card_boot_link_slot_window_entries(runtime + 0x25C);
    card_boot_initialize_slot_window(runtime, parent_object, object_index);
    *(void **)(object + 0x10) = D_80023EC4;
    return object;
}
