#include "common.h"
#include "m2c_compat.h"

s32 func_8003FC64();                         /* extern */
M2C_UNK func_8004491C();              /* extern */
extern M2C_UNK D_800A5FC0;

typedef struct S_800A613C_0 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
} S_800A613C_0;   /* temp_v1 in func_800A613C */

/* Create an object, attach its descriptor, and initialize its data fields. */
s32 func_800A613C(void) {
    s32 object;
    S_800A613C_0 *object_data;

    object = func_8003FC64(0);
    if (object != 0) {
        func_8004491C(object, &D_800A5FC0);
        object_data = object + 0x20;
        object_data->unk_08 = 6;
        object_data->unk_0C = 0x10;
    }
    return object;
}
