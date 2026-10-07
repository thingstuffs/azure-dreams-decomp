#include "shared/town_root.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef void (*Callback3)(M2C_UNK *, M2C_UNK *, M2C_UNK);

typedef struct S_800194E4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800194E4_0;

typedef struct S_800194E4_1 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
} S_800194E4_1;

extern s8 D_80010000[];
extern M2C_UNK D_80016064;
extern M2C_UNK D_8001608C;

/* Finds an entry by ID and invokes error callbacks if it is missing. */
s32 func_800194E4(void *entries, s32 entry_id) {
    s32 entry_index;
    Callback3 report_error;
    Rec_D_80016000 *root;
    TownServiceTable *callbacks;

    entry_index = 0;
    if (((S_800194E4_0 *)entries)->unk_04 != 0) {
        while (1) {
            if (((S_800194E4_1 *)((s8 *)entries + entry_index * 8))->unk_00 == entry_id) {
                break;
            }
            entry_index += 1;
            if (((S_800194E4_1 *)((s8 *)entries + entry_index * 8))->unk_04 == 0) {
                break;
            }
        }
        if (((S_800194E4_1 *)((s8 *)entries + entry_index * 8))->unk_04 != 0) {
            return entry_index;
        }
    }
    root = (*(void **)((u8 *)D_80010000 + 0x6000));
    callbacks = root->unk_20;
    report_error = ((Callback3)callbacks->callback_168);
    report_error(&D_80016064, &D_8001608C, 0x28);
    ((M2C_UNK (*)(M2C_UNK))((TownServiceTable *)(((Rec_D_80016000 *)((*(void **)((u8 *)D_80010000 + 0x6000))))->unk_20))->callback_174)(1);
    return entry_index;
}
