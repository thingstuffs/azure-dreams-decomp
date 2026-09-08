#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8002290C_arg0.h"

M2C_UNK func_80022BE8();                      /* extern */
extern u8 D_800280B4[];
__asm__(".set D_800280B4, 0x800280B4");


/* Configure the menu and compute its table entry's text dimensions. */
void func_80022C48(Rec_func_8002290C_arg0 *menu, s32 value_14, s32 entry_index, s32 input_mode, s32 exit_status_addr) {
    menu->unk_14 = value_14;
    menu->unk_20 = exit_status_addr;
    menu->unk_08 = entry_index;
    menu->unk_0C = input_mode;
    func_80022BE8((entry_index * 0x18) + &D_800280B4[0]);
}
