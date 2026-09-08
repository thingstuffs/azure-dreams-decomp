#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
extern M2C_UNK D_80026D28;

typedef struct S_80026CE4_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x5E];
    s16 unk_72;
} S_80026CE4_0;   /* temp_v0 in func_80026CE4 */

/* Allocate a type 2 object and initialize its data pointer and value. */
void func_80026CE4(s16 value) {
    S_80026CE4_0 *object;

    object = func_8003FC64(2);
    if (object != NULL) {
        object->unk_10 = &D_80026D28;
        object->unk_72 = value;
    }
}
