#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80018860_1 {
    u8 pad_00[0x1E8];
    M2C_UNK (*unk_1E8)(M2C_UNK);
} S_80018860_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80018860 */




s32 func_8001ADE0();                         /* extern */
extern Rec_D_80016000 *D_80016000;


/* Invoke the callback with code 8 when checks 0x1200 and 0x1201 both return zero. */
void func_80018860(void) {
    if ((func_8001ADE0(0x1200) == 0) && (func_8001ADE0(0x1201) == 0)) {
        ((S_80018860_1 *)(D_80016000->unk_20))->unk_1E8(8);
    }
}
