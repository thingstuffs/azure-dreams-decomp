#include "common.h"
#include "shared/town_event_buffer.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



void process_flagged_type_0x18_entries();                            /* extern */
void call_value_handler_mode_0();                   /* extern */
extern s32 D_8001B210;

/* Refresh the shared state and subtract D_8001B210 from the context counter. */
void refresh_shared_state(void) {
    TownStateRecord *context;

    process_flagged_type_0x18_entries();
    call_value_handler_mode_0(D_8001B218);
    context = D_80016000->unk_38;
    context->unk_2D5C = (s32) (((signed int)context->unk_2D5C) - D_8001B210);
}
