#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
/* Dungeon entry state, floor setup, player initialization, and opening camera movement. */
#include "shared/sprite_frame_state.h"
#include "modules/dungeon_dungeon_setup.h"
#include "dungeon/item.h"
#include "dungeon/level.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"

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
    SetGeomScreen(default_scale);
    *(s32 *)(view_state + 0x78) = 0;
    *(s32 *)(view_state + 0x7C) = 0;
    *(s32 *)(view_state + 0x80) = 0;
    SetFarColor(0, 0, 0);
    *(s16 *)(view_state + 0x58) = default_scale;
    *(s16 *)(view_state + 0x5E) = default_scale;
    *(s16 *)(view_state + 0x64) = default_scale;
    *(s16 *)(view_state + 0x5A) = -0x100;
    *(s16 *)(view_state + 0x60) = -0x100;
    *(s16 *)(view_state + 0x66) = -0x100;
    *(s16 *)(view_state + 0x5C) = 0;
    *(s16 *)(view_state + 0x62) = 0;
    *(s16 *)(view_state + 0x68) = 0;
    SetColorMatrix(render_data + 0x70);

    light_matrix = render_data + 0x50;
    set_light_vectors(view_state, -0x800, 0x800);
    SetLightMatrix(light_matrix);

    *(s32 *)(view_state + 0x84) = 0x1000;
    SetFogFar(0x1000, *(s32 *)(view_state + 0x88));
    SetBackColor(0xA0, 0xA0, 0xA0);
    upper_draw_context.red = 0;
    upper_draw_context.green = 0;
    upper_draw_context.blue = 0;
    lower_draw_context.red = 0;
    lower_draw_context.green = 0;
    lower_draw_context.blue = 0;
    SetGeomOffset(0xA0, 0x78);
    *(s16 *)(render_data + 0x18) = -0xBC;
    *(s16 *)(render_data + 0x1A) = -0x88;
    *(s16 *)(render_data + 0x1C) = 0x172;
    *(s16 *)(render_data + 0x1E) = 0x19A;
    g_dungeon_status.monster_spawn_table = &monster_spawn_records;
}

/* Sets map dimensions and cell storage, generates the floor, and resets camera transition state. */
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
    state->unk1DC.unk00 = (u32)generation_cells;
    setup_run_and_load_track();
    flag_page = D_80080AA0 - 0xAA0;
    flag_page[0xAA0] = 0;
    {
        flag_page = camera_transition_timer - 0x3D20;

        flag_page[0x3D20] = 0;
        set_continuation_value(generation_cells - 0x9C14);
    }
}

/* Clears floor items and dungeon activity state, records floor progress, and loads shared sprite assets. */
void reset_dungeon_runtime_state(void) {
    u8 *init_flag_page;
    s16 *progress_stats;
    s32 *reset_values;

    bzero(((s32 *)dungeon_ground_items), 0x100);
    bzero(&dungeon_ground_item_positions, 0x300);
    g_dungeon_status.activity_counts.parts.pending_movement_count = 0;
    g_dungeon_status.activity_counts.parts.pending_action_count = 0;
    g_dungeon_status.trap_counts.parts.pending_trap_count = 0;
    g_dungeon_status.active_actor = 0;
    g_dungeon_status.pending_display_owner = 0;
    g_dungeon_status.turn_scale = 0x100;
    g_dungeon_status.flags = 0;
    g_dungeon_status.monster_count = 0;
    g_dungeon_status.movement_frames_left = 0;
    pending_marked_actor_count = 0;
    entity_resource_read_complete = 0;
    dungeon_floor_flags = 0;
    pickup_event_latch = 0;
    bounded_runtime_counter = 0;
    dungeon_event_pending_flag = 0;
    sprite_resource_base = &dungeon_resource_buffer;
    player_turn_fraction = 0;
    reset_values = &player_turn_fraction;
    ((dungeon_setup_8028325C_S_8001625C_2 *)reset_values)->unk_04 = 0;
    ((dungeon_setup_8028325C_S_8001625C_2 *)reset_values)->unk_08 = 0;
    D_800DCF58 = 1;
    scripted_boundary_active = 0;
    if (scene_mode_code != 5) {
        progress_stats = floor_generation_state;
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
        loaded_sprite_bundle_attributes = load_dungeon_sprite_bundle();
        ((dungeon_setup_8028325C_S_8001625C_3 *)((u8 *)init_flag_page - 0x30B2))->unk_00 = 1;
    }
}

