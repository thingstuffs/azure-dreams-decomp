#include "common.h"
#include "m2c_compat.h"

s32 func_800A2000();
extern M2C_UNK D_800A2180;
extern M2C_UNK D_800A21EC;

/* Create objects with descending indices until allocation fails or index zero is reached. */
s32 func_800A20D8(s32 object_key, M2C_UNK payload_value, M2C_UNK payload_param, s32 count) {
    register s32 index ASM_REG("$16") = count;
    M2C_UNK *object_param;
    M2C_UNK *object_value;

    object_param = &D_800A2180;
    object_value = &D_800A21EC;
    ASM_KEEP(index);
    index -= 1;
create_next:
    if (func_800A2000(object_key, payload_value, payload_param, index, object_param, object_value) != 0) {
        goto call_succeeded;
    }
    index += 1;
    goto done;
call_succeeded:
    if (index != 0) {
        index -= 1;
        goto create_next;
    }
    ASM_CLOBBER("$16");
    index += 1;
    ASM_KEEP(index);
done:
    return index;
}
