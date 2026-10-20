#include "town/minigame/dispatch.h"
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"


/* Initialize D_800D4740 with selector 6 and run the follow-up setup. */
void initialize_resource_selector_six(void) {
    Control_CD(6, &D_800D4740, 0);
    drain_cd_command_queue();
}
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"

s32 initialize_mogura_minigame(); /* extern */
void initialize_resource_selector_six();                            /* extern */

/* start_mogura_func: initialize the mogura activity and reset its four control values. */
void start_mogura_func(void) {
    initialize_resource_selector_six();
    initialize_mogura_minigame(0, 0, 0, 0);
}
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_resource_selector_six();                            /* extern */

/* Run start_tako_func initialization and reset the four control values. */
void start_tako_func(void) {
    initialize_resource_selector_six();
    initialize_tako_minigame(0, 0, 0, 0);
}
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_resource_selector_six();                            /* extern */

/* Run func_sn_ball initialization and reset the four control values. */
void scr_func_sn_ball(void) {
    initialize_resource_selector_six();
    initialize_snowball_minigame(0, 0, 0, 0);
}
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void initialize_resource_selector_six();                            /* extern */

/* start_gym_func: Prepare and start the gym event. */
void start_gym_func(void) {
    initialize_resource_selector_six();
    initialize_gym_minigame(0, 0, 0, 0);
}
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass the keima resource to handler 6 and finalize the operation. */
void finalize_keima_resource_operation(void) {
    Control_CD(6, &D_800D4748, 0);
    drain_cd_command_queue();
}
#include "town/minigame/dispatch.h"
#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_80020300(s32, s32, s32, s32);
void finalize_keima_resource_operation();                            /* extern */

/* start_keima_func: Prepare and start the keima event. */
void start_keima_func(void) {
    finalize_keima_resource_operation();
    func_80020300(0, 0, 0, 0);
}
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void finalize_keima_resource_operation();                            /* extern */

/* start_keima2_func: Prepare and start the second keima event. */
void start_keima2_func(void) {
    finalize_keima_resource_operation();
    initialize_keima_interface(0, 0, 0, 0);
}
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */

/* Pass the town resource to handler 6 and finalize the operation. */
void finalize_town_resource_operation(void) {
    Control_CD(6, &D_800D4750, 0);
    drain_cd_command_queue();
}
#include "town/minigame/dispatch.h"
#include "common.h"
void card_dev_init_two_rows(void);                            /* extern */
void finalize_town_resource_operation();                            /* extern */

/* Run the two handlers for town script call 100. */
void scr_func_sn_casino(void) {
    finalize_town_resource_operation();
    card_dev_init_two_rows();
}
#include "town/minigame/dispatch.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void finalize_town_resource_operation();                            /* extern */

/* func_sn_casino_slot: prepare and run the casino slot event. */
void scr_func_sn_casino_slot(void) {
    finalize_town_resource_operation();
    create_minigame_display_objects();
}
#include "town/minigame/dispatch.h"
#include "common.h"

typedef struct InputRecord InputRecord;

void change_map(InputRecord *input);
extern s32 D_800D4758[];

/* change_map_of: Change the map using the selected table entry. */
s32 change_map_of(s32 map_index) {
    change_map(D_800D4758[map_index]);
    return 0;
}
#include "town/minigame/dispatch.h"
#include "common.h"

extern s32 test_resident_bitmap_bit(s32 bit_id);
extern void set_resident_bitmap_bit(s32 bit_id);
extern void clear_resident_bitmap_bit(s32 flag_id);
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
