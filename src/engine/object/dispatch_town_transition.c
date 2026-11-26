#include "script_symbols.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "engine/entity.h"
#include "engine/item.h"
#include "engine/movie.h"
#include "engine/object.h"
#include "engine/runtime.h"
#include "engine/scene.h"
#include "engine/town.h"
#include "slus/data.h"
#include "slus/map_state.h"
#include "town/shop/position_object_initialization_g01134.h"
#include "town/map.h"
#include "town/map/resource.h"
#include "town/shop/state_entry_processing_g00562.h"

extern void initialize_circular_list_head(void);
extern void init_town_motion_list(void);
extern void reserve_twch_load(s32 load_selector);
extern void reserve_tw_mon_load(s32 load_selector);


/* Handles change_map / chg_map_second_house_sel setup and clears the handled runtime flags. */
void dispatch_town_transition(void)
{
    u16 runtime_flags;
    GameState *page;

    reset_callback_list(&town_movie_callback_list);
    reset_callback_list(&town_transition_callback_list);
    initialize_circular_list_head();
    init_town_motion_list();
    clear_shop_record_queue();
    map_runtime_state.loaded_descriptor = 0;
    obj_disp23_cancel_sw_set(0);

    runtime_flags = runtime_dispatch_state.flags16;
    if (runtime_flags & 0x4000) {
        set_dungeon_exit_flags(0);
        reset_town_items();
        chg_map_second_house_sel();
        reserve_twch_load(1);
        reserve_tw_mon_load(1);
        file_load_com(&town_scene_resource);
    } else if (runtime_flags & 0x8000) {
        set_dungeon_exit_flags(1);
        refresh_items_and_add_counter();
        if ((test_resident_bitmap_bit(F_veld_kill) == 0) ||
            (test_resident_bitmap_bit(F_end_ending) != 0)) {
            change_map_by_home_rank_secondary();
        } else if (test_resident_bitmap_bit(F_end_ending_step0) == 0) {
            change_map_by_home_rank_tertiary();
        } else {
            chg_map_second_house_sel();
        }
        reserve_twch_load(1);
        reserve_tw_mon_load(1);
        file_load_com(&town_scene_resource);
    } else if (runtime_flags & 4) {
        chg_map_second_house_sel();
        reserve_twch_load(1);
        reserve_tw_mon_load(1);
        file_load_com(&town_scene_resource);
    } else {
        page = GAME_STATE;
        if (runtime_flags & 2) {
            page->log.head.flags &= 0xFFFD;
            if (page->resume_in_dungeon != 0) {
                set_dungeon_exit_flags(1);
                page->resume_in_dungeon = 0;
                delete_items_and_reset_state();
                chg_map_second_house_sel();
            } else {
                change_map_by_home_rank();
            }
            reserve_twch_load(1);
            reserve_tw_mon_load(1);
            file_load_com(&town_scene_resource);
        } else {
            reset_state_defaults();
            page->carry_player_FA[0] = 1;
            load_building_slot_states();
            page->town_money = 0;
            change_map(town_transition_map_descriptor);
            reserve_twch_load(0);
            reserve_tw_mon_load(0);
        }
    }

    runtime_dispatch_state.flags16 &= 0x3FF9;
    refresh_all_snapshots();
    load_resource_data();
    load_and_apply_town_building_tiles();
    town_sd_se_load_init();
}
