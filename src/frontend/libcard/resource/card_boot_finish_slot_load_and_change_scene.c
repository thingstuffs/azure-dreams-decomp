#include "shared/runtime_dispatch.h"
#include "shared/game_state.h"
#include "common.h"
#include "frontend/libcard.h"

/* S_80082E60: shared global state struct; field_16 (u16) has bit 0x2 set here.
 * Same struct family as src/code2.c / src/w_80041818.c's D_80082E60. */


#include "frontend/libcard/interfaces.h"
#include "engine/entity.h"
#include "engine/resource.h"
#include "frontend/libcard/resource.h"

/* Selects object and global modes, sets the shared state flag, and runs updates. */
void card_boot_finish_slot_load_and_change_scene(CardSlotMenuState *object) {
    /* The resident block base is held in one local across the two calls below. */
    GameState *gs = GAME_STATE;
    s16 object_mode;
    s32 global_mode;
    u16 state_flags;

    card_boot_close_events_and_resume_timer();
    object_mode = 1;
    if (object->selected_command == 0) {
        object_mode = 3;
    }
    state_flags = runtime_dispatch_state.flags16;
    gs->log.head.flags = object_mode;
    runtime_dispatch_state.flags16 = state_flags | 2;
    card_boot_destroy_slot_selection_menu(NODE_HEADER(object));
    swap_saved_state_block();
    global_mode = 6;
    if (gs->dungeon_save_marker != 0) {
        global_mode = 5;
    }
    request_scene_dispatch_state(global_mode);
}
