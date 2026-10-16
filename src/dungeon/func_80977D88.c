#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80173588_0 {
    u8 pad_00[0xA2];
    s16 unk_A2;
} S_80173588_0;   /* arg0 in dungeonResetStateFieldA2 */


s32 dungeonUpdateActorHopAndShrink(S_80173588_0 *, void *, void *);
/* Call dungeonUpdateActorHopAndShrink and clear the state field at offset 0xA2. */
void dungeonResetStateFieldA2(S_80173588_0 *state, void *context, void *data) {
    dungeonUpdateActorHopAndShrink(state, context, data);
    state->unk_A2 = 0;
}
