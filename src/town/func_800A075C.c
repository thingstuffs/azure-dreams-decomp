#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80033D08();
extern M2C_UNK func_800478B8();
extern s32 func_8009706C();
extern M2C_UNK func_800970AC();
extern s32 func_8009D20C();
extern M2C_UNK D_8009DF84[];

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

void func_8009DEBC(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    u8 saved;

    if (func_8009D20C() == 2) {
        func_80033D08(arg0);
        saved = FIELD(arg0, u8 *, 0x15);
        FIELD(arg0, u8 *, 0x15) = 0;
        FIELD(arg0, M2C_UNK **, -0x10) = D_8009DF84;
        FIELD(arg0, u8 *, 0xAC) = saved;
        return;
    }

    FIELD(arg0, M2C_UNK (**)(void *, void *, M2C_UNK, M2C_UNK), 0x50)(arg0, arg0, arg1, arg2);
    if (!(FIELD(arg0, u16 *, -2) & 0x8000)) {
        func_800970AC(func_8009706C(arg1), arg0);
        if (FIELD(arg0, u8 *, 0x4D) == 0x13) {
            func_800478B8(arg2);
        }
    }
}
