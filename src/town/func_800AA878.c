#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

M2C_UNK func_80033CD8();           /* extern */
s32 lookupItemCategoryMappedValue();                /* extern */
void *townCreateTownEffectObject(); /* extern */
void townUpdateLinkedPartPosition();         /* extern */
extern M2C_UNK D_800A8070;

typedef struct S_800A7FD8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_800A7FD8_0;

typedef struct S_800A7FD8_1 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_800A7FD8_1;

typedef struct S_800A7FD8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800A7FD8_2;

/* present_flower_set: create a flower gift object and initialize its state and callback data. */
void present_flower_set(s32 initial_value) {
    s32 callback_arg;
    S_800A7FD8_1 *state;
    S_800A7FD8_2 *callback_data;
    void *object;

    object = townCreateTownEffectObject(0, 0, &D_800A8070, 0);
    if (object != NULL) {
        callback_arg = ((S_800A7FD8_0 *)object)->unk_08;
        callback_data = ((S_800A7FD8_0 *)object)->unk_0C;
        state = object + 0x20;
        state->unk_60 = initial_value;
        callback_data->unk_08 = lookupItemCategoryMappedValue(0xB, 2);
        func_80033CD8(state, func_80045340);
        townUpdateLinkedPartPosition(state, callback_arg, callback_data);
    }
}
