#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void initialize_object_entries();          /* extern */
typedef struct S_800C56A8_0 S_800C56A8_0;
void adjust_two_state_values(Rec_func_80094268_arg0 *object, S_800C56A8_0 *state);
extern M2C_UNK D_800D5388;


/* Initialize the actor and set its counter to 40 and its handler. */
void func_800C5864(Rec_func_80094268_arg0 *actor, s32 unused, s32 init_param) {
    initialize_object_entries(actor, init_param, &D_800D5388);
    actor->unk_6C.as_s16 = 0x28;
    actor->unk_54 = &adjust_two_state_values;
}
