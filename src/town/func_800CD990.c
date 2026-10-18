#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void apply_object_setup_and_update();    /* extern */
M2C_UNK assign_object_data_pointers(Rec_func_80094268_arg0 *);                            /* extern */
s32 create_and_invoke_render_object();                  /* extern */


/* Decrement the entity countdown and run its completion handlers when it expires. */
void update_entity_countdown_completion(Rec_func_80094268_arg0 *entity, s32 completion_arg1, s32 completion_arg2) {
    u16 countdown;

    countdown = entity->unk_6C.as_u16 - 1;
    entity->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        assign_object_data_pointers(entity);
        create_and_invoke_render_object(entity, entity->unk_96.as_u8);
        apply_object_setup_and_update(entity, completion_arg1, completion_arg2);
    }
}
