#include "common.h"

extern s32 runtime_find_unused_pool_slot(void);
extern void runtime_initialize_state_value(s32, s32);
extern void runtime_clear_value(s32);
extern s32 func_8003FC64(s32);
extern void unlink_active_node(s32);
extern void push_node_onto_free_list(s32);
extern void initialize_town_map_object_state(s32, s32, s32, s32);
extern s8 D_800CFC2C[11];
extern u8 town_map_status;

s32 town_map_set(s32 value_7c, s32 value_78)
{
    s32 objects[12];
    s32 resources[12];
    s32 index = 0;
    s32 *object_slot = objects;
    s32 *resource_slot = resources;
    s32 *array_start;
    s32 new_object;
    s32 new_resource;
    s32 link_index;
    s32 linked_data;
    s8 *object_data;

    do {
        new_object = func_8003FC64(0x11);
        if (new_object == 0) {
            break;
        }
        new_resource = runtime_find_unused_pool_slot();
        if (new_resource == 0) {
            break;
        }
        runtime_initialize_state_value(new_resource, 0);
        *object_slot++ = new_object;
        *resource_slot++ = new_resource;
        index++;
    } while (index < 11);

    if (index < 11) {
        if (object_slot != objects) {
            array_start = objects;
            do {
                object_slot--;
                unlink_active_node(*object_slot);
                push_node_onto_free_list(*object_slot);
            } while (object_slot != array_start);
        }
        if (resource_slot != resources) {
            array_start = resources;
            do {
                resource_slot--;
                runtime_clear_value(*resource_slot);
            } while (resource_slot != array_start);
        }
        return 0;
    }

    object_slot = objects;
    resource_slot = resources;
    index = 0;
    do {
        link_index = D_800CFC2C[index];
        if (link_index == index) {
            linked_data = 0;
        } else {
            linked_data = objects[link_index] + 0x20;
        }
        object_data = (s8 *)(*object_slot + 0x20);
        *(s32 *)(object_data + 0x74) = 0;
        *(s32 *)(object_data + 0x78) = value_78;
        *(s32 *)(object_data + 0x7C) = value_7c;
        initialize_town_map_object_state(index, linked_data, *object_slot++, *resource_slot++);
        index++;
    } while (index < 11);
    town_map_status = 0;
    return 1;
}
