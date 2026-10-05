#include "common.h"
#include "m2c_compat.h"

s32 func_800352FC(void);        /* extern */
extern M2C_UNK (*D_800FE5D8)(s32, M2C_UNK, M2C_UNK);

void func_800933FC(s32 callback_first_value, M2C_UNK callback_second_value, M2C_UNK callback_third_value, s32 unused_value) {
    if (func_800352FC() == 0) {
        M2C_UNK (*callback)(s32, M2C_UNK, M2C_UNK) = D_800FE5D8;
                /* MATCH: Keep the callback load before argument register setup. */
        do {
            callback(callback_first_value, callback_second_value, callback_third_value);
        } while (0);
    }
}
