#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002452C_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8002452C_1;   /* temp_v0 in func_8002452C */

typedef struct S_8002452C_2 {
    u8 pad_00[0x5];
    s8 unk_05;
} S_8002452C_2;   /* ((S_8002452C_1 *)temp_v0)->unk_0C in func_8002452C */




void *func_8003FC64();                       /* extern */
extern M2C_UNK D_8002441C;

typedef struct S_8002452C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_8002452C_0;   /* temp_v0 in func_8002452C */

/* Creates a type 0x212 object and initializes its handler, mode, and value. */
void func_8002452C(s32 initial_value) {
    S_8002452C_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = &D_8002441C;
        ((S_8002452C_2 *)(((S_8002452C_1 *)object)->unk_0C))->unk_05 = 4;
        object->unk_20 = initial_value;
    }
}
