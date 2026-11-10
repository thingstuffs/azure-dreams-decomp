#include "town/minigame.h"
/* Starts town minigames, runs their resource setup, and dispatches table-selected map operations. */
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"
#include "engine/object.h"


/* Initialize minigame_module_read_descriptor with selector 6 and run the follow-up setup. */
void initialize_resource_selector_six(void) {
    Control_CD(6, &minigame_module_read_descriptor, 0);
    drain_cd_command_queue();
}

/* start_mogura_func: initialize the mogura activity and reset its four control values. */
void start_mogura_func(void) {
    initialize_resource_selector_six();
    initialize_mogura_minigame(0, 0, 0, 0);
}


/* Run start_tako_func initialization and reset the four control values. */
void start_tako_func(void) {
    initialize_resource_selector_six();
    initialize_tako_minigame(0, 0, 0, 0);
}


/* Run func_sn_ball initialization and reset the four control values. */
void scr_func_sn_ball(void) {
    initialize_resource_selector_six();
    initialize_snowball_minigame(0, 0, 0, 0);
}


/* start_gym_func: Prepare and start the gym event. */
void start_gym_func(void) {
    initialize_resource_selector_six();
    initialize_gym_minigame(0, 0, 0, 0);
}

/* Pass the keima resource to handler 6 and finalize the operation. */
void finalize_keima_resource_operation(void) {
    Control_CD(6, &D_800D4748, 0);
    drain_cd_command_queue();
}

s32 func_80020300(s32, s32, s32, s32);

/* start_keima_func: Prepare and start the keima event. */
void start_keima_func(void) {
    finalize_keima_resource_operation();
    func_80020300(0, 0, 0, 0);
}


/* start_keima2_func: Prepare and start the second keima event. */
void start_keima2_func(void) {
    finalize_keima_resource_operation();
    initialize_keima_interface(0, 0, 0, 0);
}

/* Pass the town resource to handler 6 and finalize the operation. */
void finalize_town_resource_operation(void) {
    Control_CD(6, &D_800D4750, 0);
    drain_cd_command_queue();
}

/* Run the two handlers for town script call 100. */
void scr_func_sn_casino(void) {
    finalize_town_resource_operation();
    initialize_casino_minigame();
}


/* func_sn_casino_slot: prepare and run the casino slot event. */
void scr_func_sn_casino_slot(void) {
    finalize_town_resource_operation();
    create_minigame_display_objects();
}

typedef struct InputRecord InputRecord;

extern s32 D_800D4758[];

/* change_map_of: Change the map using the selected table entry. */
s32 change_map_of(s32 map_index) {
    change_map(D_800D4758[map_index]);
    return 0;
}

extern s16 D_800D4770[];

/* Dispatches each table pair's second value according to the test of its first value. */
void dispatch_conditional_table_pairs(void) {
    s16 *test_id;
    s16 *target_id;

    test_id = D_800D4770;
    if (*test_id != -1) {
        s32 sentinel = -1;
        target_id = test_id + 1;
        do {
            if (test_resident_bitmap_bit(*test_id) != 0) {
                set_resident_bitmap_bit(*target_id);
            } else {
                clear_resident_bitmap_bit(*target_id);
            }
            test_id += 2;
            target_id += 2;
        } while (*test_id != sentinel);
    }
}
