#include "shared/town_root.h"
#include "common.h"
#include "shared/record_ptrs.h"

typedef struct TownEntry {
    s8 pad0[4];
    u8 state;
    u8 pad5[3];
} TownEntry;

extern s32 scene_cell_dispatch_code[];

extern void func_80017E1C(void);
extern s32 func_80018504(void);

/* Updates the current town entry and clears its state on a nonzero result or global state 1. */
s32 update_entry_state_and_clear(void)
{
    s32 update_result;
    u8 entry_state;

    update_result = 0;
    entry_state = ((TownEntry *)town_scene_root->event_data)[town_scene_root->entry_index].state;
    scene_cell_dispatch_code[0] = entry_state;
    if (entry_state != 2) {
        update_result = func_80018504();
    }
    if ((update_result != 0) || (func_80017E1C(), scene_cell_dispatch_code[0] == 1)) {
        ((TownEntry *)town_scene_root->event_data)[town_scene_root->entry_index].state = 0;
        scene_cell_dispatch_code[0] = 0;
    }
    return update_result;
}
