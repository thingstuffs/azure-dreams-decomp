/* Builds town display entries, checks their bounds, dispatches object updates, and opens menu windows. */
#include "shared/entity.h"
#include "shared/object_node.h"
#include "town/menu/window.h"
#include "town/scene/object.h"
#include "town/scene/effect.h"
#include "town/scene/resource.h"
#include "shared/object_flags.h"
#include "shared/sprite_frame_state.h"


/* Initializes an object with default transform and global state values. */
void initialize_object_transform_and_state(s32 slot_id, void *object, s32 object_id)
{

    *(s16 *)((u8 *)object + 0x20) = 0x1000;
    *(s16 *)((u8 *)object + 0x1E) = 0x1000;
    *(s16 *)((u8 *)object + 0x1C) = 0x1000;
    *(s16 *)((u8 *)object + 0x12) = 0;
    *(s16 *)((u8 *)object + 0x14) = 0;
    *(s16 *)((u8 *)object + 0x10) = 0;
    *(u8 *)((u8 *)object + 0xC) = g_game_work.view.tint.parts.tint_r;
    *(u8 *)((u8 *)object + 0xD) = g_game_work.view.tint.parts.tint_g;
    *(u8 *)((u8 *)object + 0xE) = g_game_work.view.tint.parts.tint_b;
    *(s16 *)((u8 *)object + 0x14) = 0;
    *(s16 *)((u8 *)object + 0x1A) = 0;
    *(s16 *)((u8 *)object + 0x18) = 0;
    *(s16 *)((u8 *)object + 0x16) = 0;
    *(s32 *)((u8 *)object + 0) = 0;
    *(s8 *)((u8 *)object + 4) = 0;
    *(s8 *)((u8 *)object + 5) = 0;
    register_node(slot_id - 0x20, lit_mesh_renderer_address);
    *(s32 *)((u8 *)object + 8) = object_id;
}

/* Initializes the shared data pointer, clears its first word and returns it. */
s32 *initialize_shared_script_data(void) {
    town_script_slot_cursor = town_script_state_slots;
    town_script_state_slots[0] = 0;
    return town_script_state_slots;
}

/* Scale a coordinate pair by 64 and append it to the null-terminated pointer list. */
void **scale_coordinates_and_append_pointers(s32 firstX, s32 firstY, s32 secondX, s32 secondY,
                     func_8009F66C_CoordPair *coords)
{
    if (coords != NULL) {
        void **cursor = town_script_slot_cursor;

        coords->x0 = (s16)((s32)(firstX << 16) >> 10);
        coords->y0 = (s16)((s32)(firstY << 16) >> 10);
        coords->x1 = (s16)((s32)(secondX << 16) >> 10);
        coords->y1 = (s16)((s32)(secondY << 16) >> 10);
        *cursor = coords;
        cursor++;
        town_script_slot_cursor = cursor;
        *cursor = NULL;
    }
    return town_script_slot_cursor;
}

/* Create a record, assign its handler, and run the remaining initialization routines. */
void create_entry_builder_controller(void) {
    ((func_8009F6D4_S_8009CE34_0 *)(initialize_scene_object_in_buffer(0x11, &D_801006D0, 0x49)))->unk_10 = &build_entries_and_update_state;
    dispatch_parameterized_or_default(&town_script_state_slots);
    update_map_world_extents();
}

/* Runs build_entry_list_and_process_items followed by run_dual_context_callbacks. */
void build_entries_and_update_state(void) {
    build_entry_list_and_process_items();
    run_dual_context_callbacks();
}

/* Run both update routines on the shared state and clear the global flag. */
void update_shared_state_and_clear_flag(void) {
    void *state = town_script_state_slots;

    init_and_publish_script_state(state);
    process_zero_terminated_entry_lists(state);
    town_overlap_slots[0] = 0;
}

/* Builds the entry list and processes each entry's items at its coordinates. */
void build_entry_list_and_process_items(void) {
    s32 setup_a[2];
    s32 setup_b[2];
    s32 *item_cursor;
    s32 coord_x;
    s32 coord_y;
    void **entry_cursor;
    func_8009F788_S_8009CEE8_0 *entry;
    u16 *base;

    base = scaled_window_quad_points;
    compute_four_point_coordinate_bounds(base, setup_a, setup_b);
    collect_overlapping_rectangles(setup_a, setup_b, town_script_state_slots, town_overlap_slots);
    entry_cursor = (void **)town_overlap_slots;
    if (town_overlap_slots[0] != 0) {
        do {
            entry = *entry_cursor;
            item_cursor = entry->unk_0C;
            if (item_cursor != NULL) {
                coord_x = entry->unk_00;
                coord_y = entry->unk_02;
                while (*item_cursor != 0) {
                    process_eligible_entries(*item_cursor, base, (s16)coord_x, (s16)coord_y);
                    item_cursor++;
                }
            }
            entry_cursor = (void **)((s8 *)((void **)((s8 *)entry_cursor + 4)));
        } while (*entry_cursor != NULL);
    }
}

/* Classify an object using its state and two positions relative to the geometry bounds. */
s32 classify_object_against_bounds(func_8009F880_S_8009CFE0_0 *object, void *position_data)
{
    func_8009F880_S_8009CFE0_2 *position = position_data;
    s32 result;
    s32 one;
    s32 geometry_result;
    s32 state_result;
    func_8009F880_S_8009CFE0_1 *state;

    state = object->unk_98;
    if (state != NULL) {
        if (!(state->unk_01 & 1)) {
            if (test_resident_bitmap_bit(state->unk_02) == 0) {
                return 1;
            }
        } else {
            state_result = test_resident_bitmap_bit(state->unk_02);
            one = 1;
            if (state_result == one) {
                result = 1;
                return result;
            }
        }
        if (state->unk_01 & 0x10) {
            result = 0;
            return result;
        }
        if (map_scene_selector_alias == 0xC) {
            result = 0;
            return result;
        }
    }
    if (check_four_vector_half_turn_gaps(
            (s16)(scaled_window_quad_points[0] - position->unk_02),
            (s16)(scaled_window_quad_points[1] - position->unk_06),
            (s16)(scaled_window_quad_points[4] - position->unk_02),
            (s16)(scaled_window_quad_points[5] - position->unk_06),
            (s32)(s16)(scaled_window_quad_points[8] - position->unk_02),
            (s32)(s16)(scaled_window_quad_points[9] - position->unk_06),
            (s32)(s16)(scaled_window_quad_points[0xC] - position->unk_02),
            (s32)(s16)(scaled_window_quad_points[0xD] - position->unk_06)) == 0) {
        geometry_result = check_four_vector_half_turn_gaps(
            (s16)(scaled_window_quad_points[0] - object->unk_84),
            (s16)(scaled_window_quad_points[1] - object->unk_86),
            (s16)(scaled_window_quad_points[4] - object->unk_84),
            (s16)(scaled_window_quad_points[5] - object->unk_86),
            (s32)(s16)(scaled_window_quad_points[8] - object->unk_84),
            (s32)(s16)(scaled_window_quad_points[9] - object->unk_86),
            (s32)(s16)(scaled_window_quad_points[0xC] - object->unk_84),
            (s32)(s16)(scaled_window_quad_points[0xD] - object->unk_86));
        result = 2;
        if (geometry_result == 0) {
            return result;
        }
    }
    result = 0;
    return result;
}

