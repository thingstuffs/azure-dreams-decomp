#include "town/menu/window.h"
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
    register_node(slot_id - 0x20, D_80046398);
    *(s32 *)((u8 *)object + 8) = object_id;
}

/* Initializes the shared data pointer, clears its first word and returns it. */
s32 *initialize_shared_script_data(void) {
    D_801007F4 = D_80100900;
    D_80100900[0] = 0;
    return D_80100900;
}

/* Scale a coordinate pair by 64 and append it to the null-terminated pointer list. */
void **scale_coordinates_and_append_pointers(s32 firstX, s32 firstY, s32 secondX, s32 secondY,
                     func_8009F66C_CoordPair *coords)
{
    if (coords != NULL) {
        void **cursor = D_801007F4;

        coords->x0 = (s16)((s32)(firstX << 16) >> 10);
        coords->y0 = (s16)((s32)(firstY << 16) >> 10);
        coords->x1 = (s16)((s32)(secondX << 16) >> 10);
        coords->y1 = (s16)((s32)(secondY << 16) >> 10);
        *cursor = coords;
        cursor++;
        D_801007F4 = cursor;
        *cursor = NULL;
    }
    return D_801007F4;
}

/* Create a record, assign its handler, and run the remaining initialization routines. */
void func_8009CE34(void) {
    ((func_8009F6D4_S_8009CE34_0 *)(initialize_scene_object_in_buffer(0x11, &D_801006D0, 0x49)))->unk_10 = &build_entries_and_update_state;
    dispatch_parameterized_or_default(&D_80100900);
    update_map_world_extents();
}

/* Runs build_entry_list_and_process_items followed by run_dual_context_callbacks. */
void build_entries_and_update_state(void) {
    build_entry_list_and_process_items();
    run_dual_context_callbacks();
}

