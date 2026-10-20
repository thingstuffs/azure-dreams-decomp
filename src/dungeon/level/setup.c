#include "modules/dungeon_dungeon_setup.h"

static __inline__ void set_light_vectors(u8 *view_state, s16 x, s16 y)
{
    *(s16 *)(view_state + 0x38) = x;
    *(s16 *)(view_state + 0x3A) = y;
    *(s16 *)(view_state + 0x3C) = x;
    *(s16 *)(view_state + 0x3E) = -x;
    *(s16 *)(view_state + 0x40) = -y;
    *(s16 *)(view_state + 0x42) = -x;
    *(s16 *)(view_state + 0x44) = 0;
    *(s16 *)(view_state + 0x46) = 0;
    *(s16 *)(view_state + 0x48) = 0;
}

/* Initialize projection, lighting, colors, and view bounds. */
void init_dungeon_view(void) {
    u8 *render_data;
    u8 *view_state;
    s32 default_scale;
    void *light_matrix;

    render_data = ((u8 *)(&g_game_work));
    view_state = render_data + 0x18;
    default_scale = 0x200;
    *(s32 *)(view_state + 0x88) = default_scale;
    func_80064F20(default_scale);
    *(s32 *)(view_state + 0x78) = 0;
    *(s32 *)(view_state + 0x7C) = 0;
    *(s32 *)(view_state + 0x80) = 0;
    func_80064EE0(0, 0, 0);
    *(s16 *)(view_state + 0x58) = default_scale;
    *(s16 *)(view_state + 0x5E) = default_scale;
    *(s16 *)(view_state + 0x64) = default_scale;
    *(s16 *)(view_state + 0x5A) = -0x100;
    *(s16 *)(view_state + 0x60) = -0x100;
    *(s16 *)(view_state + 0x66) = -0x100;
    *(s16 *)(view_state + 0x5C) = 0;
    *(s16 *)(view_state + 0x62) = 0;
    *(s16 *)(view_state + 0x68) = 0;
    func_80064D50(render_data + 0x70);

    light_matrix = render_data + 0x50;
    set_light_vectors(view_state, -0x800, 0x800);
    func_80064D20(light_matrix);

    *(s32 *)(view_state + 0x84) = 0x1000;
    func_80064624(0x1000, *(s32 *)(view_state + 0x88));
    func_80064EC0(0xA0, 0xA0, 0xA0);
    D_801C9E40.red = 0;
    D_801C9E40.green = 0;
    D_801C9E40.blue = 0;
    D_801DA714.red = 0;
    D_801DA714.green = 0;
    D_801DA714.blue = 0;
    func_80064F00(0xA0, 0x78);
    *(s16 *)(render_data + 0x18) = -0xBC;
    *(s16 *)(render_data + 0x1A) = -0x88;
    *(s16 *)(render_data + 0x1C) = 0x172;
    *(s16 *)(render_data + 0x1E) = 0x19A;
    g_dungeon_status.monster_spawn_table = &D_800DDC7C;
}

void initialize_floor_generation_state(void) {
    u32 color_command = 0x2C808080;
    dungeon_setup_802831D8_GlobalState *state = ((dungeon_setup_802831D8_GlobalState *)&g_game_work);
    dungeon_setup_802831D8_InitBlock *init_block = &state->unk1DC;
    u16 block_extent = 0x3F;
    u32 block_offset;
    u8 *flag_page;


    init_block->unk14 = 6;
    init_block->unk18 = block_extent;
    block_offset = 6;
    init_block->unk16 = block_offset;
    init_block->unk1C = 0x180;
    init_block->unk1E = 0x180;
    init_block->unk1A = block_extent;
    state->unkA8 = color_command;
    state->unk1DC.unk00 = (u32)D_800EA000;
    setup_run_and_load_track();
    flag_page = D_80080AA0 - 0xAA0;
    flag_page[0xAA0] = 0;
    {
        flag_page = D_800E3D20 - 0x3D20;

        flag_page[0x3D20] = 0;
        set_continuation_value(D_800EA000 - 0x9C14);
    }
}


