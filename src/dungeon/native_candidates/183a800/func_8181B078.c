#include "modules/dungeon_ovl_183a800.h"
#include "common.h"
#include "shared/object_flags.h"

   /* the 0x2 bytes before arg0 in func_8181B078, addressed as arg0[-1] */

   /* arg0 in func_8181B078 */

   /* arg1 in func_8181B078 */

   /* arg2 in func_8181B078 */




/* Advances the object cycle and position, flagging expiry or a flagged source. */
void func_80024878(void *object, S_8181B078_1 *position, S_8181B078_2 *source)
{
    s32 one;
    s16 phase;

    D_80025914 = 1;
    ((S_8181B078_0 *)object)->unk_02.s--;

    if (++((S_8181B078_0 *)object)->unk_1C >= 2) {
        ((S_8181B078_0 *)object)->unk_1C = 0;
        phase = ((S_8181B078_0 *)object)->unk_1E;
        one = 1;

        switch (phase) {
        case 0:
            ((S_8181B078_0 *)object)->unk_1E = one;
            ((S_8181B078_0 *)object)->unk_28 += 8;
            break;
        case 1:
            ((S_8181B078_0 *)object)->unk_1E = 2;
            ((S_8181B078_0 *)object)->unk_28 += 8;
            break;
        case 2:
            ((S_8181B078_0 *)object)->unk_1E = 0;
            ((S_8181B078_0 *)object)->unk_28 -= 16;
            break;
        }
    }

    position->unk_08 += ((S_8181B078_0 *)object)->unk_60;

    if (((S_8181B078_0 *)object)->unk_02.u <= 0) {
        ((S_8181B078_0_pre *)object)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }

    if (source->unk_14 & 0x8000) {
        ((S_8181B078_0_pre *)object)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
