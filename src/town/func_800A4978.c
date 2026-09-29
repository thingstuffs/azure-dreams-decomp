#include "common.h"
#include "m2c_compat.h"

s32 func_800A2000();
extern M2C_UNK D_800A2180;
extern M2C_UNK D_800A21EC;

/* Create objects with descending indices until allocation fails or index zero is reached. */
s32 func_800A20D8(s32 object_key, M2C_UNK payload_value, M2C_UNK payload_param, s32 count) {
    s32 index;
    index = count;
    do {
        index -= 1;
        if (func_800A2000(object_key, payload_value, payload_param, index, &D_800A2180, &D_800A21EC) == 0) {
            index += 1;
            break;
        }
    } while (index != 0);
    return index;
}
