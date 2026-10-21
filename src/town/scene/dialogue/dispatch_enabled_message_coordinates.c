#include "script_symbols.h"
#include "shared/town_event_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



extern TownEventArgumentPair16 *select_event_data_table(s32, u8);
extern void func_8001E578(s32);

/* Dispatch the enabled town message coordinates and advance the town state. */
s32 dispatch_enabled_message_coordinates(void) {
    TownEventArgumentPair16 *message;

    if (town_event_state->dispatchState == 1) {
        message = select_event_data_table(0, town_event_state->unk_05);
        D_80016000->unk_20->callback_2F8(message->unk_00, message->unk_02);
        town_event_state->dispatchState++;
        func_8001E578(F_sbs01_pad19);
        return 1;
    }
    return 0;
}
