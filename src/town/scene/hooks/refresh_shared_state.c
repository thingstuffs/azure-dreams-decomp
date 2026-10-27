#include "common.h"
#include "shared/town_event_buffer.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/value_handler_modes_g00712.h"



void process_flagged_type_0x18_entries(void);                            /* extern */
extern s32 scene_price;

/* Refresh the shared state and subtract D_8001B210 from the context counter. */
void refresh_shared_state(void) {
    TownStateRecord *context;

    process_flagged_type_0x18_entries();
    call_value_handler_mode_0(town_event_records);
    context = town_scene_root->town_state;
    context->money = (s32) (((signed int)context->money) - scene_price);
}
