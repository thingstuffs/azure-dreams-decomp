#include "common.h"
#include "town/person/actor_data_references_g00663.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object_setup.h"
void * create_owner_following_sprite(s32);                      /* extern */


/* Decrement the record's countdown and run its expiry handlers when it reaches zero. */
void run_record_countdown_expiry(Rec_func_80094268_arg0 *record, void *forward_arg_1, void *forward_arg_2) {
    u16 countdown;

    countdown = record->unk_6C.as_u16 - 1;
    record->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        set_linked_data_pointers_variant_1(record, forward_arg_1, forward_arg_2);
        create_owner_following_sprite((s32)(record));
        apply_object_setup_and_update(record, forward_arg_1, forward_arg_2);
    }
}
