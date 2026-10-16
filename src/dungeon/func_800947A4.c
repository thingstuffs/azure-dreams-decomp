#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

void dungeonApplyScaledEntityVelocity();                      /* extern */


typedef struct S_80099F04_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_80099F04_1;   /* var_s0 in dungeonProcessUnflaggedLinkedEntries */

/* Walk the linked entries and process those without flag 0x4000. */
void dungeonProcessUnflaggedLinkedEntries(s32 firstEntryBase) {
    S_80099F04_1 *entry;

    entry = firstEntryBase + 0x20;
    if (entry != ((EntityRec *)(((M2C_UNK *)&D_800814A8)))->x.v) {
        do {
            if (!(entry->unk_14 & 0x4000)) {
                dungeonApplyScaledEntityVelocity(entry);
            }
            entry = entry->unk_5C + 0x20;
        } while (entry != ((EntityRec *)(((M2C_UNK *)&D_800814A8)))->x.v);
    }
}
