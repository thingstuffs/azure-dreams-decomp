#include "common.h"
#include "m2c_compat.h"

typedef struct S_80025494_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x48];
    s32 unk_4C;
    s32 unk_50;
} S_80025494_0;   /* arg0 in cardBootEnterCopyingProgress; pointer addresses record offset 0x10 */


void cardBootShowCopyingProgress();                    /* extern */
extern M2C_UNK D_8002546C;

/* Sets two state fields, initializes embedded data, and assigns the record pointer. */
void cardBootEnterCopyingProgress(void *object_data) {
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_4C = 1;
    cardBootShowCopyingProgress(object_data - 0x20, object_data + 0x40);
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_50 = 1;
    ((S_80025494_0 *)((u8 *)object_data - 0x10))->unk_00 = &D_8002546C;
}
