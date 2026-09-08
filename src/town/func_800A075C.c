#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80033D08();
extern M2C_UNK func_800478B8();
extern s32 func_8009706C();
extern M2C_UNK func_800970AC();
extern s32 func_8009D20C(void *, M2C_UNK);
extern M2C_UNK D_8009DF84[];

#define FIELD(base, type, offset) (*(type)((s8 *)(base) + (offset)))

/* Dispatches an object callback or switches the object to its alternate state. */
void func_8009DEBC(void *object, M2C_UNK source, M2C_UNK context) {
    u8 saved_state;

    if (func_8009D20C(object, source) == 2) {
        func_80033D08(object);
        saved_state = FIELD(object, u8 *, 0x15);
        FIELD(object, u8 *, 0x15) = 0;
        FIELD(object, M2C_UNK **, -0x10) = D_8009DF84;
        FIELD(object, u8 *, 0xAC) = saved_state;
        return;
    }

    FIELD(object, M2C_UNK (**)(void *, void *, M2C_UNK, M2C_UNK), 0x50)(object, object, source, context);
    if (!(FIELD(object, u16 *, -2) & 0x8000)) {
        func_800970AC(func_8009706C(source), object);
        if (FIELD(object, u8 *, 0x4D) == 0x13) {
            func_800478B8(context);
        }
    }
}
