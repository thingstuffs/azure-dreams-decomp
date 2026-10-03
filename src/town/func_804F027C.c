#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



M2C_UNK func_8001746C();                     /* extern */
extern M2C_UNK D_800175E4;
extern M2C_UNK *D_80017698;


/* Invoke the state callback, select D_800175E4, and request operation 0x526. */
void func_804F027C(void) {
    D_80016000->unk_20->callback_2C0();
    D_80017698 = &D_800175E4;
    func_8001746C(0x526);
}
