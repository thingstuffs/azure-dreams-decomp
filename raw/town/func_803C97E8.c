#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001A1A0(s32, M2C_UNK *);              /* extern */
extern M2C_UNK D_80017AAC;
extern M2C_UNK D_80017AB8;

s32 func_8001A7E8(void) {
    func_8001A1A0(*(s32 *)0x80017D20, &D_80017AAC);
    func_8001A1A0(*(s32 *)0x80017D20 + 0x14, &D_80017AB8);
    return *(s32 *)0x80017D20;
}
