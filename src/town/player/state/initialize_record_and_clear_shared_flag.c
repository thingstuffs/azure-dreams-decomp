#include "common.h"

extern void initialize_record_with_handler_and_count(s32 record, s32 setup_value, s32 context_value);
extern s8 town_action_reset_byte;

/* Initializes the record handler and count, then clears town_action_reset_byte. */
void initialize_record_and_clear_shared_flag(s32 primary_value, s32 secondary_value, s32 context_value) {
    initialize_record_with_handler_and_count(primary_value, secondary_value, context_value);
    town_action_reset_byte = 0;
}
