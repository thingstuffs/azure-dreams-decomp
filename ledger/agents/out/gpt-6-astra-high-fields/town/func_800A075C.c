#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80033D08();
extern M2C_UNK func_800478B8();
extern s32 func_8009706C();
extern M2C_UNK func_800970AC();
extern s32 func_8009D20C(void *, M2C_UNK);
extern M2C_UNK D_8009DF84[];

typedef struct S_func_8009DEBC_0 {
    u8 pad_00[0x15];
    u8 unk_15;
    u8 pad_16[0x37];
    u8 unk_4D;
    u8 pad_4E[2];
    M2C_UNK (*unk_50)(void *, void *, M2C_UNK, M2C_UNK);
    u8 pad_54[0x58];
    u8 unk_AC;
} S_func_8009DEBC_0;

typedef struct S_func_8009DEBC_1 {
    M2C_UNK *unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
} S_func_8009DEBC_1;

/* Dispatches an object callback or switches the object to its alternate state. */
void func_8009DEBC(S_func_8009DEBC_0 *object, M2C_UNK source, M2C_UNK context) {
    u8 saved_state;

    if (func_8009D20C(object, source) == 2) {
        func_80033D08(object);
        saved_state = object->unk_15;
        object->unk_15 = 0;
        ((S_func_8009DEBC_1 *)((u8 *)object - 0x10))->unk_00 = D_8009DF84;
        object->unk_AC = saved_state;
        return;
    }

    object->unk_50(object, object, source, context);
    if (!(((S_func_8009DEBC_1 *)((u8 *)object - 0x10))->unk_0E & 0x8000)) {
        func_800970AC(func_8009706C(source), object);
        if (object->unk_4D == 0x13) {
            func_800478B8(context);
        }
    }
}