void reset_dungeon_runtime_state(void) {
    u8 *init_flag_page;
    s16 *progress_stats;
    s32 *reset_values;

    bzero(((s32 *)D_800E3548), 0x100);
    bzero(&D_800E36C8, 0x300);
    g_dungeon_status.activity_counts.parts.pending_movement_count = 0;
    g_dungeon_status.activity_counts.parts.pending_action_count = 0;
    g_dungeon_status.trap_counts.parts.pending_trap_count = 0;
    g_dungeon_status.active_actor = 0;
    g_dungeon_status.pending_display_owner = 0;
    ((Rec_D_80083460 *)(&g_dungeon_status.turn_scale))->unk_00 = 0x100;
    g_dungeon_status.flags = 0;
    g_dungeon_status.monster_count = 0;
    g_dungeon_status.movement_frames_left = 0;
    D_800DCE68 = 0;
    D_800E3E40 = 0;
    D_800E296C = 0;
    D_800E3CCC = 0;
    D_800E3CCE = 0;
    D_800DCF4F = 0;
    D_80080A90 = &D_8014A000;
    D_800E3D70 = 0;
    reset_values = &D_800E3D70;
    ((dungeon_setup_8028325C_S_8001625C_2 *)reset_values)->unk_04 = 0;
    ((dungeon_setup_8028325C_S_8001625C_2 *)reset_values)->unk_08 = 0;
    D_800DCF58 = 1;
    D_800DCF5B = 0;
    if (D_80082E6B != 5) {
        progress_stats = D_80081468;
        if (progress_stats[2] >= 0x64) {
            progress_stats[2] = 0x63;
        }
        if ((u32) D_80012D60 < (u32) progress_stats[2]) {
            D_80012D60 = (s32) progress_stats[2];
        }
    }
    init_flag_page = (u8 *)0x800E0000;
    if (((dungeon_setup_8028325C_S_8001625C_3 *)((u8 *)init_flag_page - 0x30B2))->unk_00 == 0) {
        file_load_com(&D_80080AE0);
        file_load_com(&D_80080AE8);
        file_load_com(&D_80080E18);
        file_load_com(&D_80080E20);
        file_load_com(&D_80080EE8);
        file_load_com(&D_80080E30);
        D_80080A80 = func_80048D00();
        ((dungeon_setup_8028325C_S_8001625C_3 *)((u8 *)init_flag_page - 0x30B2))->unk_00 = 1;
    }
}

/* MECHANISM: Named D_80083460 and D_80081468 bases reproduce the retail held-address forms.
   D_800E3D70 and D_80012D60 use their symbol addresses without duplicated byte displacements.
   Holding the 0x800E0000 page in s0 removes one addiu and closes the branch-displacement cascade. */

void initialize_dungeon_floor_state(void) {
    s32 floor_data;
    s32 floor_index;
    u32 saved_init_value;
    RuntimeDispatchState *dungeon_state;
    u8 *globals_base;

    initialize_dungeon_record_kinds();
    clear_dungeon_state_bytes();
    bzero(D_800E3E48, 0xAF0);
    D_80082E80.unk_038 = 0;
    g_dungeon_status.turn_counter = 0;
    D_80080A88 = 0;
    if ((D_80013714 & 3) == 0) {
        D_8008146C = 1;
        D_8001022C++;
        init_koh_properties_and_entry_tables();
        func_8004A918();
    } else {
        saved_init_value = 0x80010000;

        saved_init_value = *(u16 *)(saved_init_value + 0x234);

        D_8008146C = (u16)saved_init_value;
    }
    globals_base = (u8 *)0x80010000;
    if (D_800DCF4E == 0) {
        D_80080A80 = func_80048D00();
        D_800DCF4E = 1;
    }
    if ((*(u16 *)(globals_base + 0x3714) & 3) == 0) {
        *(s32 *)(globals_base + 0x3628) = rand();
        *(s16 *)(globals_base + 0x3624) = rand() & 0xFF;
        *(s16 *)(globals_base + 0x209C) = rand() & 0xFF;
        mark_category_items_flag_400(*(s32 *)(globals_base + 0x2090));
    }
    shuffle_enabled_item_category_pointers();
    dungeon_state = &D_80082E60;
    if (dungeon_state->field_B >= 0x12) {
        floor_index = dungeon_state->field_B - 0x12;
        func_80040AA0(0x11);
        pack_tagged_resource_descriptor(0xC, (void *)0x80010000, &floor_data,
                      (floor_index * 0xC) + 0x399D);
        Control_CD(6, &floor_data, 0);
        drain_cd_command_queue();
        D_800E3D1C = 0x384;
        *(u16 *)(globals_base + 0x3714) |= 5;
    } else {
        func_80040AA0(0x11);
        D_800E3D1C = 0;
    }
    set_monster_data_pointer();
    func_800499BC();
    D_800E3CD0 = 0;
}

