#include "common.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_800CB708_0 S_800CB708_0;

#include "town/person/object_setup.h"
#include "town/person.h"
#include "town/person/object.h"
void assign_object_data_pointers(S_800CB708_0 *object);

/* Decrement the entity countdown and run its completion handlers when it expires. */
void update_entity_countdown_completion(Rec_func_80094268_arg0 *entity, void *update_context, void *setup_context) {
    u16 countdown;

    countdown = entity->unk_6C.as_u16 - 1;
    entity->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        assign_object_data_pointers(entity);
        create_and_invoke_render_object((s32)(entity), entity->unk_96.as_u8);
        apply_object_setup_and_update(entity, update_context, setup_context);
    }
}
