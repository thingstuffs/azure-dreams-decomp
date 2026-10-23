#include "common.h"

extern s32 get_item_chk(void);
extern void write_resource_command(void *value, s32 code);
extern void set_item_selection_data_pointer(s32 object, s32 position, s32 context);
extern void init_timed_dispatch_action(s32 object, s32 position, s32 context);
extern s32 D_80088D44;
extern s32 town_motion_action_address;
extern s32 *town_player_action_callback;
extern s32 town_interaction_pending;

/* Select the object's next state based on slot availability. */
void select_next_item_state(s32 object, s32 position, s32 context) {
    if (get_item_chk() == -1) {
        write_resource_command(&D_80088D44, 0x11);
        set_item_selection_data_pointer(object, position, context);
        town_player_action_callback = &town_motion_action_address;
        return;
    }
    init_timed_dispatch_action(object, position, context);
    town_interaction_pending = 0;
}
