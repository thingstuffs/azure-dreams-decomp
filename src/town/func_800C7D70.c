#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"

extern s32 D_800C53F8;

typedef struct S_800C54D0_0 {
    u8 pad_00[0x54];
    s32 * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x8];
    s16 unk_6C;
} S_800C54D0_0;   /* arg0 in func_800C54D0 */

/* Clear the actor table flag, install its handler, and set its counter to 10. */
void func_800C54D0(S_800C54D0_0 *actor) {
    D_80082660[actor->unk_60].unk_00 = 0;
    actor->unk_54 = &D_800C53F8;
    actor->unk_6C = 0xA;
}