void initialize_dungeon_actor(void) {
    u8 pos_x;
    u8 pos_y;
    u16 flags;
    void *allocation;
    u8 *actor_storage;
    u8 *actor;
    u8 *call_target;
    u8 *state;
    u8 *obj;
    u8 *entity;
    u8 *room;
    u8 first_height;
    s16 height;
    s16 *delta_x;
    u8 *delta_page;
    s16 *delta_y;
    s32 height_diff;
    s32 entry_index;
    s32 offset_index;
    s32 sample_x;
    s32 sample_y;
    s32 state_config;
    GameWork *table_base;
    u8 tile;
    u8 actor_x;
    u8 actor_y;
    u16 display_setting;
    s32 lift_height;
    u8 *display_state;
    s32 bind_count;
    u8 *bind_state;
    u8 *bind_angle;
    u8 *defaults_page;
    u16 init_flags;
    s32 neutral_color;
    s32 object_color;
    s32 entity_mask;
    s32 copy_tail;
    u16 final_flags;

    table_base = &g_game_work;
    D_800DCF5A = 1;
    allocation = initialize_scene_object_in_buffer(0, ((u8 *)(&D_80083498)), 0x53);
    ((dungeon_setup_802835B8_S_800165B8_0 *)allocation)->unk_10 = D_80089AA0;
    register_node(allocation, project_sprite_chain);
    actor_storage = ((u8 *)(&D_80083780.x.v));
    ((dungeon_setup_802835B8_S_800165B8_0 *)allocation)->unk_08 = actor_storage;
    actor = actor_storage;
    zero_words(actor, 6);
    state = ((u8 *)(&D_80082E80));
    ((dungeon_setup_802835B8_S_800165B8_0 *)allocation)->unk_0C = state;
    zero_words(state, 0xC);
    D_800814A8 = obj = (u8 *)allocation + 0x20;
    D_800E3D7C = obj;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_13 = 0;
    entity = obj;
    room = (u8 *)&D_80082E60;

    if (!(((dungeon_setup_802835B8_S_800165B8_2 *)room)->unk_16 & 1)) {
retry_position:
        do {
        } while (select_dungeon_spawn_tile(&pos_x, &pos_y) < 0);
        if (D_80012090 != 0 || test_resident_bit(0x1389) != 0) {
            goto position_selected;
        }
        call_target = actor;
        if (D_8008146C != 0x1F) {
            goto initialize_position;
        }
        bind_state = (u8 *)(-0x400);
        first_height = sample_terrain_surface_height((pos_x << 6) | 0x20,
                                     (pos_y << 6) | 0x20, (s32)bind_state);
        entry_index = -1;
        delta_x = dir_step_x;
        delta_y = dir_step_y;
        do {
        get_offset_map_cell_value_and_flags(pos_x, pos_y, (s16)entry_index, &flags);
        bind_state = (u8 *)(-0x400);
        if (flags & 0x8000) {
            goto retry_position;
        }
        offset_index = entry_index & 7;
        {
            u8 sample_tile_y;
            s32 sample_y_sum;

            sample_tile_y = pos_y;
            sample_x = (pos_x << 6) + 0x20;
            sample_x += delta_x[offset_index] << 6;
            sample_x &= 0xFFE0;
            sample_y = ((s32)sample_tile_y << 6) + 0x20;
            sample_y_sum = sample_y + (delta_y[offset_index] << 6);
            sample_y = sample_y_sum & 0xFFE0;
        }
        height = sample_terrain_surface_height(sample_x, sample_y, (s32)bind_state);
        height_diff = (height & 0xFF) - (first_height & 0xFF);
        if (height_diff < 0) {
            height_diff = -height_diff;
        }
        entry_index++;
        if (height_diff >= 0x21) {
            goto retry_position;
        }
        } while (entry_index < 2);
    } else {
        pos_x = ((dungeon_setup_802835B8_S_800165B8_2 *)room)->unk_10;
        pos_y = ((dungeon_setup_802835B8_S_800165B8_2 *)room)->unk_12;
    }
position_selected:
    call_target = actor;
initialize_position:
    entry_index = 7;
    {
        u8 setup_x;
        u8 setup_y;

        setup_x = pos_x;
        setup_y = pos_y;
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_24 = setup_x;
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_25 = setup_y;
        set_record_integer_tile_center(call_target, setup_x, setup_y);
    }
    cycle_map_cell_flags(pos_x, pos_y, 0x300);
    height = sample_terrain_surface_height(((dungeon_setup_802835B8_S_800165B8_4 *)actor)->unk_02, ((dungeon_setup_802835B8_S_800165B8_4 *)actor)->dungeon_setup_802835B8_unk_06, -0x400);
    actor_x = pos_x;
    actor_y = pos_y;
    ((dungeon_setup_802835B8_S_800165B8_4 *)actor)->unk_0A = height;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_88 = height;
    (*(s16 *)((u8 *)entity + 0x8A)) = height;
    delta_page = (u8 *)(((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2);
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_0C = 0x2C808080;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2 = (s32)delta_page | 0x10;
    state_config = D_80080A80;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_5C = allocation;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_58 = allocation;
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_1E = 0x1000;
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_1C = 0x1000;
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_28 = state_config;
    restore_inventory_and_familiars(obj, entity, actor_x, actor_y);

    entity_mask = 0xFFEFFFFF;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_14 &= entity_mask;
    do {
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state, (&D_800DD078)[entry_index], 0, 0);
        D_800E3D80[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state, (&D_800DD0A8)[entry_index], 0, 0);
        D_800E3CF8[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state, (&D_800DD090)[entry_index], 0, 0);
        D_800E3D48[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        entry_index--;
    } while (entry_index >= 0);
    D_800E3D18 = D_800E3CF8;

    if ((get_entity_effect_value(entity, 0xA) << 16) != 0) {
        (*(void * *)((u8 *)state + 0x2C)) = D_800DD274;
        func_8003DB94(state,
            *(void **)((u8 *)D_800DD274 +
                (((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 7) & 0x1C)),
            0);
    } else {
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state, 0xB0, 0, 1);
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_2C = D_800DCFB0;
    }
    bind_count = 1;
    bind_angle = obj + 0x2A;
    (*(s16 *)((u8 *)obj + 0x94)) = -1;
    (*(s16 *)((u8 *)obj + 0x118)) = 0;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_2A = 0x400 - (((u16)g_game_work.view.camera_rotation.parts.viewAngle + 0x100) & 0xE00);
    create_tracked_effect((u8 *)&D_80083498, bind_count, state + 0x2C, bind_angle);
    {
        s32 clear_flag_mask;

        clear_flag_mask = 0xFFEFFFFF;
        ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_9A = 0xFF;
        ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_1C &= clear_flag_mask;
    }
    restore_player_control_callback(obj, entity);
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_14 |= 0x8000;
    defaults_page = (u8 *)0x80010000;
    for (entry_index = 0; entry_index < 2; entry_index++) {
        tile = defaults_page[entry_index + 0x2D6C];
        ((dungeon_setup_802835B8_S_800165B8_6 *)(obj + entry_index))->unk_FA = tile;
        if (tile == 2) {
            ((dungeon_setup_802835B8_S_800165B8_6 *)(obj + entry_index))->unk_FA = 1;
        }
    }

    object_color = 0x2C808080;
    entry_index = (s32)0x80010000;
    delta_page = (u8 *)(((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2);
    delta_page = (u8 *)(((s32)delta_page) | (0x10));
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2 = (s32)delta_page;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_14 |= 0x4000;
    bind_state = (u8 *)(0x8001020C);
    *(dungeon_setup_802835B8_Copy13 *)(entity + 0x34) = *(dungeon_setup_802835B8_Copy13 *)(u32)bind_state;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_42 = 0;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_41 = 0;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_DC = object_color;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_E0 = object_color;

    {
        u32 tile_y;
        s32 display_index;
        u16 height_index;
        u16 display_value;

        u16 *display_table = D_800DD264;
        call_target = (u8 *)(u32)((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_24;
        display_index = *(u16 *)((u8 *)entry_index + 0x20A2);
        tile_y = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_25;
        display_setting = *(u16 *)((u8 *)display_table + (s16)display_index * 2);
        bind_state = (u8 *)&g_dungeon_status;
        table_base->view.camera_rotation.parts.camera_rotation_x = display_setting;
        height_index = *(u16 *)((u8 *)entry_index + 0x20A0);
        *(u16 *)D_800DCE60 = display_setting;
        lift_height = *(u16 *)((u8 *)D_800DD26C + (s16)height_index * 2);
        display_value = ((u16)table_base->view.camera_rotation.parts.camera_rotation_y);
        display_state = D_800DCE60;
        ((dungeon_setup_802835B8_S_800165B8_8 *)display_state)->unk_04 = 0;
        (*(u16 *)((u8 *)display_state + 2)) = display_value;
        D_800E4938[0] = 0;
        final_flags = ((DungeonGlobalStatus *)bind_state)->flags;
        *(void **)&D_800E4938[1] = allocation;
        D_800E4938[2] = 0;
        final_flags |= 2;
        ((DungeonGlobalStatus *)bind_state)->flags = final_flags;
        ((dungeon_setup_802835B8_S_800165B8_8 *)display_state)->dungeon_setup_802835B8_unk_06.s = lift_height;
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_26 =
            find_active_rect_containing_point((s32)call_target, tile_y, bind_state, lift_height);
    }
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_9C = -2;
    process_global_buffer_and_submit();
    {
        s32 actor_lift;

        call_target = actor;
        actor_lift = ((dungeon_setup_802835B8_S_800165B8_8 *)display_state)->dungeon_setup_802835B8_unk_06.u;
        D_800E3540 = 0;
        D_80081484 = 0;
        D_80081470 = 0;
        initialize_random_effect_position(call_target, actor_lift);
    }
    init_flags = ((dungeon_setup_802835B8_S_800165B8_10 *)(u8 *)entry_index)->unk_3714;
    D_80082A3B = -0x24;
    if (init_flags & 4) {
        create_pulsing_effect_object();
    }
}

void apply_tile_flags_to_rectangle(s16 start_x, s16 start_y, s16 width, s16 height)
{
    s32 tile_y;
    s32 tile_x;
    s32 tiles_base;
    s16 row_width;
    s32 col;
    s32 row;
    u32 tile_id;
    u8 *flag_table;
    u8 *tile_flags;
    u8 *flags;
    u8 *extra_flags;
    void *tile;
    dungeon_setup_80283BF0_S_80016BF0_0 *map;
    GameWork *state;
    dungeon_setup_80283BF0_S_80016BF0_3 *tile_above;
    dungeon_setup_80283BF0_S_80016BF0_4 *tile_below;

    state = &g_game_work;
    map = (u8 *)state + 0x1DC;
    flag_table = map->unk_10;
    if (flag_table != 0) {
        row = 0;
        tiles_base = ((s32)state->map.cells);
        tile_flags = flag_table;
        if ((height << 0x10) > 0) {
            do {
                col = 0;
                if (width > 0) {
                    tile_y = start_y + row;
                    row_width = width;
                    do {
                        tile = (void *)(tiles_base + (((tile_y << map->unk_14) + start_x + col) * 6));
                        tile_id = ((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_00;
                        flags = tile_flags + tile_id;
                        if (*flags & 1) {
                            ((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 = (u16)(((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 | 1);
                        }
                        if (*flags & 4) {
                            ((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 = (u16)(((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 | 4);
                        }
                        if (*flags & 8) {
                            ((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 = (u16)(((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 | 8);
                        }
                        if (*flags & 0x20) {
                            ((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 = (u16)(((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 | 0x400);
                        }
                        tile_x = col + start_x;
                        if (*flags & 2) {
                            if (tile_x > 0) {
                                ((dungeon_setup_80283BF0_S_80016BF0_2_pre *)tile)[-1].unk_00 =
                                    (u16)(((dungeon_setup_80283BF0_S_80016BF0_2_pre *)tile)[-1].unk_00 | 1);
                            }
                            if (tile_x < ((1 << map->unk_14) - 1)) {
                                ((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_0A = (u16)(((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_0A | 1);
                            }
                            if (tile_y > 0) {
                                tile_above = (void *)((((0 - (1 << map->unk_14)) * 6)) + (u32)tile);
                                tile_above->unk_04 = (u16)(tile_above->unk_04 | 1);
                            }
                            if (tile_y < ((1 << map->unk_16) - 1)) {
                                tile_below = (u8 *)tile + (6 << map->unk_14);
                                tile_below->unk_04 = (u16)(tile_below->unk_04 | 1);
                            }
                        }
                        extra_flags = tile_flags + tile_id;
                        if (*extra_flags & 0x80) {
                            ((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 = (u16)(((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 | 0x8000);
                        }
                        if (*extra_flags & 0x40) {
                            ((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 = (u16)(((dungeon_setup_80283BF0_S_80016BF0_2 *)tile)->unk_04 | 0x40);
                        }
                        col += 1;
                    } while (col < row_width);
                }
                row += 1;
            } while (row < height);
        }
    }
}

/* MECHANISM: The body holds the D_80083160 base through the early branch and hoists its 0x1dc table
   pointer before both nested loops. The map pointer and signed inner bound split v1->t4 and s0->t5;
   BASE[index] fixes the neighbor addu order. */

void apply_state_index_tile_masks(void)
{
    void *state = ((u8 *)(&g_game_work));

    state = (u8 *)state + 0x1DC;

    apply_tile_flags_to_rectangle(0, 0, (s16)(1 << *(s16 *)((u8 *)state + 0x14)),
                  (s16)(1 << *(s16 *)((u8 *)state + 0x16)));
}

/* MECHANISM: Keep the natural 24-byte call frame with only $ra saved at 0x10. */

void initialize_dungeon_record_kinds(void)
{
    s16 next_type1_count;
    s16 next_type3_count;
    u8 *type2_payload;
    s16 type1_count;
    s16 type3_count;
    u8 *record;
    u8 *type1_payload;
    u8 *type3_payload;
    short record_index;
    s32 record_kind;
    record = D_800E3DB0;
    type1_count = 0;
    record_index = 0;
    record_kind = 1;
    do {
        type1_payload = record + 4;
        next_type1_count = type1_count + 1;
        type1_count = next_type1_count;
        *record = record_kind;
        *((s8 *) (((u8 *) type1_payload) + (-1))) = record_index;
        record_index += 1;
        *((s8 *) (((u8 *) type1_payload) + (-3))) = 0;
        *((s8 *) (((u8 *) type1_payload) + (-2))) = 0;
        *((s32 *) (((u8 *) type1_payload) + 0)) = 0;
        record += 8;
    }
    while (next_type1_count < 4);
    type3_count = 0;
    record_kind = 3;
    do {
        type3_payload = record + 4;
        next_type3_count = type3_count + 1;
        type3_count = next_type3_count;
        *record = record_kind;
        *((s8 *) (((u8 *) type3_payload) + (-1))) = record_index;
        record_index += 1;
        *((s8 *) (((u8 *) type3_payload) + (-3))) = 0;
        *((s8 *) (((u8 *) type3_payload) + (-2))) = 0;
        *((s32 *) (((u8 *) type3_payload) + 0)) = 0;
        record += 8;
    }
    while (next_type3_count < 2);
    *((s8 *) (((u8 *) record) + 0)) = 2;
    *((s8 *) (((u8 *) record) + 1)) = 0;
    *((s8 *) (((u8 *) record) + 2)) = 0;
    type2_payload = record + 4;
    *((s8 *) (((u8 *) record) + 3)) = record_index;
    *((s32 *) type2_payload) = 0;
}

void initialize_dungeon_region_records(void) {
    s16 next_count;
    s16 count;
    dungeon_setup_80283F70_S_80016F70_0 *record;
    s8 *id_ptr;
    s16 record_id;
    s8 record_type;

    record = (dungeon_setup_80283F70_S_80016F70_0 *)&D_800E3DB0;
    count = 0;
    record_id = count;
    record_type = 1;
    do {
        id_ptr = (s8 *)record + 3;
        next_count = count + 1;
        count = next_count;
        record->unk_00 = record_type;
        id_ptr[-2] = 0;
        id_ptr[-1] = 0;
        id_ptr[0] = record_id;
        record_id += 1;
        record++;
    } while (next_count < 4);
    count = 0;
    record_type = 3;
    do {
        id_ptr = (s8 *)record + 3;
        next_count = count + 1;
        count = next_count;
        record->unk_00 = record_type;
        id_ptr[-2] = 0;
        id_ptr[-1] = 0;
        id_ptr[0] = record_id;
        record_id += 1;
        record++;
    } while (next_count < 2);
    record->unk_00 = 2;
    record->unk_01 = 0;
    record->unk_02 = 0;
    record->unk_03 = record_id;
    record->unk_04 = 0;
}

void clear_dungeon_state_bytes(void) {
    s32 byte_index;
    s32 clear_base;
    byte_index = 6;
    clear_base = (s32)((u8 *)&D_800E3D7C + 0x24);
    do {
        *(u8*)(byte_index + clear_base) = 0;
        byte_index -= 1;
    } while (byte_index >= 0);
}

void clear_shared_state_values(void) {
    u8 *state;

    ((dungeon_setup_8028403C_S_8001703C_0 *)(&D_80083CE8))->unk_00 = 0;
    state = (u8 *)&D_80083CE8;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_04 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_08 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_0C = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_10 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_14 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_18 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_1C = 0;
}

void init_koh_properties_and_entry_tables(void)
{
    s32 slot_index;
    volatile u8 *clear_ptr;
    s32 source_offset;
    dungeon_setup_80284068_Entry *init_entry;
    dungeon_setup_80284068_Entry **table_slot;
    int entry_page_offset;
    u8 *table_base;
    u8 *entries_base;
    slot_index = 3;
    clear_ptr = (u8 *) 0x80010006;
    {
        u8 *state_base = (u8 *) 0x80010000;
        state_base[0x2194] = 5;
        state_base[0x21BA] = 5;
        state_base[0x2195] = 4;
        state_base[0x21BB] = 4;
        state_base[0x2196] = 4;
        state_base[0x2197] = 100;
        state_base[0x2199] = 16;
        state_base[0x21BC] = 16;
        *((s16 *) (state_base + 0x219A)) = 16;
        state_base[0x21A5] = 1;
        *((s32 *) (state_base + 0x21A8)) = 0x6000;
        *((s32 *) (state_base + 0x21B0)) = 0x6000;
        state_base[0x21A7] = 0;
        *((s32 *) (state_base + 0x21AC)) = 0;
        *((s16 *) (state_base + 0x21B4)) = 0;
        *((s16 *) (state_base + 0x21B6)) = 0;
        *((s16 *) (state_base + 0x21BE)) = 0x400;
    }
    do {
        clear_ptr[0x21C0] = 0;
        clear_ptr[0x21C1] = 0;
        clear_ptr -= 2;
    }
    while ((--slot_index) >= 0);
    slot_index = 19;
    entry_page_offset = 0x3E48;
    {
        u8 *ram_page = (u8 *) 0x80010000;
        ram_page[0x21E0] = 0xFF;
        ram_page[0x21E1] = 0xFF;
        *((s32 *) (ram_page + 0x21E4)) = 0;
    }
    do {
    init_entry = &((dungeon_setup_80284068_Entry *)D_800E3E48)[slot_index];
    table_slot = &((dungeon_setup_80284068_Entry **)D_800E3DF0)[slot_index];
    source_offset = slot_index * 0x54;
    restore_actor_stats_from_snapshot(init_entry, (void *) (0x800102F0 + source_offset));

    *table_slot = init_entry;
    } while ((--slot_index) >= 0);
    slot_index = 19;
    {
        volatile u8 *index_ptr = (u8 *) 0x80010013;
        u8 *copy_table_base = D_800E3DF0;
        dungeon_setup_80284068_Entry **copy_table_slot = (dungeon_setup_80284068_Entry **) (copy_table_base + 0x4C);
        u8 *ram_page = (u8 *) 0x800E0000;
        u8 *copy_entries_base = ram_page + entry_page_offset;
        dungeon_setup_80284068_Entry *copy_entry = (dungeon_setup_80284068_Entry *) (copy_entries_base + 0xA64);
        u8 *copy_dest;
        dungeon_setup_80284068_CursorPtr word_cursor;
        copy_dest = (u8 *) 0x80010A64;
        word_cursor.raw = (u8 *) 0x80010050;
        do {
            word_cursor.entry->dest = word_cursor.entry->src;
            index_ptr[0x2238] = get_bounded_stride_index(word_cursor.entry->arg, (void *) 0x80010248, 4, 20);
            *((dungeon_setup_80284068_Entry *) (copy_dest + 0x2260)) = *copy_entry;
            index_ptr[0x224C] = get_bounded_stride_index(*copy_table_slot, ram_page + 0x3E48, 0x8C, 20);
            copy_table_slot--;
            copy_entry--;
            copy_dest -= 0x8C;
            word_cursor.raw -= 4;
            index_ptr--;
        }
        while ((--slot_index) >= 0);
    }
    {
        u8 *ram_page = (u8 *) 0x80010000;
        *((s32 *) (ram_page + 0x2D58)) = 0;
        *((s16 *) (ram_page + 0x2D50)) = 0;
    }
}

void clear_dungeon_progress_state(void) {
    D_800DCF5A = 0;
}

void initialize_random_effect_position(dungeon_setup_802842A0_S_800172A0_0 *source, s16 base_offset) {
    s16 state_offset;
    s16 position_x;
    s16 position_y;
    GameView *state;
    void *effect;
    s32 random_angle;
    dungeon_setup_802842A0_S_800172A0_2 *bounds;
    s16 rotation_step;
    s32 random_bits;

    state = &g_game_work.view;
    bounds = (u8 *)state + 0x1C4;
    effect = (u8 *)state + 0xB8;
    random_angle = (rand() & 0x1FFF) - 0x1000;
    if (!((u16) *((s16 *)&D_80013714) & 2)) {
        position_x = source->unk_02 + (func_80064584(random_angle) * 2);
        state->camera_position.parts.camera_position_x = position_x;
        if (position_x < 0) {
            state->camera_position.parts.camera_position_x = 0;
        } else if (position_x >= bounds->unk_1C) {
            state->camera_position.parts.camera_position_x = (s16) ((u16) bounds->unk_1C - 1);
        }
        position_y = source->unk_06 + (func_800644B8(random_angle) * 2);
        state->camera_position.parts.camera_position_y = position_y;
        if (position_y < 0) {
            state->camera_position.parts.camera_position_y = 0;
        } else if (position_y >= bounds->unk_1E) {
            state->camera_position.parts.camera_position_y = (s16) ((u16) bounds->unk_1E - 1);
        }
        state_offset = (s16) (source->unk_0A - 0x400);
        state->camera_rotation.parts.camera_rotation_x = 0;
        state->camera_position.parts.camera_position_z = state_offset;
        random_bits = rand();
        rotation_step = -0x800;
        if (random_bits & 1) {
            rotation_step = 0x800;
        }
        state->camera_rotation.parts.viewAngle = rotation_step;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_00 = (void *) (effect + 4);
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_14 = 1;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_24 = 0x40;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_0C = source;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_18 = 0;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_26 = base_offset;
        state->slot[0].callback = &D_800C7B38;
        state_offset = base_offset + ((((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_24 + 1) * 0x30);
        state->view_offset.parts.view_offset_z = state_offset;
        ((dungeon_setup_802842A0_S_800172A0_3 *)effect)->unk_10 = (s32) state_offset;
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