/* MECHANISM: Named D_80083460 and D_80081468 bases reproduce the retail held-address forms.
   D_800E3D70 and D_80012D60 use their symbol addresses without duplicated byte displacements.
   Holding the 0x800E0000 page in s0 removes one addiu and closes the branch-displacement cascade. */

/* Initializes a dungeon entry or restored run, including familiars, resource slots, and scene state. */
void initialize_dungeon_floor_state(void) {
    s32 floor_data;
    s32 floor_index;
    u32 saved_init_value;
    RuntimeDispatchState *dungeon_state;
    u8 *globals_base;

    initialize_dungeon_record_kinds();
    clear_dungeon_state_bytes();
    bzero(familiar_record_storage, 0xAF0);
    reference_tile_object.unk_038 = 0;
    g_dungeon_status.turn_counter = 0;
    scene_music_hold = 0;
    if ((system_update_flags & 3) == 0) {
        current_dungeon_floor = 1;
        D_8001022C++;
        init_koh_properties_and_entry_tables();
        clear_floor_resource_state_table();
    } else {
        saved_init_value = 0x80010000;

        saved_init_value = *(u16 *)(saved_init_value + 0x234);

        current_dungeon_floor = (u16)saved_init_value;
    }
    globals_base = (u8 *)0x80010000;
    if (sprite_bundle_loaded == 0) {
        loaded_sprite_bundle_attributes = load_dungeon_sprite_bundle();
        sprite_bundle_loaded = 1;
    }
    if ((*(u16 *)(globals_base + 0x3714) & 3) == 0) {
        *(s32 *)(globals_base + 0x3628) = rand();
        *(s16 *)(globals_base + 0x3624) = rand() & 0xFF;
        *(s16 *)(globals_base + 0x209C) = rand() & 0xFF;
        mark_category_items_flag_400(*(s32 *)(globals_base + 0x2090));
    }
    shuffle_enabled_item_category_pointers();
    dungeon_state = &runtime_dispatch_state;
    if (dungeon_state->field_B >= 0x12) {
        floor_index = dungeon_state->field_B - 0x12;
        request_scene_dispatch_state(0x11);
        pack_tagged_resource_descriptor(0xC, (void *)0x80010000, &floor_data,
                      (floor_index * 0xC) + 0x399D);
        Control_CD(6, &floor_data, 0);
        drain_cd_command_queue();
        D_800E3D1C = 0x384;
        *(u16 *)(globals_base + 0x3714) |= 5;
    } else {
        request_scene_dispatch_state(0x11);
        D_800E3D1C = 0;
    }
    set_monster_data_pointer();
    invalidate_four_sprite_resource_slots();
    dungeon_button_latch = 0;
}

