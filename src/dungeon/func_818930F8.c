#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

   /* the 0x2 bytes before arg0 in func_800248F8, addressed as arg0[-1] */

   /* arg0 in func_800248F8 */





/* Advance the object counters, apply the initial frame offset, and flag completion. */
void func_800248F8(void *state, M2C_UNK draw_context, M2C_UNK update_context) {
    s16 frame;
    B22_818930F8_S_818930F8_1 *object;

    object = ((B22_818930F8_S_818930F8_0 *)state)->unk_00;
    object->unk_14 = (u16) (object->unk_14 + 1);
    ((B22_818930F8_S_818930F8_0 *)state)->unk_04 = (u16) (((B22_818930F8_S_818930F8_0 *)state)->unk_04 + 1);
    func_800478B8(update_context);
    frame = (s16) ((B22_818930F8_S_818930F8_0 *)state)->unk_04;
    if (frame < 5) {
        func_80024824(((B22_818930F8_S_818930F8_0 *)state)->unk_00, draw_context, 8, (s16) ((frame * 0x10) - 0x40));
    }
    if ((s16) ((B22_818930F8_S_818930F8_0 *)state)->unk_04 > ((B22_818930F8_S_818930F8_0 *)state)->unk_06) {
        ((B22_818930F8_S_818930F8_0_pre *)state)[-1].unk_00 = (u16) (((B22_818930F8_S_818930F8_0_pre *)state)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
