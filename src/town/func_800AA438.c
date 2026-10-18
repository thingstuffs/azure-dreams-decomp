#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

void func_80033CD8(void *block_data, s32 registration_id);
void *create_town_effect_object();       /* extern */
extern M2C_UNK D_800A7C0C;

typedef struct S_800A7B98_0 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_800A7B98_0;

typedef struct S_800A7B98_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800A7B98_1;

typedef struct S_800A7B98_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800A7B98_2;   /* arg2 in create_timed_effect_object */

typedef struct S_800A7B98_3 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800A7B98_3;

/* Creates an object, copies its source data fields, and initializes its state. */
void create_timed_effect_object(s32 ownerDataAddress, s32 creationParam, S_800A7B98_2 *sourceData) {
    S_800A7B98_3 *objectState;
    void *createdObject;
    S_800A7B98_1 *objectData;

    createdObject = create_town_effect_object(ownerDataAddress - 0x20, creationParam, &D_800A7C0C, 0);
    objectState = createdObject + 0x20;
    if (createdObject != NULL) {
        objectData = ((S_800A7B98_0 *)createdObject)->unk_0C;
        objectData->unk_08 = (s32) sourceData->unk_08;
        objectData->unk_14 = (u16) sourceData->unk_14;
        func_80033CD8(objectState, func_80045340);
        objectState->unk_6C = 5;
    }
}
