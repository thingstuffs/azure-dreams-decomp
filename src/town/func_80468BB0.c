#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



M2C_UNK func_80019B70();                      /* extern */
extern u8 D_80017B30;


/* Pass the callback-selected eight-byte table entry to func_80019B70. */
void func_80019BB0(void) {
    func_80019B70((D_80016000->unk_20->callback_2D4(0) * 8) + &D_80017B30);
}
