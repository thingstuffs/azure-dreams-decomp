#include "modules/dungeon_engine_dungeon_util_fragment_c0bec.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void display_formatted_context_message();                   /* extern */
extern M2C_UNK D_800E092B;

/* Passes D_800E092B to display_formatted_context_message by address. */
void display_fixed_item_action_message(void) {
    display_formatted_context_message(&D_800E092B);
}
