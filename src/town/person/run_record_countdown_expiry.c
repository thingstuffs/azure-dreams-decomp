#include "common.h"
#include "town/person/actor_data_references_g00663.h"
#include "town/person.h"
#include "m2c_compat.h"
#include "shared/town_object.h"

#include "town/person/object_setup.h"
#include "town/person/object.h"


/* Decrement the record's countdown and run its expiry handlers when it reaches zero. */
void run_record_countdown_expiry(TownObjectRecord *record, ObjectPosition *forward_arg_1, void *forward_arg_2) {
    u16 countdown;

    countdown = record->timer.as_u16 - 1;
    record->timer.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        set_linked_data_pointers_variant_1(record, forward_arg_1, forward_arg_2);
        create_owner_following_sprite(record);
        apply_object_setup_and_update(record, forward_arg_1, forward_arg_2);
    }
}
