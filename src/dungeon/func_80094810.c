#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
void apply_scaled_entity_velocity();                      /* extern */


typedef struct S_80099F70_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x44];
    s32 unk_5C;
} S_80099F70_1;

// Process linked entries with flag 0x4000 until reaching the global sentinel.
void process_unflagged_linked_entries_alt(s32 firstNodeBase) {
    S_80099F70_1 *currentEntry;

    currentEntry = firstNodeBase + 0x20;
    if (currentEntry != ((EntityRec *)(((s32 *)&D_800814A8)))->x.v) {
        do {
            if (currentEntry->unk_14 & 0x4000) {
                apply_scaled_entity_velocity(currentEntry);
            }
            currentEntry = currentEntry->unk_5C + 0x20;
        } while (currentEntry != ((EntityRec *)(((s32 *)&D_800814A8)))->x.v);
    }
}
