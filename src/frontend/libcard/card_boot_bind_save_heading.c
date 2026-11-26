#include "common.h"
#include "shared/resident_resources.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"
#include "frontend/libcard/save_heading.h"
#include "frontend/libcard.h"



/* Populate output pointers with shared data and embedded record addresses. */
void card_boot_bind_save_heading(CardSaveHeadingDisplayPrefix *record_arg) {
    CardSaveHeadingDisplayPrefix *record = record_arg;

    record->left->payload.data = cached_selection_row_left_template;
    record->right->payload.data = cached_selection_row_middle_template;
    record->value->payload.data = record_arg->value_text;
    record->heading->payload.data = record_arg->heading_text;
}
