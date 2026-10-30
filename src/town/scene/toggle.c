#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"
#include "town/scene.h"

extern void func_80017670(s32);
extern M2C_UNK scene_event_data;
extern M2C_UNK D_8001605E;
extern M2C_UNK D_800162A4;
extern s32 *D_80017760;


/* Flip the current slot's toggle byte, point the dispatcher at the matching handler and raise two events. */
void toggle_active_scene_event(void) {
    u8 *toggle;
    Rec_D_80016000 *state;
    s32 event;
    TownPositionState *dispatch_base;
    TownPositionState *dispatch_base_2;

    state = town_scene_root;
    D_80017760 = &D_800162A4;
    toggle = ((s32)state->event_data) + (state->entry_index * 8);
    if (*toggle != 0) {
        dispatch_base_2 = state->position;
        dispatch_base_2->unk_40 = &D_8001605E;
    } else {
        dispatch_base = state->position;
        dispatch_base->unk_40 = &scene_event_data;
    }
    event = 0x7E;
    *toggle = (*toggle + 1) & 1;
    func_80017670(event);
    func_80017670(F_act_sun);
}