/* Classifies a record using its attached state and two position tests. */
s32 classify_record_by_state_and_position(Rec_D_80082D58 *record, void *position_data)
{
    func_8009FAAC_S_8009D20C_2 *position = position_data;
    s32 result;
    s32 one;
    s32 geom_result;
    s32 state_result;
    func_8009FAAC_S_8009D20C_1 *state;

    state = record->unk_98.as_pv;
    if (state != NULL) {
        if (!(state->unk_01 & 1)) {
            if (test_resident_bitmap_bit(state->unk_02) == 0) {
                return 1;
            }
        } else {
            state_result = test_resident_bitmap_bit(state->unk_02);
            one = 1;
            if (state_result == one) {
                result = 1;
                return result;
            }
        }
        if (state->unk_01 & 0x10) {
            result = 0;
            return result;
        }
    }
    if (check_four_vector_half_turn_gaps(
        (s16)(scaled_window_quad_points[0] - position->unk_02), (s16)(scaled_window_quad_points[1] - position->unk_06),
        (s16)(scaled_window_quad_points[4] - position->unk_02), (s16)(scaled_window_quad_points[5] - position->unk_06),
        (s32)(s16)(scaled_window_quad_points[8] - position->unk_02), (s32)(s16)(scaled_window_quad_points[9] - position->unk_06),
        (s32)(s16)(scaled_window_quad_points[0xC] - position->unk_02), (s32)(s16)(scaled_window_quad_points[0xD] - position->unk_06)) == 0) {
        geom_result = check_four_vector_half_turn_gaps(
            (s16)(scaled_window_quad_points[0] - record->unk_84), (s16)(scaled_window_quad_points[1] - record->unk_86),
            (s16)(scaled_window_quad_points[4] - record->unk_84), (s16)(scaled_window_quad_points[5] - record->unk_86),
            (s32)(s16)(scaled_window_quad_points[8] - record->unk_84), (s32)(s16)(scaled_window_quad_points[9] - record->unk_86),
            (s32)(s16)(scaled_window_quad_points[0xC] - record->unk_84), (s32)(s16)(scaled_window_quad_points[0xD] - record->unk_86));
        result = 2;
        if (geom_result == 0) {
            return result;
        }
    }
    result = 0;
    return result;
}

/* Create an object, initialize its position and render state, and invoke its callback. */
s32 create_object_and_initialize_render_state(s32 callback_id, s32 angle_index, s32 state_94, u8 state_95, u8 state_96, u8 height_mode, s32 state_48, s16 coord_x, s16 coord_z, s32 state_98)
{
    TownObjectCallbackEntry initializer;
    s32 saved_angle_index;
    ObjectNodeHeader *object;
    ObjectPosition *position;
    void *object_state;
    SpriteFrameState *render_data;
    u16 angle;
    void *state;
    u32 color;
    void *callback_render;
    s32 saved_state_48;
    s32 saved_state_98;
    s32 saved_state_94;

    saved_angle_index = angle_index;
    saved_state_94 = state_94;
    object = allocate_list_node(0x136, ((u8 *)(&scene_object_list_anchor)));
    if (object == 0) {
        return 0;
    }
    if ((callback_id & 0xC0000000) == 0xC0000000) {
        initializer.callback = town_object_callbacks[(u16)callback_id];
        object->update_callback = initializer.address;
    }
    if ((callback_id & 0xC0000000) != 0xC0000000) {
        object->update_callback = callback_id;
    }

    if (callback_id & 1) {
        position = object->position;
        render_data = object->sprite;
    }
    else if (callback_id & 2) {
        position = object->position;
        render_data = object->sprite;
    }
    else if (callback_id & 4) {
        position = object->position;
        render_data = object->sprite;
    }
    else {
        position = object->position;
        render_data = object->sprite;
    }

    position->x.w.i = coord_x;
    object_state = (u8 *)object + 0x20;
    position->y.w.i = coord_z;

    if (height_mode == 0) {
        position->z.w.i = -0x40;
    } else {
        position->z.w.i = -0xC0;
    }
    position->z.w.i = query_lowered_transform_position(position);
    if (position != 0) {
        color = 0x808080;
    }
    else {
        color = 0x808080;
    }
    ((func_8009FCC4_S_8009D424_2 *)object_state)->unk_84 = *(u16 *)&position->x.w.i;
    if (position != 0) {
        if (render_data != 0) {
            state = object_state;
        }
        else {
            state = object_state;
        }
    } else {
        if (render_data != 0) {
            state = object_state;
        }
        else {
            state = object_state;
        }
    }
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_86 = *(u16 *)&position->y.w.i;
    render_data->scale_y = 0x1000;
    render_data->scale_x = 0x1000;
    render_data->color.word = color;
    angle = town_facing_angles[saved_angle_index & 3];
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_94 = saved_state_94;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_95 = state_95;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_96 = state_96;
    if (position != 0) {
        if (render_data != 0) {
            saved_state_48 = state_48;
        }
        else {
            saved_state_48 = state_48;
        }
    } else {
        saved_state_48 = state_48;
    }
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_48 = saved_state_48;
    if (position != 0) {
        if (render_data != 0) {
            saved_state_98 = state_98;
        }
        else {
            saved_state_98 = state_98;
        }
    } else {
        saved_state_98 = state_98;
    }
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_93 = 0;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_70 = 0;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_71 = 0;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_72 = angle;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_6E = angle;
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_98 = saved_state_98;
    if (position != 0) {
        if (render_data != 0) {
            callback_render = render_data;
        }
        else {
            callback_render = render_data;
        }
    } else {
        callback_render = render_data;
    }
    ((func_8009FCC4_Callback)*(u32 *)&object->update_callback)(state, position, callback_render);
    return 1;
}

