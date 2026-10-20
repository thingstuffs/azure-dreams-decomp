#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



void copy_three_component_values();                      /* extern */
extern u8 D_80017B30;


/* Pass the callback-selected eight-byte table entry to copy_three_component_values. */
void pass_callback_selected_entry(void) {
    copy_three_component_values((D_80016000->unk_20->callback_2D4(0) * 8) + &D_80017B30);
}
