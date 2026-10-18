#include "common.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
void update_threshold_and_interaction(Rec_func_80094268_arg0 *state, EntityRec *entity, s32 context);

typedef struct S_8009431C_0 {
    s32 * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
} S_8009431C_0;   /* arg0 in initialize_threshold_interaction_action */

/* Initialize the object's data pointer and clear its state field. */
void initialize_threshold_interaction_action(S_8009431C_0 *object) {
    object->unk_00 = &update_threshold_and_interaction;
    object->unk_0A = 0;
}
