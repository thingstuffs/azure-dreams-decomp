#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B683C_arg0.h"


typedef struct S_800B683C_2 {
    u8 pad_00[0x5C];
    void ** unk_5C;
} S_800B683C_2;   /* ((Rec_func_800B683C_arg0 *)arg0)->unk_98 in func_800B683C */




M2C_UNK func_800B6580();


/* Clears two linked values and initializes the object's embedded data. */
void func_800B683C(void *object) {
    s32 *linkedValue;
    s32 slotIndex;

    slotIndex = 0x14;
    do {
        linkedValue = *(s32 **)((slotIndex * 4) + ((Rec_func_800B683C_arg0 *)object)->unk_98);
        slotIndex += 1;
        *linkedValue = 0;
    } while (slotIndex < 0x16);
    *((S_800B683C_2 *)(((Rec_func_800B683C_arg0 *)object)->unk_98))->unk_5C = object + 0x18;
    func_800B6580(*((S_800B683C_2 *)(((Rec_func_800B683C_arg0 *)object)->unk_98))->unk_5C, 0);
}
