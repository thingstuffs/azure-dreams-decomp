#include "common.h"
#include "m2c_compat.h"

typedef struct S_801253EC_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
} S_801253EC_0;   /* arg0 in func_801253EC */

/* Advance the counter and switch to state one when the limit is reached. */
void func_801253EC(S_801253EC_0 *controller) {
    u16 next_count;

    next_count = controller->unk_04 + 1;
    controller->unk_04 = next_count;
    if ((s16) next_count == controller->unk_06) {
        controller->unk_0A = 1;
        controller->unk_06 = 0;
        controller->unk_04 = 0U;
    }
}
