#include "common.h"
#include "town/player.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"

typedef struct S_8009431C_0 {
    void (*unk_00)(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context);
    u8 pad_04[0x6];
    s16 unk_0A;
} S_8009431C_0;   /* arg0 in initialize_threshold_interaction_action */

/* Initialize the object's data pointer and clear its state field. */
void initialize_threshold_interaction_action(void *record, void *unused_entity, s32 unused_context) {
    S_8009431C_0 *object;

    object = record;
    object->unk_00 = &update_threshold_and_interaction;
    object->unk_0A = 0;
}
