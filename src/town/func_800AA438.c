#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();           /* extern */
void *func_8009C390();       /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A7C0C;

typedef struct S_800A7B98_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800A7B98_0;   /* temp_v0 in func_800A7B98 */

typedef struct S_800A7B98_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800A7B98_1;   /* temp_v1 in func_800A7B98 */

typedef struct S_800A7B98_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800A7B98_2;   /* arg2 in func_800A7B98 */

typedef struct S_800A7B98_3 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800A7B98_3;   /* temp_s0 in func_800A7B98 */

/* Creates an object, copies its source data fields, and initializes its state. */
void func_800A7B98(s32 ownerDataAddress, M2C_UNK creationParam, S_800A7B98_2 *sourceData) {
    S_800A7B98_3 *objectState;
    void *createdObject;
    S_800A7B98_1 *objectData;

    createdObject = func_8009C390(ownerDataAddress - 0x20, creationParam, &D_800A7C0C, 0);
    objectState = createdObject + 0x20;
    if (createdObject != NULL) {
        objectData = ((S_800A7B98_0 *)createdObject)->unk_0C;
        objectData->unk_08 = (s32) sourceData->unk_08;
        objectData->unk_14 = (u16) sourceData->unk_14;
        func_80033CD8(objectState, &D_80045340);
        objectState->unk_6C = 5;
    }
}
