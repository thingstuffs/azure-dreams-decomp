#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017D24();                            /* extern */
M2C_UNK func_80019520(s16, s16, s16);               /* extern */
M2C_UNK func_80019D04(s32, M2C_UNK *, M2C_UNK *);   /* extern */
extern M2C_UNK D_8001A91C;
extern s32 D_8001B320;
extern M2C_UNK D_8001B430;
extern M2C_UNK D_8001B5B0;
extern M2C_UNK D_8001B5F0;
extern M2C_UNK D_8001B638;

void func_8001A144(void) {
    void *temp_v1;

    func_80019520(M2C_FIELD(&D_8001A91C, s16 *, 0), M2C_FIELD(&D_8001A91C, s16 *, 2), M2C_FIELD(&D_8001A91C, s16 *, 4));
    func_80017D24();
    func_80019D04(D_8001B320, &D_8001B430, &D_8001B5B0);
    temp_v1 = *(void **)0x80016000;
    M2C_FIELD(temp_v1, M2C_UNK **, 0x28) = &D_8001B430;
    M2C_FIELD(temp_v1, M2C_UNK **, 0x34) = &D_8001B5F0;
    M2C_FIELD(temp_v1, M2C_UNK **, 0x2C) = &D_8001B638;
}
