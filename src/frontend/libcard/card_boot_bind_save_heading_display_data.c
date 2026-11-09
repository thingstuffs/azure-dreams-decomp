#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"
#include "frontend/libcard/save_heading.h"
#include "frontend/libcard.h"

extern M2C_UNK D_80077EF0;
extern M2C_UNK D_80077EFC;


/* Populate output pointers with shared data and embedded record addresses. */
void card_boot_bind_save_heading_display_data(CardSaveHeadingDisplayPrefix *record_arg) {
    CardSaveHeadingDisplayPrefix *record = record_arg;

    record->left->payload.data = &D_80077EF0;
    record->right->payload.data = &D_80077EFC;
    record->value->payload.data = record_arg->value_text;
    record->heading->payload.data = record_arg->heading_text;
}
