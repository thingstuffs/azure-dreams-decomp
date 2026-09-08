#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800395F0_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
    u8 pad_20[0x5C];
    s32 * unk_7C;
} S_800395F0_0;   /* arg0 in func_800395F0 */

typedef struct S_800395F0_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800395F0_1;   /* temp_a2 in func_800395F0 */


/* Push the event-script return address and jump to the encoded destination. */
void func_800395F0(S_800395F0_0 *script) {
    S_800395F0_1 *target_bytes;

    *script->unk_7C = script->unk_1C + 4;
    target_bytes = script->unk_1C;
    script->unk_7C = (s32 *) (script->unk_7C + 1);
    script->unk_1C = (void *) (target_bytes->unk_00 + (target_bytes->unk_01 << 8) + (target_bytes->unk_02 << 0x10) + (target_bytes->unk_03 << 0x18));
}
