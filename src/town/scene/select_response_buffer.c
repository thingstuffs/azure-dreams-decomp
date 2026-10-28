#include "shared/town_event_state.h"
#include "common.h"

extern void set_event_state_and_dispatch_a_2(void);
extern s32 check_event_value_in_list(s32 target_value);
extern s32 find_first_enabled_entry_id(void);
#include "town/scene.h"

extern u8 scene_mode_response_data[];
extern u8 D_8001914C[];
extern s32 D_8001E958;
extern u8 D_8001EEA7[];
extern u8 D_8001F0AA[];
extern u8 D_80021CC0[];

/* Selects a response buffer by request type, refreshing state for the initial request. */
u8 *select_response_buffer(s32 context, s32 data, s32 request) {
    u8 **state_page;
    u8 *response;

    if (request == 0) {
        state_page = (u8 **)0x80020000;
        set_event_state_and_dispatch_a_2();
        if (check_event_value_in_list((*(u8 **)((u8 *)state_page - 0x16B0))[4]) == 0) {
            (*(u8 **)((u8 *)state_page - 0x16B0))[4] = find_first_enabled_entry_id();
        }
        if ((*(u8 **)((u8 *)state_page - 0x16B0))[4] != 0) {
            D_8001E958 = 1;
            return D_80021CC0;
        }
        return D_8001F0AA;
    }

    if (request == 4) {
        return D_8001EEA7;
    }
    if (request == 5) {
        return scene_mode_response_data;
    }
    if (request != 1) {
        response = resolve_event_response_key(context, data, request);
    } else {
        response = D_8001914C;
    }
    return response;
}
