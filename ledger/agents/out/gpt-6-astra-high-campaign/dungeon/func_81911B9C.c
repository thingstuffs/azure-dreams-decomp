#include "common.h"
#include "m2c_compat.h"

typedef struct S_81911B9C_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_81911B9C_1;   /* temp_v0 in func_81911B9C */

typedef struct S_81911B9C_2 {
    u8 pad_00[0x5];
    s8 unk_05;
} S_81911B9C_2;   /* ((S_81911B9C_1 *)temp_v0)->unk_0C in func_81911B9C */




void *func_8003FC64();                       /* extern */
extern M2C_UNK D_8002528C;

typedef struct S_81911B9C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81911B9C_0;   /* temp_v0 in func_81911B9C */

/* Create object 0x212 and initialize its data pointer, mode, and value. */
void func_81911B9C(s32 *initial_value) {
    S_81911B9C_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = &D_8002528C;
        ((S_81911B9C_2 *)(((S_81911B9C_1 *)object)->unk_0C))->unk_05 = 0x10;
        object->unk_20 = (s32) *initial_value;
    }
}