/* Sets up town state and runs initialization and list callbacks. */
void init_and_publish_script_state(void **entries) {
    s16 mode;
    void **entry_cursor;
    u8 *state_buffer;
    u8 *system_work;
    u8 *init_object;
    func_8009FE60_TownState *town_state;
    func_8009FE60_TownState *state;
    func_8009FE60_InitCallback init_callback;
    func_8009FE60_ListCallback entry_callback;
    void *entry;

    entry_cursor = entries;
    town_state = &town_resource_context;
    mode = map_runtime_state.field18;
    town_state->field4 = (mode == 12);
    if (mode == 12) {
        town_state->field8 = map_runtime_state.field1A;
    } else {
        town_state->field8 = 0;
    }
    if (optional_resource_descriptor[0] != 0) {
        state_buffer = D_80082A80;
        system_work = state_buffer - 0x48;
        state = &town_resource_context;
        state->field1C = state_buffer;
        state->field20 = D_800D3CC8;
        state->field24 = D_800D401C;
        state->field30 = D_800D381C;
        state->field38 = (void *)0x80010000;
        state->field18 = (void *)0x80012D70;
        state->field40 = (void *)0x80013188;
        state->field3C = town_building_slot_rectangles;
        TOWN_SYSTEM_SCRATCH->state = (void *)state;
        runtime_set_record_value_and_buffer(system_work, (void *)TOWN_SYSTEM_SCRATCH->payload);
        *(s32 *)(system_work + 0x84) = 0;
        init_object = window_node_list_storage;
        init_callback = *(func_8009FE60_InitCallback *)(init_object + 0x10);
        init_callback(init_object + 0x20, 0, 0);
        reset_resource_entry(0);
        ensure_packed_resource_list(state->field34);
    }
    while ((entry = *entry_cursor) != 0) {
        entry_callback = *(func_8009FE60_ListCallback *)((u8 *)entry + 0x10);
        if (entry_callback != 0)
            entry_callback();
        entry_cursor++;
    }
    runtime_set_record_value_and_buffer(runtime_script_state, *(void **)((u8 *)runtime_script_state + 0x88));
}

/* Process each zero-terminated value list in the null-terminated entry array. */
void process_zero_terminated_entry_lists(void **entries) {
    s32 *value_ptr;
    s32 value;
    void **entry_ptr;

    entry_ptr = entries;
    if (*entry_ptr != NULL) {
        do {
            value_ptr = ((func_8009FFDC_S_8009D73C_0 *)(*entry_ptr))->unk_0C;
            if ((value_ptr != NULL) && (*value_ptr != 0)) {
                do {
                    value = *value_ptr;
                    value_ptr += 1;
                    clear_record_20_status_bytes(value);
                } while (*value_ptr != 0);
            }
            entry_ptr = (void **)((s8 *)((void **)((s8 *)entry_ptr + 4)));
        } while (*entry_ptr != NULL);
    }
}

/* Clear each record's first byte until the end marker is reached. */
void clear_record_20_status_bytes(s8 *records) {
    s8 *record;

    record = records;
    if ((((func_800A0070_S_8009D7D0_0 *)record)->unk_01 & 0xC0) != 0x80) {
        do {
            *record = 0;
            record += 0x14;
        } while ((((func_800A0070_S_8009D7D0_0 *)record)->unk_01 & 0xC0) != 0x80);
    }
}

/* Compute coordinate bounds for four points using the configured limits. */
void compute_four_point_coordinate_bounds(void *points, func_800A00A8_S_8009D808_2 *max_point, func_800A00A8_S_8009D808_1 *min_point) {
    s16 x_for_max;
    s16 x_for_min;
    s16 y_for_max;
    s16 y_for_min;
    s32 x_limit;
    s32 y_limit;
    u16 first_x;
    u16 first_y;
    s32 base_extent;
    u8 *config_base;
    u8 *size_config;
    void *point;

    first_x = ((func_800A00A8_S_8009D808_0 *)points)->unk_00;
    min_point->unk_00 = first_x;
    max_point->unk_00 = first_x;
    first_y = ((func_800A00A8_S_8009D808_0 *)points)->unk_02;
    min_point->unk_02 = first_y;
    max_point->unk_02 = first_y;
    config_base = ((u8 *)(&g_game_work));
    size_config = config_base + 0x1DC;
    if ((s16) max_point->unk_00 < 0) {
        min_point->unk_00 = 0U;
        max_point->unk_00 = 0U;
    }
    if ((s16) max_point->unk_02 < 0) {
        min_point->unk_02 = 0U;
        max_point->unk_02 = 0U;
    }
    base_extent = 0x40;
    point = points;
    do {
        x_for_max = ((func_800A00A8_S_8009D808_3 *)point)->unk_00;
        if ((s16) max_point->unk_00 < x_for_max) {
            max_point->unk_00 = (u16) ((func_800A00A8_S_8009D808_3 *)point)->unk_00;
            x_limit = (base_extent << ((s16 *)size_config)[0xA]) - 1;
            if (x_limit < x_for_max) {
                max_point->unk_00 = (u16) x_limit;
            }
        }
        x_for_min = ((func_800A00A8_S_8009D808_3 *)point)->unk_00;
        if ((s16) min_point->unk_00 > x_for_min) {
            min_point->unk_00 = (u16) ((func_800A00A8_S_8009D808_3 *)point)->unk_00;
            if (x_for_min < 0) {
                min_point->unk_00 = 0U;
            }
        }
        y_for_max = ((func_800A00A8_S_8009D808_3 *)point)->unk_02;
        if ((s16) max_point->unk_02 < y_for_max) {
            max_point->unk_02 = (u16) ((func_800A00A8_S_8009D808_3 *)point)->unk_02;
            y_limit = (base_extent << ((s16 *)size_config)[0xB]) - 1;
            if (y_limit < y_for_max) {
                max_point->unk_02 = (u16) y_limit;
            }
        }
        y_for_min = ((func_800A00A8_S_8009D808_3 *)point)->unk_02;
        if ((s16) min_point->unk_02 > y_for_min) {
            min_point->unk_02 = (u16) ((func_800A00A8_S_8009D808_3 *)point)->unk_02;
            if (y_for_min < 0) {
                min_point->unk_02 = 0U;
            }
            point += 8;
        } else {
            point += 8;
        }
    } while ((s32) point < (s32) (points + 0x20));
}

/* Collect rectangles overlapping the query bounds into a null-terminated list. */
void collect_overlapping_rectangles(func_800A01E0_S_8009D940_1 *query_max, func_800A01E0_S_8009D940_2 *query_min, void **entries, void **matches) {
    s32 top;
    s32 left;
    void **entry_ptr;
    void **match_ptr;
    func_800A01E0_S_8009D940_0 *rect;

    entry_ptr = entries;
    match_ptr = matches;
    if (*entry_ptr != NULL) {
        do {
            rect = *entry_ptr;
            left = rect->unk_00 + rect->unk_04;
            if (query_max->unk_00 >= left) {
                top = rect->unk_02 + rect->unk_06;
                if ((query_max->unk_02 >= top) && ((left + rect->unk_08) >= query_min->unk_00)
                    && ((top + rect->unk_0A) >= query_min->unk_02)) {
                    *match_ptr = rect;
                    match_ptr = (void **)((s8 *)((void **)((s8 *)match_ptr + 4)));
                }
            }
            entry_ptr = (void **)((s8 *)((void **)((s8 *)entry_ptr + 4)));
        } while (*entry_ptr != NULL);
    }
    *match_ptr = NULL;
}

/* Builds four corner vertices from a rectangle with position offsets. */
void rectangle_to_four_corners(func_800A0284_S_8009D9E4_0 *rectangle, func_800A0284_S_8009D9E4_1 *vertices) {
    s16 left;
    s16 right;
    s16 top;
    s16 bottom;

    left = rectangle->unk_00 + rectangle->unk_04;
    vertices->unk_08 = left;
    vertices->unk_00 = left;
    right = rectangle->unk_08 + (rectangle->unk_00 + rectangle->unk_04);
    vertices->unk_0C = right;
    vertices->unk_04 = right;
    top = rectangle->unk_02 + rectangle->unk_06;
    vertices->unk_06 = top;
    vertices->unk_02 = top;
    bottom = rectangle->unk_0A + (rectangle->unk_02 + rectangle->unk_06);
    vertices->unk_0E = bottom;
    vertices->unk_0A = bottom;
}

