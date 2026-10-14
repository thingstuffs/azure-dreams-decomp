#include "modules/dungeon_ovl_18d6800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

   /* the 0x2 bytes before arg0 in func_800240B8, addressed as arg0[-1] */

   /* arg0 in func_800240B8 */

   /* temp_v1 in func_800240B8 */

   /* arg1 in func_800240B8 */




/* Increment counters, reduce the stored value, and propagate status flags. */
void func_800240B8(void *counter_state, B28_818B68B8_S_818B68B8_2 *value_state, Rec_D_80082E80 *status) {
    B28_818B68B8_S_818B68B8_1 *linked_counter;

    linked_counter = ((B28_818B68B8_S_818B68B8_0 *)counter_state)->unk_00;
    linked_counter->unk_14 = (u16) (linked_counter->unk_14 + 1);
    ((B28_818B68B8_S_818B68B8_0 *)counter_state)->unk_04 = (u16) (((B28_818B68B8_S_818B68B8_0 *)counter_state)->unk_04 + 1);
    value_state->unk_08 = (s32) (value_state->unk_08 + 0xFFF60000);
    func_800478B8(status);
    if (status->unk_14.at00_u16.v & 0x6000) {
        ((B28_818B68B8_S_818B68B8_0_pre *)counter_state)[-1].unk_00 = (u16) (((B28_818B68B8_S_818B68B8_0_pre *)counter_state)[-1].unk_00 | 0x8000);
        objectFlagBlock.flags = (s32) (objectFlagBlock.flags | 0x8000);
    }
}
