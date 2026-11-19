#include "common.h"
#include "frontend/libcard/paired_choice.h"

#include "frontend/libcard/interfaces.h"
#include "frontend/libcard.h"


/* Store the initial value, link embedded data, and update the record. */
void card_boot_initialize_paired_choice_panel(CardChoiceOwner *record, struct ObjectNodeHeader *owner) {
    record->owner = owner;
    init_card_choice_templates(&record->display, &record->display_block, &record->display_vector);
    card_boot_initialize_paired_choice_layout(record);
}
