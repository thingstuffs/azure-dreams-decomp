#include "shared/town_event_state.h"
#include "common.h"

extern s8 D_8001601C[];
extern u8 D_80017774[];
extern void *D_80018034[];

/* Select fixed data by mode or look up data using the current table index. */
void *select_event_data_by_mode(s32 unused_value, s32 unused_option, s32 mode)
{
    if (mode == 4) {
        return D_8001601C;
    } else if (mode == 5) {
        return D_80017774;
    } else {
        return D_80018034[town_event_state->unk_03];
    }
}
