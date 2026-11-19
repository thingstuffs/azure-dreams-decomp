#include "common.h"
#include "frontend/libcard/paired_choice.h"
#include "m2c_compat.h"

#include "frontend/libcard/interfaces.h"
#include "main/data.h"
#include "frontend/libcard.h"

/* Update the record using the two shared data addresses. */
void card_boot_initialize_paired_choice_layout(CardChoiceOwner *state) {
    card_boot_layout_left_right_labels(state);
    position_paired_choice_items(state);
    card_boot_set_paired_choice_animations(state, D_8002807C, D_80028084);
    card_boot_refresh_paired_choice_labels(state);
}
