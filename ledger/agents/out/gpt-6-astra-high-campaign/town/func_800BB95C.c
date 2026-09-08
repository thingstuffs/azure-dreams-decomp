#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_800B90B4;

typedef struct S_800B90BC_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800B90BC_0;   /* temp_v0 in func_800B90BC */

/* Allocate an object and set its data pointer. */
void func_800B90BC(void) {
    S_800B90BC_0 *object;

    object = func_8003FC64(0);
    if (object != NULL) {
        object->unk_10 = &D_800B90B4;
    }
}
