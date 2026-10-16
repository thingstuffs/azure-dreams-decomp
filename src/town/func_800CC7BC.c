#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
/* extern */

typedef struct S_800C9F1C_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
} S_800C9F1C_0;   /* arg0 in townDecrementReactionTimerAndUpdate */


void townApplyObjectSetupAndUpdate(S_800C9F1C_0 *, M2C_UNK, M2C_UNK);
/* Decrement the object countdown and call townApplyObjectSetupAndUpdate when it expires. */
void townDecrementReactionTimerAndUpdate(S_800C9F1C_0 *object, M2C_UNK param_1, M2C_UNK param_2) {
    u16 countdown;

    countdown = object->unk_6C - 1;
    object->unk_6C = countdown;
    if ((countdown << 0x10) <= 0) {
        townApplyObjectSetupAndUpdate(object, param_1, param_2);
    }
}
