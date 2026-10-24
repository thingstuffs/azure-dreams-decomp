#include "common.h"
#include "m2c_compat.h"

#include "frontend/libcard/interfaces.h"
#include "main/data.h"
#include "frontend/libcard.h"

/* Update the record using the two shared data addresses. */
void card_boot_initialize_paired_choice_layout(void *record_addr) {
    card_boot_layout_left_right_labels(record_addr);
    set_entry_destination_and_value(record_addr);
    card_boot_set_paired_choice_animations(record_addr, D_8002807C, D_80028084);
    card_boot_refresh_paired_choice_labels(record_addr);
}
