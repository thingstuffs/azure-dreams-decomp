#include "common.h"

#include "town/player/action_initializers.h"
extern s8 town_action_reset_byte;

/* Initializes the record handler and count, then clears town_action_reset_byte. */
void initialize_record_and_clear_shared_flag(Rec_func_80094268_arg0 *primary_value, struct EntityRec *secondary_value, void *context_value) {
    initialize_record_with_handler_and_count(primary_value, secondary_value, context_value);
    town_action_reset_byte = 0;
}
