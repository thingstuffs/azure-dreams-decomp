#include "shared/town_root.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_event_state.h"

typedef struct S_800195B8_0 {
    s32 unk_00;
} S_800195B8_0;





typedef struct S_800195B8_3 {
    u8 pad_00[0x6000];
    void * unk_6000;
} S_800195B8_3;

typedef struct S_800195B8_5 {
    u8 pad_00[0x168];
    void (*unk_168)(s32 *, s32 *, s32);
    u8 pad_16C[0x8];
    void (*unk_174)(s32);
} S_800195B8_5;

extern s32 D_80016064[];
extern s32 D_8001608C[];

/* Find the index of an entry by ID, reporting an error if it is missing. */
s32 find_entry_28_index_or_assert(void *entries, s32 entry_id) {
    s32 entry_index;

    for (entry_index = 0; ((TownEventEntryValueView *)(((entry_index * 0x1C) + entries)))->value != 0; entry_index++) {
        if (((S_800195B8_0 *)((((entry_index * 8) - entry_index) * 4) + entries))->unk_00 == entry_id) {
            break;
        }
    }

    if (((TownEventEntryValueView *)(((((entry_index * 8) - entry_index) * 4) + entries)))->value == 0) {
        u8 *page = (u8 *)0x80010000;
        void (*report_missing)(s32 *, s32 *, s32);
        report_missing = ((S_800195B8_5 *)(((Rec_D_80016000 *)(((S_800195B8_3 *)page)->unk_6000))->services))->unk_168;
        report_missing(&D_80016064, &D_8001608C, 0x37);
        ((S_800195B8_5 *)(((Rec_D_80016000 *)(((S_800195B8_3 *)page)->unk_6000))->services))->unk_174(1);
    }
    return entry_index;
}
