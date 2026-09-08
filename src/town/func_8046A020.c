#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80019730(s32, s32);
extern M2C_UNK D_8001601C;
extern u8 D_80017774[];
extern M2C_UNK D_8002576F;

/* Select data by mode, calling func_80019730 for modes other than four and five. */
M2C_UNK *func_8001B020(s32 setup_value, s32 setup_option, s32 mode) {
    M2C_UNK *selected_data;

    if (mode == 5) {
        selected_data = (M2C_UNK *)D_80017774;
        goto done;
    }
    if (mode == 4) {
        goto case_4;
    }
    func_80019730(setup_value, setup_option);
    selected_data = &D_8002576F;
    goto done;

case_4:
    selected_data = &D_8001601C;

done:
    return selected_data;
}
