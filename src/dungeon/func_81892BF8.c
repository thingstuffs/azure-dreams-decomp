#include "modules/dungeon_ovl_18b2800.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

   /* the 0x2 bytes before arg0 in func_800243F8, addressed as arg0[-1] */

   /* arg0 in func_800243F8 */




/* Increment both counters and set completion flags when the count reaches its limit. */
void func_800243F8(void *counterState) {
    u16 incrementedCount;
    B22_81892BF8_S_81892BF8_1 *linkedCounter;

    linkedCounter = ((B22_81892BF8_S_81892BF8_0 *)counterState)->unk_00;
    linkedCounter->unk_14 = (u16) (linkedCounter->unk_14 + 1);
    incrementedCount = ((B22_81892BF8_S_81892BF8_0 *)counterState)->unk_04 + 1;
    ((B22_81892BF8_S_81892BF8_0 *)counterState)->unk_04 = incrementedCount;
    if ((s16) incrementedCount >= ((B22_81892BF8_S_81892BF8_0 *)counterState)->unk_06) {
        ((B22_81892BF8_S_81892BF8_0_pre *)counterState)[-1].unk_00 = (u16) (((B22_81892BF8_S_81892BF8_0_pre *)counterState)[-1].unk_00 | 0x8000);
        object_flag_block.flags = (s32) (object_flag_block.flags | 0x8000);
    }
}
