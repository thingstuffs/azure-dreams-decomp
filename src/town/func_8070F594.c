#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



M2C_UNK func_80016CC4();                            /* extern */
M2C_UNK func_8001A5CC();                     /* extern */
extern M2C_UNK D_8001D9D4;


/* Initialize state, process two entries, set the data pointer, and invoke the callback. */
s32 func_8070F594(void) {
    func_80016CC4();
    func_8001A5CC(0x935);
    func_8001A5CC(0x936);
    ((TownPositionState *)D_80016000->unk_1C)->unk_40 = &D_8001D9D4;
    D_80016000->unk_20->callback_2F8(0xE, 0x200);
    return 0;
}
