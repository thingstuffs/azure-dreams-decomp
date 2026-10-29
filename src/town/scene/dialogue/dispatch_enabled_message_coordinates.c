#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/dialogue.h"
#include "town/scene/event.h"

extern void func_8001E578(s32);

/* Dispatch the enabled town message coordinates and advance the town state. */
s32 dispatch_enabled_message_coordinates(void) {
    TownEventArgumentPair16 *message;

    if (town_event_state->dispatchState == 1) {
        message = select_event_data_table(0, town_event_state->selection_mode);
        town_scene_root->services->callback_2F8(message->unk_00, message->unk_02);
        town_event_state->dispatchState++;
        func_8001E578(F_sbs01_pad19);
        return 1;
    }
    return 0;
}
