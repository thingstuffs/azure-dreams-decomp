#include "script_symbols.h"
#include "common.h"
#include "town/scene/entry_requests.h"
#include "shared/record_ptrs.h"
#include "town/scene/resource.h"

typedef struct TownRecord {
    s8 pad0[8];
    s32 index;
    s8 padC[0x34];
    u8 *entries;
} TownRecord;

extern void func_80017E1C(void);
extern s32 func_80018618(void *object, s32 entry_index);
extern s32 func_800194D8(s32);
extern s32 scene_cell_dispatch_code;

/* Loads the current entry's value, conditionally clears it, and handles the follow-up check. */
s32 load_entry_value_and_handle_followup(void *object, s32 entry_index) {
    TownRecord *record;

    record = *(TownRecord **)((s8 *)(&town_scene_root));
    scene_cell_dispatch_code = record->entries[(record->index * 8) + 4];
    if (func_80018618(object, entry_index) != 0) {
        TownRecord *clear_record;

        clear_record = *(TownRecord **)((s8 *)(&town_scene_root));
        clear_record->entries[(clear_record->index * 8) + 4] = 0;
        scene_cell_dispatch_code = 0;
    }
    if (func_800194D8(F_sbs14_pad20) == 0) {
        func_80017E1C();
    }
    return 0;
}
