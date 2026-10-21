#include "common.h"

#include "common.h"
#include "engine/resource.h"

typedef struct {
    u8 pad0[0x0C];
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 padF;
    u16 unk10;
    u8 pad12[2];
    u16 unk14;
} State;

typedef struct {
    void (*callback)(void);
    u8 rest[0x0C];
} Manager;

extern Manager fade_manager_state;
extern void fade_manager_step_black(void);

/* Prepare the state when needed, set the manager callback, and process the state. */
void begin_fade_to_black(void) {
    void *manager = &fade_manager_state;
    State *state = *(State **)((u8 *)manager - 0x14);

    if (state->unkC == 0x80) {
        state->unkE = 0x60;
        state->unkD = 0x60;
        state->unkC = 0x60;
        state->unk10 = 0x20;
        state->unk14 |= 0x1C;
        fade_manager_state.callback = fade_manager_step_black;
    } else {
        fade_manager_state.callback = fade_manager_step_black;
    }

    runtime_set_destination_flag_from_source(manager, state);
}
