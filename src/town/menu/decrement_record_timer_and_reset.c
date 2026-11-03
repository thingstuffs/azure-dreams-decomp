#include "common.h"
#include "engine/graphics.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "engine/node.h"
#include "town/menu.h"
#include "town/menu/effect.h"




/* Decrement the countdown and reset the record data and handler when it expires. */
void decrement_record_timer_and_reset(TownObjectRecord *record) {
    u16 countdown;

    countdown = record->unk_90.as_u16 - 1;
    record->unk_90.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        register_node_if_unregistered(record, project_sprite_chain);
        record->unk_90.as_u16 = 0xAU;
        record->unk_50.as_pm = decrement_effect_timer_and_switch;
    }
}
