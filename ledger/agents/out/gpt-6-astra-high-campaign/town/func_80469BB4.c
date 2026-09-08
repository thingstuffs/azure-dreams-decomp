#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001A1A0();        /* extern */
extern u8 D_80017AF4;
extern M2C_UNK D_80017B0C;
extern M2C_UNK D_80017B18;
extern u8 D_80017F44;

/* Apply three value tables to consecutive global destinations and return their base. */
M2C_UNK *func_8001ABB4(void) {
    func_8001A1A0(&D_80017F44, &D_80017AF4);
    func_8001A1A0(&D_80017F44 + 0x14, &D_80017B0C);
    func_8001A1A0(&D_80017F44 + 0x28, &D_80017B18);
    return &D_80017F44;
}
