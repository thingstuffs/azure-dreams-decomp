#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
typedef struct S_800C56A8_0 S_800C56A8_0;
void adjust_two_state_values(Rec_func_80094268_arg0 *object, S_800C56A8_0 *state);
extern s32 D_800D5388[];


/* Initialize the actor and set its counter to 40 and its handler. */
void initialize_two_value_adjustment_action(Rec_func_80094268_arg0 *actor, s32 unused, void *init_param) {
    initialize_object_entries((Struct800C5724 *)(actor), init_param, &D_800D5388);
    actor->unk_6C.as_s16 = 0x28;
    actor->unk_54 = &adjust_two_state_values;
}
