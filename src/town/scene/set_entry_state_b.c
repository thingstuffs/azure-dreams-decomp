#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

/* Eight-byte entries selected by the town root's current index. */
typedef struct TownEntryStatus {
    u8 pad_00[4];
    s8 state;
    u8 pad_05[3];
} TownEntryStatus;

void set_selected_entry_state_2(void) {
    Rec_D_80016000 *context;

    context = town_scene_root;
    ((TownEntryStatus *)((context->entry_index * 8) + (s32)context->event_data))->state = 2;
}
