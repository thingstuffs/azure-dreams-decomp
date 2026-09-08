#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"

M2C_UNK func_80099EA4();                      /* extern */
extern M2C_UNK D_800814A8;


typedef struct S_80099F70_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_80099F70_1;   /* var_s0 in func_80099F70 */

// Process linked entries with flag 0x4000 until reaching the global sentinel.
void func_80099F70(s32 firstNodeBase) {
    S_80099F70_1 *currentEntry;

    currentEntry = firstNodeBase + 0x20;
    if (currentEntry != ((Rec_D_800814A8 *)(&D_800814A8))->unk_00.as_s32) {
        do {
            if (currentEntry->unk_14 & 0x4000) {
                func_80099EA4(currentEntry);
            }
            currentEntry = currentEntry->unk_5C + 0x20;
        } while (currentEntry != ((Rec_D_800814A8 *)(&D_800814A8))->unk_00.as_s32);
    }
}
