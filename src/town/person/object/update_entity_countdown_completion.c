#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_800CB708_0 S_800CB708_0;

void apply_object_setup_and_update(void *, s32, s32);    /* extern */
void assign_object_data_pointers(S_800CB708_0 *object);
s32 create_and_invoke_render_object(s32, s32);                  /* extern */


/* Decrement the entity countdown and run its completion handlers when it expires. */
void update_entity_countdown_completion(Rec_func_80094268_arg0 *entity, s32 completion_arg1, s32 completion_arg2) {
    u16 countdown;

    countdown = entity->unk_6C.as_u16 - 1;
    entity->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        assign_object_data_pointers(entity);
        create_and_invoke_render_object((s32)(entity), entity->unk_96.as_u8);
        apply_object_setup_and_update(entity, completion_arg1, completion_arg2);
    }
}
