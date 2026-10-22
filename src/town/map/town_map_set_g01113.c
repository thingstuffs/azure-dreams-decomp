/* Town map set.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01113 - CL:town/func_8008E0B8.
 */
#include "town/map/town_map_set_g01113.h"

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
        new_object = allocate_flagged_object_node(0x11);
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
    (*((u8 *)town_map_status)) = 0;
    return 1;
}

/* town_map_del: flag the town map for deletion and return success. */
s32 town_map_del(void) {
    (*((u8 *)town_map_status)) = 0xFF;
    return 1;
}

/* Clears D_800FC418 and returns success. */
s32 clear_town_map_status(void) {
    (*((s8 *)town_map_status)) = 0;
    return 1;
}

/* Initializes a town object and its state for the selected type. */
void initialize_town_map_object_state(s32 type_id, s32 *init_value_ptr, void *object, void *context)
{
    s32 type_data;
    s32 init_value;
    void *state;
    SpriteFrameState *render_data;
    void *transform;
    s32 *type_table;
    s32 *value_table_base;
    s32 *value_table;
    s32 *type_entry;
    *((s32 **) (((s8 *) object) + 0x10)) = &D_8008B9D8;
    register_node(object, &town_map_tag);
    init_value = 0;
    transform = *((void **) (((s8 *) object) + 8));
    render_data = *((void **) (((s8 *) object) + 0xC));
    state = object + 0x20;
    if (init_value_ptr != 0) {
        init_value = *init_value_ptr;
    }
    runtime_initialize_state_value(context, init_value);
    {
        s32 context_mode;
        context_mode = 2;
        type_table = D_800CFB74;
        *((void **) (((s8 *) object) + 0x20)) = context;
        *((s32 *) (((s8 *) context) + 0x60)) = context_mode;
    }
    *((s32 *) (((s8 *) state) + 4)) = 0;
    *((s16 *) (((s8 *) state) + 0x66)) = type_id;
    type_entry = type_table - (-type_id);
    type_data = *type_entry;
    if (type_data != 0) {
        *((s32 **) (((s8 *) state) + 8)) = &D_80037714;
        copy_window_params(state, (struct Source *)(type_data));
    }
    else {
        *((s32 **) (((s8 *) state) + 8)) = 0;
    }
    *((s16 *) (((s8 *) state) + 0x60)) = 0;
    render_data->color.word = 0x808080;
    if (((u32) (type_id - 9)) < 2U) {
        select_record_entry_and_value(render_data, &D_800794AC, 0);
    }
    else {
        render_data->source = 0;
    }
    if (type_id == 0) {
        *((s16 *) (((s8 *) transform) + 2)) = 0x20;
        *((s16 *) (((s8 *) transform) + 6)) = -0x20;
        *((s16 *) (((s8 *) transform) + 0xA)) = 0x200;
    }
    if (type_id == 0xA) {
        *((s32 *) (((s8 *) state) + 0x74)) = 0;
        town_map_selection = (s32) (*(*((u8 **) (((s8 *) state) + 0x7C))));
    }
    *((s32 **) (((s8 *) state) + 0x68)) = &D_8008BA00;
    value_table_base = D_800CFC44;
    value_table = value_table_base;
    *((s16 *) (((s8 *) state) + 0x64)) = (s16) ((s8) D_800CFC38[type_id]);
    *((s32 *) (((s8 *) state) + 0x6C)) = value_table[type_id];
    if (type_id == 9) {
        unlink_node_if_registered(state);
    }
}
