#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

   /* the 0x2 bytes before arg0 in func_800249B8, addressed as arg0[-1] */

   /* arg0 in func_800249B8 */



   /* arg1 in func_800249B8 */



/* Increment the linked counter, reduce the source value by four, and process and flag the target status. */
void func_800249B8(void *entry, B22_818931B8_S_818931B8_2 *source, Rec_D_80082E80 *target) {
    B22_818931B8_S_818931B8_1 *counter_state;

    counter_state = ((B22_818931B8_S_818931B8_0 *)entry)->unk_00;
    counter_state->unk_14 = (u16) (counter_state->unk_14 + 1);
    source->unk_0A = (u16) (source->unk_0A - 4);
    func_800478B8(target);
    if (target->unk_14.at00_u16.v & 0x6000) {
        ((B22_818931B8_S_818931B8_0_pre *)entry)[-1].unk_00 = (u16) (((B22_818931B8_S_818931B8_0_pre *)entry)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
