#include "common.h"
#include "engine/graphics.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
void register_node_if_unregistered(void *block_data, void *registration_id);                   /* extern */

extern M2C_UNK D_800A7774[3];


/* Decrement the countdown and reset the record data and handler when it expires. */
void decrement_record_timer_and_reset(Rec_func_80094268_arg0 *record) {
    u16 countdown;

    countdown = record->unk_90.as_u16 - 1;
    record->unk_90.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        register_node_if_unregistered(record, project_sprite_chain);
        record->unk_90.as_u16 = 0xAU;
        record->unk_50.as_pm = &D_800A7774[0];
    }
}