/* Process eligible entries and mark those handled successfully as active. */
void process_eligible_entries(func_800A02F0_S_8009DA50_2 *entries, void *bounds, s32 origin_x, s32 origin_y)
{
    s32 test_x;
    s32 test_y;
    s16 entry_x;
    s16 entry_y;
    s32 base_y;
    s32 base_x;
    s32 flags;

    base_x = origin_x;
    base_y = origin_y;
    while (((flags = entries->unk_01) & 0xC0) != 0x80) {
        if (entries->unk_00 == 0) {
            if (!(flags & 1) ? test_resident_bitmap_bit(entries->unk_02) != 0 : test_resident_bitmap_bit(entries->unk_02) != 1) {
                test_x = base_x + entries->unk_10;
                test_y = base_y + entries->unk_12;
                entry_x = test_x;
                entry_y = test_y;
                if ((check_four_vector_half_turn_gaps(
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_00 - test_x),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_02 - test_y),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_08 - test_x),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_0A - test_y),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_10 - test_x),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_12 - test_y),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_18 - test_x),
                         (s16)(((func_800A02F0_S_8009DA50_1 *)bounds)->unk_1A - test_y)) != 0) ||
                    (map_scene_selector_alias == 0xC) ||
                    (entries->unk_01 & 0x10)) {
                    if (create_object_and_initialize_render_state(entries->unk_0C, entries->unk_04, entries->unk_05, entries->unk_06,
                            entries->unk_07, entries->unk_01 & 0x20, entries->unk_08,
                            (s16)entry_x, (s16)entry_y, entries) != 0) {
                        entries->unk_00 = 1;
                    }
                    while (!(entries->unk_01 & 0xC0)) {
                        entries++;
                    }
                }
            }
        }
        entries++;
    }
}

/* Sets the object state for the selected mode and flags. */
void set_object_state_for_mode(void *owner, SpriteFrameState *object, s32 mode, s32 flags) {
    if (mode == 2) {
        ((Rec_func_80094268_arg0 *)owner)->unk_93 = 1;
        (*(s32 *)((u8 *)object + (0x28))) = loaded_town_resource_attributes[0];
        select_sprite_entry(object, D_800D07AC, 0);
        return;
    }
    select_record_entry_and_value(object, window_sprites[mode], 0);
    if (flags & 2) {
        object->clut = 0x100;
        return;
    }
    if (flags & 4) {
        object->clut = 0x200;
        return;
    }
    object->clut = 0;
}

