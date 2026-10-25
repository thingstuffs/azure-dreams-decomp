#include "common.h"
#include "m2c_compat.h"

extern void town_interaction_action_address();

typedef struct S_800946FC_0 {
    void (*unk_00)();
    u8 pad_04[0x6];
    s16 unk_0A;
} S_800946FC_0;   /* arg0 in initialize_actor_interaction_state_19 */

/* Initializes the object's data pointer and sets its initial value to 0x13. */
void initialize_actor_interaction_state_19(S_800946FC_0 *object) {
    object->unk_00 = &town_interaction_action_address;
    object->unk_0A = 0x13;
}
