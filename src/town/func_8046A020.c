#include "common.h"

typedef s32 M2C_UNK;

extern void townAdvanceDispatchStateToTwo(void);
extern M2C_UNK D_8001601C;
extern u8 D_80017774[];
extern M2C_UNK D_8002576F;

/* Select data by mode, calling townAdvanceDispatchStateToTwo for modes other than four and five. */
M2C_UNK *townSelectEventDataWithModeSetup(s32 setup_value, s32 setup_option, s32 mode) {
    M2C_UNK *selected_data;

    if (mode == 5) {
        selected_data = (M2C_UNK *)D_80017774;
        return selected_data;
    }
    if (mode != 4) {
        townAdvanceDispatchStateToTwo();
        selected_data = &D_8002576F;
    } else {
        selected_data = &D_8001601C;
    }
    return selected_data;
}