/* Run both update routines on the shared state and clear the global flag. */
void update_shared_state_and_clear_flag(void) {
    void *state = D_80100900;

    init_and_publish_script_state(state);
    process_zero_terminated_entry_lists(state);
    D_801007F8[0] = 0;
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

    base = D_80082D08;
    compute_four_point_coordinate_bounds(base, setup_a, setup_b);
    collect_overlapping_rectangles(setup_a, setup_b, D_80100900, D_801007F8);
    entry_cursor = (void **)D_801007F8;
    if (D_801007F8[0] != 0) {
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
        if (D_8006ADD4 == 0xC) {
            result = 0;
            return result;
        }
    }
    if (check_four_vector_half_turn_gaps(
            (s16)(D_80082D08[0] - position->unk_02),
            (s16)(D_80082D08[1] - position->unk_06),
            (s16)(D_80082D08[4] - position->unk_02),
            (s16)(D_80082D08[5] - position->unk_06),
            (s32)(s16)(D_80082D08[8] - position->unk_02),
            (s32)(s16)(D_80082D08[9] - position->unk_06),
            (s32)(s16)(D_80082D08[0xC] - position->unk_02),
            (s32)(s16)(D_80082D08[0xD] - position->unk_06)) == 0) {
        geometry_result = check_four_vector_half_turn_gaps(
            (s16)(D_80082D08[0] - object->unk_84),
            (s16)(D_80082D08[1] - object->unk_86),
            (s16)(D_80082D08[4] - object->unk_84),
            (s16)(D_80082D08[5] - object->unk_86),
            (s32)(s16)(D_80082D08[8] - object->unk_84),
            (s32)(s16)(D_80082D08[9] - object->unk_86),
            (s32)(s16)(D_80082D08[0xC] - object->unk_84),
            (s32)(s16)(D_80082D08[0xD] - object->unk_86));
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
        (s16)(D_80082D08[0] - position->unk_02), (s16)(D_80082D08[1] - position->unk_06),
        (s16)(D_80082D08[4] - position->unk_02), (s16)(D_80082D08[5] - position->unk_06),
        (s32)(s16)(D_80082D08[8] - position->unk_02), (s32)(s16)(D_80082D08[9] - position->unk_06),
        (s32)(s16)(D_80082D08[0xC] - position->unk_02), (s32)(s16)(D_80082D08[0xD] - position->unk_06)) == 0) {
        geom_result = check_four_vector_half_turn_gaps(
            (s16)(D_80082D08[0] - record->unk_84), (s16)(D_80082D08[1] - record->unk_86),
            (s16)(D_80082D08[4] - record->unk_84), (s16)(D_80082D08[5] - record->unk_86),
            (s32)(s16)(D_80082D08[8] - record->unk_84), (s32)(s16)(D_80082D08[9] - record->unk_86),
            (s32)(s16)(D_80082D08[0xC] - record->unk_84), (s32)(s16)(D_80082D08[0xD] - record->unk_86));
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
    s32 saved_angle_index;
    void *object;
    void *position;
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
    object = allocate_list_node(0x136, ((u8 *)(&D_80083498)));
    if (object == 0) {
        return 0;
    }
    if ((callback_id & 0xC0000000) == 0xC0000000) {
        ((func_8009FCC4_S_8009D424_0 *)object)->unk_10 = D_800D3950[(u16)callback_id];
    }
    if ((callback_id & 0xC0000000) != 0xC0000000) {
        ((func_8009FCC4_S_8009D424_0 *)object)->unk_10 = callback_id;
    }

    if (callback_id & 1) {
        position = ((func_8009FCC4_S_8009D424_0 *)object)->unk_08;
        render_data = ((func_8009FCC4_S_8009D424_0 *)object)->unk_0C;
    }
    else if (callback_id & 2) {
        position = ((func_8009FCC4_S_if_b1_0 *)object)->unk_08;
        render_data = ((func_8009FCC4_S_if_b1_0 *)object)->unk_0C;
    }
    else if (callback_id & 4) {
        position = ((func_8009FCC4_S_if_b2_0 *)object)->unk_08;
        render_data = ((func_8009FCC4_S_if_b2_0 *)object)->unk_0C;
    }
    else {
        position = ((func_8009FCC4_S_8009D424_0 *)object)->unk_08;
        render_data = ((func_8009FCC4_S_8009D424_0 *)object)->unk_0C;
    }

    ((func_8009FCC4_S_8009D424_1 *)position)->unk_02 = coord_x;
    object_state = (u8 *)object + 0x20;
    ((func_8009FCC4_S_8009D424_1 *)position)->unk_06 = coord_z;

    if (height_mode == 0) {
        ((func_8009FCC4_S_8009D424_1 *)position)->unk_0A = -0x40;
    } else {
        ((func_8009FCC4_S_8009D424_1 *)position)->unk_0A = -0xC0;
    }
    ((func_8009FCC4_S_8009D424_1 *)position)->unk_0A = query_lowered_transform_position(position);
    if (position != 0) {
        color = 0x808080;
    }
    else {
        color = 0x808080;
    }
    ((func_8009FCC4_S_8009D424_2 *)object_state)->unk_84 = ((func_8009FCC4_S_8009D424_1 *)position)->unk_02;
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
    ((func_8009FCC4_S_8009D424_3 *)state)->unk_86 = ((func_8009FCC4_S_8009D424_1 *)position)->unk_06;
    render_data->scale_y = 0x1000;
    render_data->scale_x = 0x1000;
    render_data->color.word = color;
    angle = D_800D5070[saved_angle_index & 3];
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
    ((func_8009FCC4_Callback)((func_8009FCC4_S_8009D424_0 *)object)->unk_10)(state, position, callback_render);
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
    town_state = &D_801131B8;
    mode = D_8006ADBC.field18;
    town_state->field4 = (mode == 12);
    if (mode == 12) {
        town_state->field8 = D_8006ADBC.field1A;
    } else {
        town_state->field8 = 0;
    }
    if (D_8006ADC0[0] != 0) {
        state_buffer = D_80082A80;
        system_work = state_buffer - 0x48;
        state = &D_801131B8;
        state->field1C = state_buffer;
        state->field20 = D_800D3CC8;
        state->field24 = D_800D401C;
        state->field30 = D_800D381C;
        state->field38 = (void *)0x80010000;
        state->field18 = (void *)0x80012D70;
        state->field40 = (void *)0x80013188;
        state->field3C = D_800D2EA4;
        TOWN_SYSTEM_SCRATCH->state = (void *)state;
        runtime_set_record_value_and_buffer(system_work, (void *)TOWN_SYSTEM_SCRATCH->payload);
        *(s32 *)(system_work + 0x84) = 0;
        init_object = D_80082BC0;
        init_callback = *(func_8009FE60_InitCallback *)(init_object + 0x10);
        init_callback(init_object + 0x20, 0, 0);
        func_8008AC84(0);
        ensure_packed_resource_list(state->field34);
    }
    while ((entry = *entry_cursor) != 0) {
        entry_callback = *(func_8009FE60_ListCallback *)((u8 *)entry + 0x10);
        if (entry_callback != 0)
            entry_callback();
        entry_cursor++;
    }
    runtime_set_record_value_and_buffer(D_80082A38, *(void **)((u8 *)D_80082A38 + 0x88));
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
                    (D_8006ADD4 == 0xC) ||
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
void set_object_state_for_mode(void *owner, void *object, s32 mode, s32 flags) {
    if (mode == 2) {
        ((Rec_func_80094268_arg0 *)owner)->unk_93 = 1;
        (*(s32 *)((u8 *)object + (0x28))) = D_80081458[0];
        select_sprite_entry(object, D_800D07AC, 0);
        return;
    }
    func_8003DB94(object, D_800D07A4[mode], 0);
    if (flags & 2) {
        ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0x100;
        return;
    }
    if (flags & 4) {
        ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0x200;
        return;
    }
    ((Rec_D_80082E80 *)object)->unk_12.at00_s16.v = 0;
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
        object_flag_block.flags = object_flag_block.flags | 0x8000;
        return;
    }
    ((Rec_D_80082D58 *)object)->unk_50.as_x151a23(object, object, source, context);
    if (!(((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 & 0x8000)) {
        set_state_bytes_from_flags(update_object_and_clear_status_fields(source), object);
        if (((Rec_D_80082D58 *)object)->unk_4D == 0x13) {
            func_800478B8(context);
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
            func_800478B8((void *)callback_data);
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
            func_800478B8(context);
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
    void *created;
    SpriteFrameState *render_state;
    void *position;
    void *object;
    u8 type;

    created = allocate_list_node(0x136, ((u8 *)(&D_80083498)));
    if (created == 0) {
        return 0;
    }

    position = POINTER_AT(created, 8);
    render_state = POINTER_AT(created, 0xC);
    HALF_AT(position, 2) = HALF_AT(source_position, 2);
    HALF_AT(position, 6) = HALF_AT(source_position, 6);
    HALF_AT(position, 0xA) = HALF_AT(source_position, 0xA);

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
                              + (u32)copy_table);
        D_80100AF8 = *copy_src;
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
        render_state->source = &D_8006E240;
    } else if (type == 0x13) {
        set_object_state_for_mode(object, render_state, BYTE_AT(object, 0x4C), D_80100B0C);
    } else {
        render_state->source = (void *)lookup_item_category_mapped_value(
            BYTE_AT(object, 0x4D), BYTE_AT(object, 0x4C));
    }

    POINTER_AT(created, 0x10) = dispatch_object_or_switch_alternate_state;
    initialize_object_and_maybe_play_sound(object, object, position, render_state);
    del_t_item_w_ptr(object_data);
    return created;
}

/* Store the current record's signed value and table lookup in the script globals. */
s32 store_record_value_and_table_lookup(void) {
    D_80082A38[0x12] = (s8)D_800CFCC4->value;
    D_80082A38[0x13] = D_800D0910[D_800CFCC4->kind];
    return 0;
}

// Populate three global slots with a signed byte, lookup value, and record pointer from the first entry.
s32 get_selected_table_entry(void) {
    D_80082A38[0x12] = (s8)D_800CFCC4->value;
    D_80082A38[0x13] = D_800D0910[D_800CFCC4->kind];
    D_80082A38[0x14] =
        (u32)((u8 *)0x80010AB4 +
              ((D_800CFCC4->unk_4F & 0x3F) * 0x54));
    return 0;
}

/* Initializes the shared state from the selected table entry and stores the result. */
s32 initialize_shared_state_from_table(void) {
    u8 *record_table = (u8 *)0x80010A80;
    u32 record_index = D_800CFCC4->unk_4F & 0x3F;
    s32 *state = &D_80100A10;

    restore_actor_stats_from_snapshot(state, record_table + (record_index * 0x54));
    D_80100AF4 = load_and_open_monster_status_display(state, 1, 0x5C, -0x68, 0x200);
    return 0;
}

/* Passes D_80100AF4 to process_object_pointer_array and returns zero. */
s32 pass_shared_data_to_window_handler(void) {
    process_object_pointer_array(D_80100AF4);
    return 0;
}

// Processes the selected town record and saves the returned result.
s32 get_window_mode_value(void)
{
    func_800A0C10_TownRecord *townRecords = (func_800A0C10_TownRecord *)0x80010AB4;
    s32 selectedRecordIndex = D_800CFCC4->unk_4F & 0x3F;

    D_80100AF0 = create_item_view_for_entry(
        0,
        townRecords[selectedRecordIndex].bytes,
        ((func_800A0C10_TownPage *)0x80010000)->entries[selectedRecordIndex].value);
    return 0;
}

/* Return the high-bit flag from D_80100AF0->unk_1E. */
s32 get_current_high_bit_flag(void) {
    return D_80100AF0->unk_1E & 0x8000;
}

/* kewn_namewin_open: Open the name window and store its handle. */
s32 kewn_namewin_open(void) {
    D_80100AF0 = create_item_view_for_entry(0, (void *)0x80010AB4,
                                  *(u8 *)0x80010980);
    return 0;
}

/* kewn_namewin_close_check: Copies the entered name to the main and matching item buffers when the close flag is set. */
s32 kewn_namewin_close_check(void) {
    s32 close_flag;
    void *matched_item;

    close_flag = *(u16 *)((u8 *)D_80100AF0 + 0x1E) & 0x8000 & 0xFFFF;
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
        resource = (u32)&D_8006E240;
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
void update_object_pulse_brightness(func_800A0FB4_S_func_8009E714_0 *object, s32 context, func_800A0FB4_S_func_8009E714_1 *primitive) {
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
        object_flag_block.flags |= 0x8000;
        return;
    }
    if (status_match == 2) {
        unlink_node_if_registered(object);
        return;
    }
    register_node_if_unregistered(object, project_sprite_chain);
    phase = object->unk_6C + 0x60;
    object->unk_6C = phase;
    wave = func_800644B8(phase);
    wave_step = wave >> 7;
    if (wave < 0) {
        wave_step = (wave + 0x7F) >> 7;
    }
    brightness = (wave_step + 0x20) * 0x30;
    if (brightness < 0) {
        brightness += 0x3F;
    }
    brightness >>= 6;
    primitive->unk_0E = (s8)brightness;
    primitive->unk_0D = (s8)brightness;
    primitive->unk_0C = (s8)brightness;
    if (!(((func_800A0FB4_S_func_8009E714_2 *)object)[-1].unk_00 & 0x8000) &&
        object->unk_4D == 0x13) {
        func_800478B8(primitive);
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
        state->unk_08 = &D_8006E240;
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
