#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001A1A0();        /* extern */
extern M2C_UNK D_80017B0C;
extern M2C_UNK D_80017B18;
extern u8 D_80017F08;

/* Process two locations in the data block and return its base address. */
M2C_UNK *func_8001AB68(void) {
    func_8001A1A0(&D_80017F08, &D_80017B0C);
    func_8001A1A0(&D_80017F08 + 0x14, &D_80017B18);
    return &D_80017F08;
}
