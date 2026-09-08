#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64();                  /* extern */
extern M2C_UNK D_800B328C;

typedef struct S_800B341C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800B341C_0;   /* temp_v0 in func_800B341C */

typedef struct S_800B341C_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x86];
    s16 unk_8E;
} S_800B341C_1;   /* temp_v0_2 in func_800B341C */

/* Allocates and initializes an object when the payload value is nonzero. */
void func_800B341C(s32 allocationKey, s32 payloadValue, s16 payloadShortValue) {
    void *allocatedObject;
    S_800B341C_1 *objectData;

    if (payloadValue != 0) {
        allocatedObject = func_8003FD64(0x210, allocationKey);
        if (allocatedObject != NULL) {
            ((S_800B341C_0 *)allocatedObject)->unk_10 = &D_800B328C;
            objectData = allocatedObject + 0x20;
            ((S_800B341C_0 *)allocatedObject)->unk_20 = allocationKey;
            objectData->unk_04 = payloadValue;
            objectData->unk_8E = payloadShortValue;
        }
    }
}
