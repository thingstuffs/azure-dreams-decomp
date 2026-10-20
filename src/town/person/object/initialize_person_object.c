#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
void register_node_if_unregistered(void *block_data, s32 registration_id);                   /* extern */
void configure_the_set_mode_n_1();  /* extern */
void clear_object_status_and_dispatch_target(); /* extern */
void dispatch_object_state();    /* extern */
extern M2C_UNK D_800D5028;


/* Initialize the object and its animation, then dispatch its current state. */
void initialize_person_object(Rec_func_80094268_arg0 *object, s32 context, s32 animation) {
    register_node_if_unregistered(object, project_sprite_chain);
    object->unk_8C = 0x40;
    object->unk_8E = 0x40;
    clear_object_status_and_dispatch_target(object, animation, **object->unk_7C.as_pps32, 0);
    configure_the_set_mode_n_1(object, context, &D_800D5028);
    dispatch_object_state(object, context, animation);
}
