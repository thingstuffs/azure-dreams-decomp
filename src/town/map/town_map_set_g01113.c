#include "shared/object_node.h"

struct ObjectNodeHeader;
/* Town map set.
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_8008E0B8.
 */
#include "town/map/town_map_set_g01113.h"
#include "town/map.h"
#include "engine/window.h"

/* Allocates and links eleven town map objects; returns 0 if allocation fails and 1 after setup. */
s32 town_map_set(s32 value_7c, s32 value_78)
{
    s32 objects[12];
    s32 resources[12];
    s32 index = 0;
    s32 *object_slot = objects;
    s32 *resource_slot = resources;
    s32 *array_start;
    void *new_object;
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
                push_node_onto_free_list((struct ObjectNodeHeader *)*object_slot);
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
        link_index = town_map_link_slots[index];
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
    (*town_map_status) = 0;
    return 1;
}

/* town_map_del: flag the town map for deletion and return success. */
s32 town_map_del(void) {
    (*town_map_status) = 0xFF;
    return 1;
}

/* Clears the town map status byte and returns one. */
s32 clear_town_map_status(void) {
    (*((s8 *)town_map_status)) = 0;
    return 1;
}

/* Initializes a town object and its state for the selected type. */
void initialize_town_map_object_state(s32 type_id, s32 *init_value_ptr, ObjectNodeHeader *object, Rec_D_80081FDC *context)
{
    s32 type_data;
    s32 init_value;
    TownMapBody *state;
    SpriteFrameState *render_data;
    ObjectPosition *transform;
    s32 *type_table;
    s32 *value_table_base;
    s32 *value_table;
    s32 *type_entry;
    object->update_callback = run_map_object_callback;
    register_node(object, &town_map_tag);
    init_value = 0;
    transform = object->position;
    render_data = object->sprite;
    state = (TownMapBody *)(object + 1);
    if (init_value_ptr != 0) {
        init_value = *init_value_ptr;
    }
    runtime_initialize_state_value(context, init_value);
    {
        s32 context_mode;
        context_mode = 2;
        type_table = D_800CFB74;
        ((TownMapBody *)(object + 1))->context = context;
        context->unk_60 = context_mode;
    }
    state->unk_04 = 0;
    state->type_id = type_id;
    type_entry = type_table - (-type_id);
    type_data = *type_entry;
    if (type_data != 0) {
        state->window_callback = &D_80037714;
        copy_window_params((struct Container *)state, (struct Source *)(type_data));
    }
    else {
        state->window_callback = 0;
    }
    state->unk_60 = 0;
    render_data->color.word = 0x808080;
    if (((u32) (type_id - 9)) < 2U) {
        select_record_entry_and_value(render_data, &D_800794AC, 0);
    }
    else {
        render_data->source = 0;
    }
    if (type_id == 0) {
        transform->x.w.i = 0x20;
        transform->y.w.i = -0x20;
        transform->z.w.i = 0x200;
    }
    if (type_id == 0xA) {
        state->selection = 0;
        town_map_selection = (s32) (*state->entries);
    }
    state->update = advance_town_map_countdown_callback;
    value_table_base = D_800CFC44;
    value_table = value_table_base;
    state->timer.as_s16 = (s16) ((s8) D_800CFC38[type_id]);
    *((s32 *) (((s8 *) state) + 0x6C)) = value_table[type_id];
    if (type_id == 9) {
        unlink_node_if_registered(state);
    }
}
