#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



M2C_UNK func_80019814();                /* extern */
M2C_UNK func_8001A418();                     /* extern */


/* Clear the state field, trigger 0x12CB, and forward the handler arguments. */
void func_80017BF0(s32 handler_id, M2C_UNK handler_arg) {
    ((TownProgressState *)D_80016000->unk_40)->unk_B0 = 0;
    func_8001A418(0x12CB);
    func_80019814(handler_id, handler_arg);
}
