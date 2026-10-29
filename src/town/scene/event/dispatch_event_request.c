#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef s32 Callback(s32);

typedef struct S_8001B828_0 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 pad_05[0x1B];
    void * unk_20;
} S_8001B828_0;   /* obj in dispatch_event_request */

extern s32 check_event_value_in_list(s32);
extern void *clear_event_resource_state_and_get_buffer(s32); /* Unprototyped: retail call passes more arguments than the callee reads */
#include "town/scene.h"
extern void func_8001E5F0(s32);

extern s32 scene_event_data;
extern u8 scene_mode_event_data[];
extern u8 D_8001914C[];


/* Dispatches requests by mode, refreshing the state code before selecting a response. */
void *dispatch_event_request(s32 request, void *data, s32 mode) {
    u8 new_code;
    s32 status;
    void *context;
    TownEventState *state;

    if (mode == 0) {
        func_8001E5F0(F_sbs01_pad13);
        context = town_event_state;
        status = check_event_value_in_list(((S_8001B828_0 *)context)->unk_04);
        if (status == 0) {
            context = town_scene_root;
            context = ((S_8001B828_0 *)context)->unk_20;
            status = (*(Callback **)((u8 *)context + 0x2D4))(0);
            if (status != 2) {
                return D_8001914C;
            }
            new_code = find_first_enabled_entry_id();
            town_event_state->selected_entry = new_code;
        }
        state = town_event_state;
        if (state->selected_entry != 0) {
            return clear_event_resource_state_and_get_buffer(state->selected_entry);
        }
        return D_8001914C;
    }
    if (mode == 1) {
        advance_dispatch_state_to_two();
        return resolve_event_response_key(request, data, 1);
    }
    if (mode == 5) {
        return scene_mode_event_data;
    }
    if (mode == 4) {
        return &scene_event_data;
    }
    return resolve_event_response_key(request, data, mode);
}