/* Creates the player at a chosen tile, restores inventory and familiars, and sets up sprites and camera. */
void initialize_dungeon_actor(void) {
    u8 pos_x;
    u8 pos_y;
    u16 flags;
    ObjectNodeHeader *allocation;
    u8 *actor_storage;
    ObjectPosition *actor;
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
    random_pickup_enabled = 1;
    allocation = initialize_scene_object_in_buffer(0, ((u8 *)(&scene_object_list_anchor)), 0x53);
    allocation->update_callback = D_80089AA0;
    register_node(allocation, project_sprite_chain);
    actor_storage = ((u8 *)(&view_reference_entity.x.v));
    allocation->position = actor_storage;
    actor = actor_storage;
    zero_words(actor, 6);
    state = ((u8 *)(&reference_tile_object));
    allocation->sprite = state;
    zero_words(state, 0xC);
    primary_actor_record = obj = (u8 *)allocation + 0x20;
    dungeon_actor_ring_anchor = obj;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_13 = 0;
    entity = obj;
    room = (u8 *)&runtime_dispatch_state;

    do {
        if (!(((dungeon_setup_802835B8_S_800165B8_2 *)room)->unk_16 & 1)) {
retry_position:
            do {
            } while (select_dungeon_spawn_tile(&pos_x, &pos_y) < 0);
            if (dungeon_mode_state != 0 || test_resident_bit(0x1389) != 0) {
                call_target = actor;
                break;
            }
            call_target = actor;
            if (current_dungeon_floor != 0x1F) {
                break;
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
        call_target = actor;
    } while (0);

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
    height = sample_terrain_surface_height(*(u16 *)&actor->x.w.i, *(u16 *)&actor->y.w.i, -0x400);
    actor_x = pos_x;
    actor_y = pos_y;
    actor->z.w.i = height;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_88 = height;
    (*(s16 *)((u8 *)entity + 0x8A)) = height;
    delta_page = (u8 *)(((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2);
    ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_0C = 0x2C808080;
    ((dungeon_setup_802835B8_S_800165B8_1 *)obj)->unk_A2 = (s32)delta_page | 0x10;
    state_config = loaded_sprite_bundle_attributes;
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
        equipped_actor_sprite_sources[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state, (&D_800DD0A8)[entry_index], 0, 0);
        unequipped_actor_sprite_sources[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state, (&player_attack_followup_frames)[entry_index], 0, 0);
        D_800E3D48[entry_index] = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_08;
        entry_index--;
    } while (entry_index >= 0);
    actor_direction_sprites = unequipped_actor_sprite_sources;

    if ((get_entity_effect_value(entity, STATUS_FROG) << 16) != 0) {
        (*(void **)((u8 *)state + 0x2C)) = actor_default_frames;
        select_record_entry_and_value(state,
            *(void **)((u8 *)actor_default_frames +
                (((g_game_work.view.camera_rotation.parts.viewAngle + (*(s16 *)((u8 *)entity + 0x2A)) + 0x100) >> 7) & 0x1C)),
            0);
    } else {
        texture_handle_installs_selected_animation_frame_secondary_pointer_updates_animation_flags(state, 0xB0, 0, 1);
        ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_2C = player_wait_frames;
    }
    bind_count = 1;
    bind_angle = obj + 0x2A;
    (*(s16 *)((u8 *)obj + 0x94)) = -1;
    (*(s16 *)((u8 *)obj + 0x118)) = 0;
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_2A = 0x400 - (((u16)g_game_work.view.camera_rotation.parts.viewAngle + 0x100) & 0xE00);
    create_tracked_effect((u8 *)&scene_object_list_anchor, bind_count, state + 0x2C, bind_angle);
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
    ((dungeon_setup_802835B8_S_800165B8_5 *)entity)->unk_14 |= ACTOR_PARTY_MEMBER;
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

        u16 *display_table = camera_pitch_presets;
        call_target = (u8 *)(u32)((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_24;
        display_index = *(u16 *)((u8 *)entry_index + 0x20A2);
        tile_y = ((dungeon_setup_802835B8_S_800165B8_3 *)state)->unk_25;
        display_setting = *(u16 *)((u8 *)display_table + (s16)display_index * 2);
        bind_state = (u8 *)&g_dungeon_status;
        table_base->view.camera_rotation.parts.camera_rotation_x = display_setting;
        height_index = *(u16 *)((u8 *)entry_index + 0x20A0);
        *(u16 *)dungeon_camera_targets = display_setting;
        lift_height = *(u16 *)((u8 *)camera_depth_presets + (s16)height_index * 2);
        display_value = ((u16)table_base->view.camera_rotation.parts.camera_rotation_y);
        display_state = dungeon_camera_targets;
        ((dungeon_setup_802835B8_S_800165B8_8 *)display_state)->unk_04 = 0;
        (*(u16 *)((u8 *)display_state + 2)) = display_value;
        dungeon_menu_action_state[0] = 0;
        final_flags = ((DungeonGlobalStatus *)bind_state)->flags;
        *(void **)&dungeon_menu_action_state[1] = allocation;
        dungeon_menu_action_state[2] = 0;
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
        saved_held_item_word = 0;
        held_item_record = 0;
        temporary_item_record = 0;
        initialize_random_effect_position(call_target, actor_lift);
    }
    init_flags = ((dungeon_setup_802835B8_S_800165B8_10 *)(u8 *)entry_index)->unk_3714;
    D_80082A3B = -0x24;
    if (init_flags & 4) {
        create_pulsing_effect_object();
    }
}

/* Applies tile-kind flags to a map rectangle, marking adjacent cells for kinds that require it. */
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

/* Initializes seven resource cache slots with four kind-1 entries, two kind-3 entries, and one kind-2
   entry. */
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
    record = monster_resource_cache_slots;
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

/* Initializes resource cache slot kinds and sequential IDs, then clears the trailing record. */
void initialize_dungeon_region_records(void) {
    s16 next_count;
    s16 count;
    dungeon_setup_80283F70_S_80016F70_0 *record;
    s8 *id_ptr;
    s16 record_id;
    s8 record_type;

    record = (dungeon_setup_80283F70_S_80016F70_0 *)&monster_resource_cache_slots;
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
    clear_base = (s32)((u8 *)&dungeon_actor_ring_anchor + 0x24);
    do {
        *(u8*)(byte_index + clear_base) = 0;
        byte_index -= 1;
    } while (byte_index >= 0);
}

/* Clears the eight words of saved view vectors. */
void clear_shared_state_values(void) {
    u8 *state;

    ((dungeon_setup_8028403C_S_8001703C_0 *)(&saved_view_vectors))->unk_00 = 0;
    state = (u8 *)&saved_view_vectors;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_04 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_08 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_0C = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_10 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_14 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_18 = 0;
    ((dungeon_setup_8028403C_S_8001703C_1 *)state)->unk_1C = 0;
}

/* Sets initial player properties and restores familiar records, inventory links, and saved entry tables. */
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
    init_entry = &((dungeon_setup_80284068_Entry *)familiar_record_storage)[slot_index];
    table_slot = &((dungeon_setup_80284068_Entry **)familiar_record_slots)[slot_index];
    source_offset = slot_index * 0x54;
    restore_actor_stats_from_snapshot(init_entry, (void *) (0x800102F0 + source_offset));

    *table_slot = init_entry;
    } while ((--slot_index) >= 0);
    slot_index = 19;
    {
        volatile u8 *index_ptr = (u8 *) 0x80010013;
        u8 *copy_table_base = familiar_record_slots;
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
    random_pickup_enabled = 0;
}

/* Starts a camera approach from a random offset around the player unless updates are disabled. */
void initialize_random_effect_position(ObjectPosition *source, s16 base_offset) {
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
    effect = &state->slot[0].unk_04;
    random_angle = (rand() & 0x1FFF) - 0x1000;
    if (!((u16) *((s16 *)&system_update_flags) & 2)) {
        position_x = *(u16 *)&source->x.w.i + (rcos(random_angle) * 2);
        state->camera_position.parts.camera_position_x = position_x;
        if (position_x < 0) {
            state->camera_position.parts.camera_position_x = 0;
        } else if (position_x >= bounds->unk_1C) {
            state->camera_position.parts.camera_position_x = (s16) ((u16) bounds->unk_1C - 1);
        }
        position_y = *(u16 *)&source->y.w.i + (rsin(random_angle) * 2);
        state->camera_position.parts.camera_position_y = position_y;
        if (position_y < 0) {
            state->camera_position.parts.camera_position_y = 0;
        } else if (position_y >= bounds->unk_1E) {
            state->camera_position.parts.camera_position_y = (s16) ((u16) bounds->unk_1E - 1);
        }
        state_offset = (s16) (*(u16 *)&source->z.w.i - 0x400);
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