/* Cleans up an object when its state check succeeds, or dispatches its callback and updates it. */
void cleanup_or_dispatch_object(void *object, s32 source, s32 context) {
    s8 *status_ptr;

    if (classify_record_by_state_and_position(object, source) != 0) {
        unlink_scene_list_node(object);
        status_ptr = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (status_ptr != NULL) {
            *status_ptr = 0;
        }
        unlink_node_if_registered(object);
        ((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 = (u16) (((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    }
    ((Rec_D_80082D58 *)object)->unk_50.as_x151a23(object, object, source, context);
    if (!(((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 & 0x8000)) {
        set_state_bytes_from_flags(update_object_and_clear_status_fields(source), object);
        if (((Rec_D_80082D58 *)object)->unk_4D == 0x13) {
            advance_sprite_animation_and_textures(context);
        }
    }
}

/* Invoke the entity callback and perform follow-up processing unless its flags suppress it. */
void invoke_entity_callback_and_follow_up(func_800A06C8_EntityLike *entity, s32 callback_id, s32 callback_data)
{
    u16 *flags = (u16 *)((u8 *)entity - 2);

    entity->unk50(entity, entity, callback_id, callback_data);
    if (!(*flags & 0x8000)) {
        set_state_bytes_from_flags(update_state_when_active(callback_id), entity);
        if (entity->unk4D == 0x13) {
            advance_sprite_animation_and_textures((void *)callback_data);
        }
    }
}

/* Dispatches an object callback or switches the object to its alternate state. */
void dispatch_object_or_switch_alternate_state(func_800A075C_S_func_8009DEBC_0 *object, s32 source, s32 context) {
    u8 saved_state;

    if (classify_record_by_state_and_position(object, source) == 2) {
        unlink_node_if_registered(object);
        saved_state = object->unk_15;
        object->unk_15 = 0;
        ((func_800A075C_S_func_8009DEBC_1 *)((u8 *)object - 0x10))->unk_00 = reset_object_handler_and_saved_byte;
        object->unk_AC = saved_state;
        return;
    }

    object->unk_50(object, object, source, context);
    if (!(((func_800A075C_S_func_8009DEBC_1 *)((u8 *)object - 0x10))->unk_0E & 0x8000)) {
        set_state_bytes_from_flags(update_state_when_active(source), object);
        if (object->unk_4D == 0x13) {
            advance_sprite_animation_and_textures(context);
        }
    }
}

/* Reset the object handler and restore its saved byte unless the check returns two. */
void reset_object_handler_and_saved_byte(void *object, void *context) {
    if (classify_record_by_state_and_position(object, context) != 2) {
        register_node_if_unregistered(object, project_sprite_chain);
        ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_00 = &dispatch_object_or_switch_alternate_state;
        ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_25 = (u8) ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_BC;
    }
}

/* Creates an object with the supplied data, position, and callback mode. */
void *create_configured_object(void *object_data, void *source_position, s32 alternate_callback)
{
    ObjectNodeHeader *created;
    SpriteFrameState *render_state;
    ObjectPosition *position;
    void *object;
    u8 type;

    created = allocate_list_node(0x136, ((u8 *)(&scene_object_list_anchor)));
    if (created == 0) {
        return 0;
    }

    position = created->position;
    render_state = created->sprite;
    position->x.w.i = HALF_AT(source_position, 2);
    position->y.w.i = HALF_AT(source_position, 6);
    position->z.w.i = HALF_AT(source_position, 0xA);

    object = (u8 *)created + 0x20;
    render_state->scale_y = 0x1000;
    render_state->scale_x = 0x1000;
    render_state->color.word = 0x00808080;
    WORD_AT(object, 0x48) = 0;
    WORD_AT(object, 0x98) = 0;
    BYTE_AT(object, 0x93) = 0;

    BYTE_AT(object, 0x4C) = BYTE_AT(object_data, 0);
    BYTE_AT(object, 0x4D) = BYTE_AT(object_data, 1);
    BYTE_AT(object, 0x4E) = BYTE_AT(object_data, 2);
    BYTE_AT(object, 0x4F) = BYTE_AT(object_data, 3);
    type = BYTE_AT(object, 0x4D);

    if (type == 0x13) {
        func_800A0878_Copy84 *copy_table = COPY_TABLE_ADDRESS;
        func_800A0878_Copy84 *copy_src;

        copy_src = (func_800A0878_Copy84 *)((u32)(BYTE_AT(object, 0x4F) & 0x1F) * 84U
                              + (u8 *)copy_table);
        town_slot_snapshot = *copy_src;
    }

    configure_the_set_mode_n_4(object, position, D_800D073C);
    if (alternate_callback != 0) {
        initialize_optional_object_state(object, position, render_state, D_800D0788);
    } else {
        initialize_optional_object_state(object, position, render_state, D_800D076C);
    }

    if ((u32)(BYTE_AT(object, 0x4D) - 0x12) < 2) {
        POINTER_AT(object, 0xC) = D_800D0754;
    }
    type = BYTE_AT(object, 0x4D);

    if (type == 0x12) {
        render_state->source = &item_effect_descriptor;
    } else if (type == 0x13) {
        set_object_state_for_mode(object, render_state, BYTE_AT(object, 0x4C), D_80100B0C);
    } else {
        render_state->source = (void *)lookup_item_category_mapped_value(
            BYTE_AT(object, 0x4D), BYTE_AT(object, 0x4C));
    }

    created->update_callback = dispatch_object_or_switch_alternate_state;
    initialize_object_and_maybe_play_sound(object, object, position, render_state);
    del_t_item_w_ptr(object_data);
    return created;
}

/* Store the current record's signed value and table lookup in the script globals. */
s32 store_record_value_and_table_lookup(void) {
    runtime_script_state[0x12] = (s8)town_target_record->value;
    runtime_script_state[0x13] = item_kind_script_words[town_target_record->kind];
    return 0;
}

// Populate three global slots with a signed byte, lookup value, and record pointer from the first entry.
s32 store_selected_record_fields(void) {
    runtime_script_state[0x12] = (s8)town_target_record->value;
    runtime_script_state[0x13] = item_kind_script_words[town_target_record->kind];
    runtime_script_state[0x14] =
        (u32)((u8 *)0x80010AB4 +
              ((town_target_record->unk_4F & 0x3F) * 0x54));
    return 0;
}

/* Initializes the shared state from the selected table entry and stores the result. */
s32 initialize_shared_state_from_table(void) {
    u8 *record_table = (u8 *)0x80010A80;
    u32 record_index = town_target_record->unk_4F & 0x3F;
    s32 *state = &town_actor_scratch;

    restore_actor_stats_from_snapshot(state, record_table + (record_index * 0x54));
    monster_status_window = load_and_open_monster_status_display(state, 1, 0x5C, -0x68, 0x200);
    return 0;
}

/* Processes monster_status_window as an object pointer array and returns zero. */
s32 pass_shared_data_to_window_handler(void) {
    process_object_pointer_array(monster_status_window);
    return 0;
}

// Processes the selected town record and saves the returned result.
s32 create_selected_record_view(void)
{
    func_800A0C10_TownRecord *townRecords = (func_800A0C10_TownRecord *)0x80010AB4;
    s32 selectedRecordIndex = town_target_record->unk_4F & 0x3F;

    active_item_view = create_item_view_for_entry(
        0,
        townRecords[selectedRecordIndex].bytes,
        ((func_800A0C10_TownPage *)0x80010000)->entries[selectedRecordIndex].value);
    return 0;
}

/* Returns flag 0x8000 from the active item-view record. */
s32 get_current_high_bit_flag(void) {
    return active_item_view->unk_1E & 0x8000;
}

/* kewn_namewin_open: Open the name window and store its handle. */
s32 kewn_namewin_open(void) {
    active_item_view = create_item_view_for_entry(0, (void *)0x80010AB4,
                                  *(u8 *)0x80010980);
    return 0;
}

/* kewn_namewin_close_check: Copies the entered name to the main and matching item buffers when the close flag is set. */
s32 kewn_namewin_close_check(void) {
    s32 close_flag;
    void *matched_item;

    close_flag = active_item_view->unk_1E & 0x8000 & 0xFFFF;
    if (close_flag != 0) {
        strcpy((void *)0x80010238, (void *)0x80010AB4);
        matched_item = find_item_by_kind_and_type(2, 0x13);
        if (matched_item != 0) {
            strcpy(
                   (void *)(0x80010324 +
                            ((*(u8 *)((u8 *)matched_item + 3) & 0x1F) * 0x54)),
                   (void *)0x80010AB4);
        }
    }
    return close_flag;
}

/* t_soukowin_open: Initialize and open the storage window, saving its handle. */
s32 t_soukowin_open(void) {
    clear_global_80110_ec_0_global_80082_a_39();
    D_80100A08 = open_twin_souko(0);
    return 0;
}

/* t_soukowin_close_check: Returns the storage window close flag. */
s32 t_soukowin_close_check(void) {
    return ((func_800A0D8C_S_8009E4EC_0 *)D_80100A08)->unk_1E & 0x8000;
}

/* Sets object type fields and selects the corresponding resource. */
void set_object_types_and_resource(void *object, s32 index, void *output)
{
    u32 resource;
    u8 mode;
    u8 type;

    mode = BU(object, 0x94);
    if (mode == 0) {
        configure_the_set_mode_n_4(object, index, D_800D073C);
        initialize_optional_object_state(object, index, output, D_800D076C);
        BU(object, 0x4C) = BU(object, 0x95);
        BU(object, 0x4D) = BU(object, 0x96);
    } else
    if ((s8)mode == -1) {
        configure_the_set_mode_n_3(object, index, D_800D073C);
        initialize_optional_object_state(object, index, output, 0);
        BU(object, 0x4C) = BU(object, 0x95);
        BU(object, 0x4D) = BU(object, 0x96);
    } else {
        configure_the_set_mode_n_4(object, index, D_800D073C);
        initialize_optional_object_state(object, index, output, D_800D0788);
        {
            u8 *type_table;

            type_table = (u8 *)0x80010000;
            BU(object, 0x4C) = type_table[BU(object, 0x95) * 4 + 0x980];
            BU(object, 0x4D) = type_table[BU(object, 0x95) * 4 + 0x981];
            BU(object, 0x4E) = type_table[BU(object, 0x95) * 4 + 0x982];
            BU(object, 0x4F) = type_table[BU(object, 0x95) * 4 + 0x983];
        }
        initialize_entity_flags_transform_type_dependent_variant(object, object, index, output);
    }

    if (is_unk_18_n_12_unk_1_a_between_n_37_n_41() == 0) {
        resource = (u32)&cleanup_or_dispatch_object;
        PP(object, -0x10) = (u8 *)resource;
    } else {
        resource = (u32)dispatch_object_or_switch_alternate_state;
        PP(object, -0x10) = (u8 *)resource;
    }
    if ((u32)(BU(object, 0x4D) - 0x12) < 2U) {
        PP(object, 0xC) = D_800D0754;
    }

    type = BU(object, 0x4D);
    if (type == 0x12) {
        resource = (u32)&item_effect_descriptor;
    } else if (type == 0x13) {
        u8 *data_base = (u8 *)0x80010000;

        set_object_state_for_mode(
            object,
            output,
            BU(object, 0x4C),
            *(s32 *)&data_base[
                ((data_base[BU(object, 0x95) * 4 + 0x983] & 0x3F) * 0x54)
                    + 0xA94]);
        return;
    } else {
        resource = lookup_item_category_mapped_value(BU(object, 0x4D), BU(object, 0x4C));
    }
    WD(output, 8) = resource;
}

/* Updates an object's pulse brightness and handles its completion state. */
void update_object_pulse_brightness(func_800A0FB4_S_func_8009E714_0 *object, s32 context, SpriteFrameState *primitive) {
    s32 status_match;
    s16 phase;
    s32 wave;
    s32 wave_step;
    s32 brightness;

    status_match = classify_record_by_state_and_position(object, context) == 1;
    if (classify_record_by_state_and_position(object, context) == 1) {
        s8 *active_flag = object->unk_98;
        if (active_flag != 0) {
            *active_flag = 0;
        }
        unlink_node_if_registered(object);
        ((func_800A0FB4_S_func_8009E714_2 *)object)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    if (status_match == 2) {
        unlink_node_if_registered(object);
        return;
    }
    register_node_if_unregistered(object, project_sprite_chain);
    phase = object->unk_6C + 0x60;
    object->unk_6C = phase;
    wave = rsin(phase);
    wave_step = wave >> 7;
    if (wave < 0) {
        wave_step = (wave + 0x7F) >> 7;
    }
    brightness = (wave_step + 0x20) * 0x30;
    if (brightness < 0) {
        brightness += 0x3F;
    }
    brightness >>= 6;
    primitive->color.c.b = (s8)brightness;
    primitive->color.c.g = (s8)brightness;
    primitive->color.c.r = (s8)brightness;
    if (!(((func_800A0FB4_S_func_8009E714_2 *)object)[-1].unk_00 & 0x8000) &&
        object->unk_4D == 0x13) {
        advance_sprite_animation_and_textures(primitive);
    }
}

/* Initialize the entity from its table entry and invoke its callback. */
void initialize_entity_from_table_and_callback(void *entity, func_800A10FC_S_8009E85C_1 *placement, func_800A10FC_S_8009E85C_2 *state) {
    u8 *table_page = (u8 *)0x80010000;
    s32 active;
    s32 init_flags;
    func_800A10FC_S_8009E85C_4 *tail_entity;
    void (*callback)(void *, void *, void *);
    void *callback_entity;
    void *callback_placement;
    void *callback_state;
    u16 flags;
    u8 entry_type;

    ((func_800A10FC_S_8009E85C_0_pre *)entity)[-1].unk_00 = update_object_pulse_brightness;
    ((Rec_func_80094268_arg0 *)entity)->unk_A0 = 0xFFE00000;
    placement->unk_08 = 0xFFE00000;
    ((Rec_func_80094268_arg0 *)entity)->unk_4C = table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4) + 0x980];
    entry_type = table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4) + 0x981];
    ((Rec_func_80094268_arg0 *)entity)->unk_4D = entry_type;
    if (entry_type == 0x12) {
        state->unk_08 = &item_effect_descriptor;
    } else {
        set_object_state_for_mode(entity, state, ((Rec_func_80094268_arg0 *)entity)->unk_4C,
            ((func_800A10FC_S_8009E85C_6 *)(table_page + ((table_page[(((Rec_func_80094268_arg0 *)entity)->unk_95 * 4)
            + 0x983] & 0x3F) * 0x54)))->unk_A94);
    }
    register_node_if_unregistered(entity, project_sprite_chain);
    init_flags = 0x20;
    state->unk_10 = init_flags;
    flags = state->unk_14.s;
    active = D_800D09C8[0];
    state->unk_14.u = (u16)(flags | 0x1C);
    tail_entity = entity;
    if (active == 0) {
        ((Rec_func_80094268_arg0 *)entity)->unk_6C.as_s16 = scale_random_to_unsigned_halfword_limit(0x1000);
    } else {
        tail_entity->unk_6C = 0;
    }
    callback_entity = tail_entity;
    callback_placement = placement;
    callback_state = state;
    callback = ((func_800A10FC_S_8009E85C_5_pre *)callback_entity)[-1].unk_00;
    D_800D09C8[0] = 0;
    callback(callback_entity, callback_placement, callback_state);
}

/* Initializers selected by the low callback id in scene object records. */
extern void set_motion_handler_and_copy_signed_byte(void *, void *, SpriteFrameState *);
extern void initialize_object_resource_table(void *, void *, SpriteFrameState *);
extern void initialize_object_resource_tables(void *, void *, SpriteFrameState *);
extern void initialize_object_resources_and_state(void *, void *, SpriteFrameState *);
extern void initialize_object_state_from_selector(void *, void *, SpriteFrameState *);
extern void select_object_state_by_mode_2(void *, void *, SpriteFrameState *);
extern void initialize_optional_scene_state_a(void *, void *, SpriteFrameState *);
extern void no_op_action_callback(void *, void *, SpriteFrameState *);
extern void initialize_optional_scene_state_b(void *, void *, SpriteFrameState *);
extern void initialize_optional_scene_state_c(void *, void *, SpriteFrameState *);
extern void initialize_object_action_with_default_data(void *, void *, SpriteFrameState *);
extern void initialize_actor_action_with_default_data(void *, void *, SpriteFrameState *);
extern void initialize_timed_object_action(void *, void *, SpriteFrameState *);
extern void initialize_flagged_actor_action_a(void *, void *, SpriteFrameState *);
extern void initialize_flagged_actor_action_b(void *, void *, SpriteFrameState *);
extern void initialize_flagged_actor_action_c(void *, void *, SpriteFrameState *);
extern void initialize_flagged_actor_action_d(void *, void *, SpriteFrameState *);
extern void initialize_door_variant(void *, void *, SpriteFrameState *);
extern void initialize_scaled_effect_object(void *, void *, SpriteFrameState *);
extern void initialize_unit_scale_object(void *, void *, SpriteFrameState *);
extern void initialize_emote_animation(void *, void *, SpriteFrameState *);
extern void initialize_timed_scale_object(void *, void *, SpriteFrameState *);
extern void initialize_effect_object(void *, void *, SpriteFrameState *);
extern void initialize_resource_object(void *, void *, SpriteFrameState *);
extern void initialize_projected_sprite_chain_a(void *, void *, SpriteFrameState *);
extern void initialize_projected_sprite_chain_b(void *, void *, SpriteFrameState *);
extern void initialize_projected_sprite_chain_c(void *, void *, SpriteFrameState *);
extern void initialize_indexed_resource_object(void *, void *, SpriteFrameState *);
extern void initialize_timed_resource_object(void *, void *, SpriteFrameState *);
extern void set_record_pointer_and_byte(void *, void *, SpriteFrameState *);
extern void initialize_randomized_object_state(void *, void *, SpriteFrameState *);
extern void initialize_record_with_defaults(void *, void *, SpriteFrameState *);
extern void initialize_record_pointers_and_clear_state(void *, void *, SpriteFrameState *);
extern void initialize_variant_record_pointers_and_clear_state(void *, void *, SpriteFrameState *);
extern void initialize_person_resources(void *, void *, SpriteFrameState *);
extern void initialize_object_data_transform_color(void *, void *, SpriteFrameState *);
extern void initialize_effect_with_child_sprites(void *, void *, SpriteFrameState *);
extern void initialize_effect_with_random_angle(void *, void *, SpriteFrameState *);
extern void initialize_random_particle_effect(void *, void *, SpriteFrameState *);
extern void initialize_object_header_and_state(void *, void *, SpriteFrameState *);
extern void initialize_object_appearance_with_delay(void *, void *, SpriteFrameState *);
extern void init_object_with_countdown(void *, void *, SpriteFrameState *);
extern void initialize_record_resources(void *, void *, SpriteFrameState *);
extern void initialize_object_with_default_data(void *, void *, SpriteFrameState *);
extern void initialize_object_motion_and_animation(void *, void *, SpriteFrameState *);
extern void initialize_object_and_dispatch_by_state(void *, void *, SpriteFrameState *);
extern void no_op_secondary_effect_callback(void *, void *, SpriteFrameState *);
extern void spawn_fixed_effect_object(void *, void *, SpriteFrameState *);
extern void spawn_effect_object_with_packet(void *, void *, SpriteFrameState *);
extern void create_positioned_linked_visual_child(void *, void *, SpriteFrameState *);
extern void replace_active_table_callbacks(void *, void *, SpriteFrameState *);
extern void initialize_transform_object(void *, void *, SpriteFrameState *);
extern void initialize_object_resources_2(void *, void *, SpriteFrameState *);
extern void init_actor_slot_30(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_1_context(void *, void *, SpriteFrameState *);
extern void init_person_slot_fifty_one(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_16(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_22(void *, void *, SpriteFrameState *);
extern void init_person_slot_nineteen(void *, void *, SpriteFrameState *);
extern void func_800C60DC(void *, void *, SpriteFrameState *);
extern void configure_actor_mode_13(void *, void *, SpriteFrameState *);
extern void func_800C620C(void *, void *, SpriteFrameState *);
extern void func_800C629C(void *, void *, SpriteFrameState *);
extern void init_person_slot_thirty_five(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_63(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_32(void *, void *, SpriteFrameState *);
extern void initialize_object_slot_9_data(void *, void *, SpriteFrameState *);
extern void initialize_object_slot_9_and_display(void *, void *, SpriteFrameState *);
extern void func_800C65C8(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_15(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_47_context(void *, void *, SpriteFrameState *);
extern void initialize_object_slot_0x17(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_6_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_3(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_53(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_55(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_49(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_28_and_render_state(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_52_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_54(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_56(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_60_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_41_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_42_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_27(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_4(void *, void *, SpriteFrameState *);
extern void init_person_slot_four(void *, void *, SpriteFrameState *);
extern void set_actor_flag_copy_global(void *, void *, SpriteFrameState *);
extern void initialize_object_configuration_x(void *, void *, SpriteFrameState *);
extern void func_800C83F0(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_59_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_31(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_36(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_26_and_render_state(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_68(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_11(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_75_and_copy_global(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_76_and_copy_global(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_77_and_copy_global(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_78_and_copy_global(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_45_context(void *, void *, SpriteFrameState *);
extern void initialize_reaction_object_type_4_a(void *, void *, SpriteFrameState *);
extern void init_person_slot_sixty_one(void *, void *, SpriteFrameState *);
extern void initialize_reaction_object_type_4_f(void *, void *, SpriteFrameState *);
extern void initialize_reaction_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_18(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_18_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_46(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_38(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_30(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_57_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_62_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_24(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_25_and_render_state(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_69(void *, void *, SpriteFrameState *);
extern void init_person_slot_eight(void *, void *, SpriteFrameState *);
extern void initialize_variant_object(void *, void *, SpriteFrameState *);
extern void initialize_record_from_table_index(void *, void *, SpriteFrameState *);
extern void reset_object_substate_and_flag(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_70_and_render_state(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_71_and_render_state(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_72_and_render_state(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_73_and_render_state(void *, void *, SpriteFrameState *);
extern void init_person_slot_thirty_three(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_21_and_render_state(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_44_and_render_state(void *, void *, SpriteFrameState *);
extern void func_800CC2E8(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_11_context_variant(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_1(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_12_context(void *, void *, SpriteFrameState *);
extern void init_person_slot_fifty(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_64_and_render_state(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_65_and_render_state(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_66_and_render_state(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_34(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_14(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_20(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_58(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_43(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_80(void *, void *, SpriteFrameState *);
extern void configure_actor_slot_5(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_60(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_59(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_83(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_84(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_58(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_45(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_62(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_57(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_48(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_47(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_52(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_16(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_41(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_42(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_10(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_12(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_11_context(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_8(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_9(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_13(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_7(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_6(void *, void *, SpriteFrameState *);
extern void initialize_scene_slot_37(void *, void *, SpriteFrameState *);

TownObjectCallback town_object_callbacks[172] = {
    set_actor_flag_copy_global, /* 0 */
    initialize_scene_slot_4, /* 1 */
    configure_actor_slot_5, /* 2 */
    initialize_scene_slot_6_context, /* 3 */
    func_800CC2E8, /* 4 */
    init_person_slot_eight, /* 5 */
    initialize_object_slot_9_data, /* 6 */
    initialize_object_configuration_x, /* 7 */
    initialize_scene_slot_11, /* 8 */
    initialize_scene_slot_12_context, /* 9 */
    initialize_scene_slot_thirteen, /* 10 */
    func_800C629C, /* 11 */
    configure_actor_slot_14, /* 12 */
    initialize_scene_slot_15, /* 13 */
    configure_actor_slot_16, /* 14 */
    initialize_scene_slot_18, /* 15 */
    init_person_slot_nineteen, /* 16 */
    configure_actor_slot_20, /* 17 */
    configure_actor_slot_21_and_render_state, /* 18 */
    configure_actor_slot_22, /* 19 */
    initialize_object_slot_0x17, /* 20 */
    initialize_scene_slot_24, /* 21 */
    configure_actor_slot_25_and_render_state, /* 22 */
    configure_actor_slot_26_and_render_state, /* 23 */
    initialize_scene_slot_27, /* 24 */
    configure_actor_slot_28_and_render_state, /* 25 */
    initialize_scene_slot_30, /* 26 */
    initialize_scene_slot_31, /* 27 */
    configure_actor_slot_32, /* 28 */
    init_person_slot_thirty_three, /* 29 */
    configure_actor_slot_34, /* 30 */
    init_person_slot_thirty_five, /* 31 */
    initialize_scene_slot_36, /* 32 */
    initialize_scene_slot_37, /* 33 */
    initialize_scene_slot_38, /* 34 */
    reset_object_substate_and_flag, /* 35 */
    initialize_scene_slot_forty_sprite, /* 36 */
    initialize_scene_slot_41_context, /* 37 */
    initialize_scene_slot_42_context, /* 38 */
    configure_actor_slot_43, /* 39 */
    configure_actor_slot_44_and_render_state, /* 40 */
    initialize_scene_slot_45_context, /* 41 */
    initialize_scene_slot_46, /* 42 */
    initialize_scene_slot_47_context, /* 43 */
    init_actor_slot_30, /* 44 */
    initialize_scene_slot_49, /* 45 */
    init_person_slot_fifty, /* 46 */
    init_person_slot_fifty_one, /* 47 */
    initialize_scene_slot_52_context, /* 48 */
    initialize_scene_slot_53, /* 49 */
    initialize_scene_slot_54, /* 50 */
    initialize_scene_slot_55, /* 51 */
    initialize_scene_slot_56, /* 52 */
    initialize_scene_slot_57_context, /* 53 */
    configure_actor_slot_58, /* 54 */
    initialize_scene_slot_59_context, /* 55 */
    initialize_scene_slot_60_context, /* 56 */
    init_person_slot_sixty_one, /* 57 */
    initialize_scene_slot_62_context, /* 58 */
    configure_actor_slot_63, /* 59 */
    configure_actor_slot_64_and_render_state, /* 60 */
    configure_actor_slot_65_and_render_state, /* 61 */
    configure_actor_slot_66_and_render_state, /* 62 */
    initialize_object_resources_2, /* 63 */
    initialize_scene_slot_3, /* 64 */
    initialize_scene_slot_1, /* 65 */
    initialize_scene_slot_11_context_variant, /* 66 */
    init_person_slot_four, /* 67 */
    initialize_scene_slot_1_context, /* 68 */
    initialize_scene_slot_68, /* 69 */
    initialize_scene_slot_69, /* 70 */
    configure_actor_slot_70_and_render_state, /* 71 */
    configure_actor_slot_71_and_render_state, /* 72 */
    configure_actor_slot_72_and_render_state, /* 73 */
    configure_actor_slot_73_and_render_state, /* 74 */
    initialize_reaction_object_type_4_a, /* 75 */
    configure_actor_slot_75_and_copy_global, /* 76 */
    configure_actor_slot_76_and_copy_global, /* 77 */
    configure_actor_slot_77_and_copy_global, /* 78 */
    configure_actor_slot_78_and_copy_global, /* 79 */
    initialize_door_variant, /* 80 */
    initialize_person_resources, /* 81 */
    set_object_types_and_resource, /* 82 */
    initialize_object_resource_table, /* 83 */
    initialize_object_resource_tables, /* 84 */
    initialize_object_resources_and_state, /* 85 */
    initialize_object_state_from_selector, /* 86 */
    select_object_state_by_mode_2, /* 87 */
    initialize_optional_scene_state_a, /* 88 */
    no_op_action_callback, /* 89 */
    initialize_optional_scene_state_b, /* 90 */
    initialize_optional_scene_state_c, /* 91 */
    initialize_object_action_with_default_data, /* 92 */
    initialize_transform_object, /* 93 */
    initialize_object_header_and_state, /* 94 */
    initialize_object_appearance_with_delay, /* 95 */
    initialize_object_data_transform_color, /* 96 */
    initialize_effect_with_child_sprites, /* 97 */
    initialize_effect_with_random_angle, /* 98 */
    initialize_object_slot_9_and_display, /* 99 */
    func_800C65C8, /* 100 */
    func_800C83F0, /* 101 */
    initialize_scene_slot_ten, /* 102 */
    initialize_falling_object_sprite, /* 103 */
    initialize_variant_object, /* 104 */
    initialize_record_from_table_index, /* 105 */
    initialize_reaction_object_type_4_f, /* 106 */
    initialize_reaction_context, /* 107 */
    configure_actor_slot_80, /* 108 */
    initialize_scaled_effect_object, /* 109 */
    initialize_scene_slot_48, /* 110 */
    initialize_scene_slot_16, /* 111 */
    initialize_scene_slot_59, /* 112 */
    initialize_scene_slot_13, /* 113 */
    initialize_scene_slot_9, /* 114 */
    initialize_scene_slot_60, /* 115 */
    initialize_scene_slot_52, /* 116 */
    initialize_scene_slot_41, /* 117 */
    initialize_scene_slot_42, /* 118 */
    initialize_scene_slot_10, /* 119 */
    initialize_scene_slot_11_context, /* 120 */
    initialize_scene_slot_45, /* 121 */
    initialize_scene_slot_62, /* 122 */
    initialize_scene_slot_57, /* 123 */
    initialize_scene_slot_8, /* 124 */
    initialize_scene_slot_6, /* 125 */
    initialize_scene_slot_7, /* 126 */
    initialize_scene_slot_12, /* 127 */
    initialize_scene_slot_83, /* 128 */
    initialize_scene_slot_84, /* 129 */
    initialize_scene_slot_58, /* 130 */
    initialize_scene_slot_47, /* 131 */
    func_800C60DC, /* 132 */
    configure_actor_mode_13, /* 133 */
    func_800C620C, /* 134 */
    initialize_record_resources, /* 135 */
    initialize_object_and_dispatch_by_state, /* 136 */
    initialize_scene_slot_18_context, /* 137 */
    no_op_secondary_effect_callback, /* 138 */
    initialize_timed_scale_object, /* 139 */
    initialize_effect_object, /* 140 */
    initialize_unit_scale_object, /* 141 */
    initialize_emote_animation, /* 142 */
    initialize_entity_from_table_and_callback, /* 143 */
    set_motion_handler_and_copy_signed_byte, /* 144 */
    set_record_pointer_and_byte, /* 145 */
    initialize_timed_resource_object, /* 146 */
    initialize_randomized_object_state, /* 147 */
    initialize_indexed_resource_object, /* 148 */
    initialize_resource_object, /* 149 */
    replace_active_table_callbacks, /* 150 */
    initialize_object_motion_and_animation, /* 151 */
    spawn_fixed_effect_object, /* 152 */
    spawn_effect_object_with_packet, /* 153 */
    create_positioned_linked_visual_child, /* 154 */
    initialize_timed_object_action, /* 155 */
    initialize_projected_sprite_chain_a, /* 156 */
    initialize_projected_sprite_chain_b, /* 157 */
    initialize_projected_sprite_chain_c, /* 158 */
    initialize_flagged_actor_action_a, /* 159 */
    initialize_flagged_actor_action_b, /* 160 */
    initialize_flagged_actor_action_c, /* 161 */
    initialize_flagged_actor_action_d, /* 162 */
    initialize_object_with_default_data, /* 163 */
    initialize_actor_action_with_default_data, /* 164 */
    initialize_record_with_defaults, /* 165 */
    init_object_with_countdown, /* 166 */
    initialize_sprite_six, /* 167 */
    initialize_effect_with_sprite_set_nine, /* 168 */
    initialize_random_particle_effect, /* 169 */
    initialize_record_pointers_and_clear_state, /* 170 */
    initialize_variant_record_pointers_and_clear_state, /* 171 */
};
