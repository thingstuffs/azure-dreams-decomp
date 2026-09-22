#include "common.h"

typedef s32 M2C_UNK;

s32 func_80017B24();
M2C_UNK *func_80017BDC();
M2C_UNK func_8001856C();
s32 func_800187D8();
extern M2C_UNK D_80018974;
extern M2C_UNK D_80018AD0;
extern M2C_UNK D_80019F15;
extern M2C_UNK D_8001A0A1;

/* Look up the slot's record; when it is already claimed, substitute one of two fixed records. */
M2C_UNK *func_806973CC(s32 slot, M2C_UNK unused, M2C_UNK context) {
    M2C_UNK *record;
    M2C_UNK *result;

    record = func_80017BDC(&D_80018974, &D_80018AD0, slot, context);
    result = record;
    if (func_80017B24(&D_80018974, slot, context) != 0) {
        if (func_800187D8(8) != 0) {
            result = &D_8001A0A1;
        } else {
            func_8001856C(0x12C8);
            result = &D_80019F15;
        }
    }
    return result;
}
