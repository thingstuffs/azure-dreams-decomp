#include "common.h"
#include "shared/game_work.h"

#include "common.h"
#include "engine/node.h"

/* Runs the entry callback, then processes the entry and sets the output field unless flagged to stop. */
void run_node_callback_and_set_marker(void *entry, void *output, void *context) {
    GameWork *runtime_state;
    s32 field_value;
    void (*callback)(void) = *(void (**)(void))entry;

    runtime_state = &g_game_work;
    if (callback != 0) {
        callback();
        if ((*(u16 *)((u8 *)entry - 2) & NODE_REMOVE) != 0) {
            return;
        }
    }

    update_node_registration(entry, context);
    field_value = ((u32)runtime_state->buttons) & 0x10;
    if (field_value != 0) {
        field_value = 5;
    } else {
        field_value = 0x10;
    }
    *(u16 *)((u8 *)output + 0xA) = field_value;
}
