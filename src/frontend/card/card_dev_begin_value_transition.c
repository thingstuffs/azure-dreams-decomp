#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

typedef struct S_8001CD7C_0 {
    u8 pad_00[0xA0];
    s32 unk_A0;
    s32 unk_A4;
    s32 unk_A8;
    s32 unk_AC;
} S_8001CD7C_0;   /* arg0 in card_dev_begin_value_transition */

/* Saves and replaces the object's value, setting its control fields to 0 and 3. */
void card_dev_begin_value_transition(S_8001CD7C_0 *object, s32 new_value) {
    s32 previous_value;

    if (object != NULL) {
        previous_value = object->unk_A8;
        object->unk_A4 = 0;
        object->unk_A0 = 3;
        object->unk_A8 = new_value;
        object->unk_AC = previous_value;
    }
}
