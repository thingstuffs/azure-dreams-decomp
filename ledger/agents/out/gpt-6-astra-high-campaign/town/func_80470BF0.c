#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80017BF0_1 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80017BF0_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_40.as_pv in func_80017BF0 */




M2C_UNK func_80019814();                /* extern */
M2C_UNK func_8001A418();                     /* extern */
extern Rec_D_80016000 *D_80016000;


/* Clear the state field, trigger 0x12CB, and forward the handler arguments. */
void func_80017BF0(s32 handler_id, M2C_UNK handler_arg) {
    ((S_80017BF0_1 *)(D_80016000->unk_40.as_pv))->unk_B0 = 0;
    func_8001A418(0x12CB);
    func_80019814(handler_id, handler_arg);
}
