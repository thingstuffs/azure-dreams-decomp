#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();           /* extern */
s32 lookupItemCategoryMappedValue();                          /* extern */
void *townCreateTownEffectObject(); /* extern */
void townCopyAdjustedVectorOrFlagObject();         /* extern */
extern M2C_UNK D_8006E240;
extern M2C_UNK D_800A8248;

typedef struct S_800A8184_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_800A8184_0;

typedef struct S_800A8184_1 {
    u8 pad_00[0x4C];
    u8 unk_4C;
    u8 unk_4D;
} S_800A8184_1;

typedef struct S_800A8184_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A8184_2;

/* Creates an object, selects its data, and initializes its state. */
void townCreateIndexedEffectObject(s32 index, s32 kind) {
    s32 object_id;
    S_800A8184_1 *state;
    S_800A8184_2 *data;
    void *object;
    s32 saved_kind = kind;

    object = townCreateTownEffectObject(0, 0, &D_800A8248, 0);
    state = object + 0x20;
    if (object != NULL) {
        object_id = ((S_800A8184_0 *)object)->unk_08;
        data = ((S_800A8184_0 *)object)->unk_0C;
        state->unk_4C = index;
        state->unk_4D = saved_kind;
        {
            s32 dispatch_result;

            if ((saved_kind & 0xFF) == 0x12) {
                dispatch_result = (s32)&D_8006E240;
            } else {
                dispatch_result = lookupItemCategoryMappedValue(state->unk_4D, state->unk_4C);
            }
            data->unk_08 = dispatch_result;
        }
        func_80033CD8(state, func_80045340);
        townCopyAdjustedVectorOrFlagObject(state, object_id, data);
    }
}
