#include "common.h"

extern s32 initialize_floor_generation_state();
extern s32 set_selected_entry_state_3(s32);
typedef struct {
    s32 value;
    s32 pad[2];
} Global32;

extern Global32 D_8001967C;
extern Global32 D_80019AFC;

/* Set the mode to two and dispatch according to the current state. */
void dispatch_mode_two_by_state(s32 state_input) {
    D_8001967C.value = 2;
    if (3 == D_80019AFC.value) {
        set_selected_entry_state_3(state_input);
        return;
    }
    initialize_floor_generation_state();
}
