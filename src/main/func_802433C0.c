/* Relink of matched main/func_80012494; every changed retail word is a paired relocation. */
#define D_8002546C D_80026398
#define cardBootShowCopyingProgress cardBootShowSavingProgress
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025494_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
    s32 unk_50;
} S_80025494_0;   /* arg0 in inventorySetObjectEntryAddress; pointer addresses record offset 0x10 */


extern void cardBootShowSavingProgress(s32, s32);                    /* extern */
extern M2C_UNK D_80026398;

/* Sets two state fields, initializes embedded data, and assigns the record pointer. */
void inventorySetObjectEntryAddress(void *object_data) {
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_4C = 1;
    cardBootShowSavingProgress(object_data - 0x20, object_data + 0x40);
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_50 = 1;
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_00 = &D_80026398;
}
