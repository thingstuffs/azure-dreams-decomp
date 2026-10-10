#include "modules/dungeon_ovl_198a800.h"
#include "common.h"
#include "shared/object_flags.h"

   /* the 0x2 bytes before arg0 in func_8196BF24, addressed as arg0[-1] */

   /* arg0 in func_8196BF24 */

   /* arg2 in func_8196BF24 */


/* Advance the effect animation and flag completion when its countdown expires. */
void func_80025724(void *effect, s32 unused, S_8196BF24_1 *transform) {
    u8 next_u;

    ((S_8196BF24_0 *)effect)->unk_2C.s = (s16)(((S_8196BF24_0 *)effect)->unk_2C.s - 1);
    transform->unk_1C = (u16)(transform->unk_1C - 0x300);
    transform->unk_1E = (u16)(transform->unk_1E - 0x200);
    next_u = ((S_8196BF24_0 *)effect)->unk_40 - 0x18;
    ((S_8196BF24_0 *)effect)->unk_40 = next_u;
    if ((next_u & 0xFF) == 0xE8) {
        ((S_8196BF24_0 *)effect)->unk_40 = 0x18U;
        ((S_8196BF24_0 *)effect)->unk_41 = (u8)(((S_8196BF24_0 *)effect)->unk_41 - 0x20);
    }
    if (((S_8196BF24_0 *)effect)->unk_2C.u <= 0) {
        ((S_8196BF24_0_pre *)effect)[-1].unk_00 = (u16)(((S_8196BF24_0_pre *)effect)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = (s32)(objectFlagBlock.flags | 0x8000);
    }
}
