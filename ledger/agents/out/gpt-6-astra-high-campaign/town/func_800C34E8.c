#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_800C0D80(s32, s32, s32);                            /* extern */
extern M2C_UNK D_800C0C28;

typedef struct S_800C0C48_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800C0C48_0;   /* temp_v0 in func_800C0C48 */

/* Run setup, assign the retrieved object handler when present, and return -1. */
s32 func_800C0C48(s32 context, s32 value, s32 options) {
    S_800C0C48_0 *object;

    func_800C0D80(context, value, options);
    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = &D_800C0C28;
    }
    return -1;
}
