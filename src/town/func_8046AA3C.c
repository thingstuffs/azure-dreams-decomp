#include "common.h"

extern void advance_dispatch_state_to_two(void);
extern u8 D_8001601C[];
extern u8 D_80017774[];
extern u8 D_80022E7E[];

/* Select data by mode, calling advance_dispatch_state_to_two for mode one. */
void *select_event_data_with_mode_1_setup(s32 setup_value, s32 setup_option, s32 mode) {
    if (mode == 1) {
        advance_dispatch_state_to_two();
        return D_80022E7E;
    } else if (mode == 4) {
        return D_8001601C;
    } else {
        return D_80017774;
    }
}
