#include "common.h"
#include "m2c_compat.h"


extern void advance_dispatch_state_to_two(void);
extern M2C_UNK D_8001601C;
extern u8 D_80017774[];
extern M2C_UNK D_8002576F;

/* Select data by mode, calling advance_dispatch_state_to_two for modes other than four and five. */
s32 *select_event_data_with_mode_setup(s32 setup_value, s32 setup_option, s32 mode) {
    s32 *selected_data;

    if (mode == 5) {
        selected_data = (s32 *)D_80017774;
        return selected_data;
    }
    if (mode != 4) {
        advance_dispatch_state_to_two();
        selected_data = &D_8002576F;
    } else {
        selected_data = &D_8001601C;
    }
    return selected_data;
}
