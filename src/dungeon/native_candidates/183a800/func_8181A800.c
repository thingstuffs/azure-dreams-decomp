#include "modules/dungeon_ovl_183a800.h"
#include "common.h"
#include "shared/object_flags.h"

   /* arg0 in func_8002404C; pointer addresses record offset 0x2 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))




/* Decrement the record counter, process update data, and flag depletion. */
void func_8002404C(void *record_data, void *unused, void *update_data) {
    s16 remaining;
    s16 *update_flag;

    update_flag = &D_80025914;
    remaining = (s16)((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 - 1;
    update_flag[0] = 1;
    ((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 = remaining;
    func_800478B8(update_data);
    if (((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_04 <= 0) {
        ((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_00 =
            (u16)(((S_8181A800_0 *)((u8 *)record_data - 0x2))->unk_00 | 0x8000);
        objectFlagBlock.flags |= 0x8000;
    }
}
