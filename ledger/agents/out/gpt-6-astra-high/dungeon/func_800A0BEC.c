#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_800A6194;
extern M2C_UNK D_800A624C;

typedef struct S_800A634C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_800A634C_0;   /* temp_v0 in func_800A634C */

typedef struct S_800A634C_1 {
    u8 pad_00[0x8];
    s16 unk_08;
    u8 pad_0A[0x2];
    s16 unk_0C;
} S_800A634C_1;   /* temp_v1 in func_800A634C */

/* Allocates an object and initializes its state with the supplied value. */
void *func_800A634C(s16 initialValue) {
    void *object;
    S_800A634C_1 *objectState;

    object = func_8003FC64(0);
    if (object != NULL) {
        ((S_800A634C_0 *)object)->unk_10 = &D_800A6194;
        func_8004491C(object, &D_800A624C);
        objectState = object + 0x20;
        objectState->unk_08 = 8;
        objectState->unk_0C = initialValue;
    }
    return object;
}
