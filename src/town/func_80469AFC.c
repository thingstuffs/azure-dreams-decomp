#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001A1A0();        /* extern */
extern u8 D_80017AF4;
extern u8 D_80017B0C;
extern M2C_UNK D_80017B18;
extern M2C_UNK D_80017B24;
extern u8 D_80017EA4;

/* Initializes four consecutive entries in D_80017EA4 and returns their base address. */
M2C_UNK *func_8001AAFC(void) {
    func_8001A1A0(&D_80017EA4, &D_80017AF4);
    func_8001A1A0(&D_80017EA4 + 0x14, &D_80017B24);
    func_8001A1A0(&D_80017EA4 + 0x28, &D_80017B0C);
    func_8001A1A0(&D_80017EA4 + 0x3C, &D_80017B18);
    return &D_80017EA4;
}
