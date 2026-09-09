#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



M2C_UNK func_8001A414(s32, s32, s32);                            /* extern */
extern Rec_D_8001E950 *D_8001E950;

void func_8001A3E8(s32 arg0, s32 arg1, s32 arg2) {
    D_8001E950->unk_02 = 0xFF;
    func_8001A414(arg0, arg1, arg2);
}
