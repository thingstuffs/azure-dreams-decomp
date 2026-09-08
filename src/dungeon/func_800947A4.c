#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800814A8.h"

M2C_UNK func_80099EA4();                      /* extern */
extern M2C_UNK D_800814A8;


typedef struct S_80099F04_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_80099F04_1;   /* var_s0 in func_80099F04 */

/* Walk the linked entries and process those without flag 0x4000. */
void func_80099F04(s32 firstEntryBase) {
    S_80099F04_1 *entry;

    entry = firstEntryBase + 0x20;
    if (entry != ((Rec_D_800814A8 *)(&D_800814A8))->unk_00.as_s32) {
        do {
            if (!(entry->unk_14 & 0x4000)) {
                func_80099EA4(entry);
            }
            entry = entry->unk_5C + 0x20;
        } while (entry != ((Rec_D_800814A8 *)(&D_800814A8))->unk_00.as_s32);
    }
}
