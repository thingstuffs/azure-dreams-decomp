#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/event.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene/motion.h"

extern s8 D_80018EBC[];
extern s32 scene_state_dispatch_context;

/* Selects a table entry from flag 0xFCB or callback 4 and passes it to func_800182E4. */
void select_event_table_entry(s32 forwarded_first, s32 unused, s32 forwarded_last)
{
    s32 entry_index;

    if (get_script_flag_mask(F_cheriru_first_cheriru) != 0) {
        entry_index = 8;
    } else {
        entry_index = ((*(s32 (**)(s32))((s8 *)((void *)(town_scene_root->services))
            + 0x54))(4) & 3) * 2;
    }
    apply_entry_position(D_80018EBC + (entry_index * 8), &scene_state_dispatch_context, forwarded_first, forwarded_last);
}
