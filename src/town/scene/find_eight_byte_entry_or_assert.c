#include "shared/town_root.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"

typedef void (*Callback3)(s32 *, s32 *, s32);

extern u8 D_80010000[];
extern s32 D_80016064[];
extern s32 D_8001608C[];

/* Finds an entry by ID and invokes error callbacks if it is missing. */
s32 find_eight_byte_entry_or_assert(ScenePositionEntry *entries, s32 entry_id) {
    s32 entry_index;
    Callback3 report_error;
    Rec_D_80016000 *root;
    TownServiceTable *callbacks;

    entry_index = 0;
    if (entries[0].result != 0) {
        while (1) {
            if (entries[entry_index].id == entry_id) {
                break;
            }
            entry_index += 1;
            if (entries[entry_index].result == 0) {
                break;
            }
        }
        if (entries[entry_index].result != 0) {
            return entry_index;
        }
    }
    root = (*(void **)((u8 *)D_80010000 + 0x6000));
    callbacks = root->services;
    report_error = ((Callback3)callbacks->callback_168);
    report_error(D_80016064, D_8001608C, 0x28);
    ((s32 (*)(s32))(((Rec_D_80016000 *)((*(void **)((u8 *)D_80010000 + 0x6000))))->services)->callback_174)(1);
    return entry_index;
}
