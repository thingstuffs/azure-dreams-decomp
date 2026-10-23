#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D6FBC;

typedef struct S_800CCC34_0 {
    u8 pad_00[0x68];
    s16 unk_68;
} S_800CCC34_0;   /* arg0 in invoke_flag_state_callback */

/* Invoke the callback selected by the object state. */
void invoke_flag_state_callback(S_800CCC34_0 *object, s32 context, void *motion) {
    ((void (*)(S_800CCC34_0 *, s32, void *)) (*(s32 *)((u8 *)&D_800D6FBC + ((object->unk_68) * 4))))(object, context, motion);
}