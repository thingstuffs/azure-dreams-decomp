#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FC64();
extern s32 func_800B835C();
extern u8 D_800243C4[9];
extern u8 D_80028208[9];
extern u8 D_800DF334[9];

void *func_80024578(void *arg0, s32 arg1) {
    s32 init[2];
    void *object;
    void *part;
    void *effect;
    void *result;

    object = func_8003FC64(0x12);
    if (object != NULL) {
        init[0] = 0x01000340;
        init[1] = 0x00200020;
        func_800B835C(D_800DF334, init, 1, 0);

        part = FIELD(object, void *, 8);
        FIELD(object, void *, 0x10) = D_800243C4;
        FIELD(part, u16, 2) = FIELD(arg0, u16, 2);
        FIELD(part, u16, 6) = FIELD(arg0, u16, 6);
        FIELD(part, u16, 0xA) = FIELD(arg0, u16, 0xA);

        effect = FIELD(object, void *, 0xC);
        FIELD(effect, void *, 8) = D_80028208;
        FIELD(effect, s16, 0x1E) = 0xC00;
        FIELD(effect, s16, 0x1C) = 0xC00;
        FIELD(object, s32, 0x28) = arg1 - 0x20;
    }

    result = NULL;
    if (object != NULL) {
        result = (u8 *)object + 0x20;
    }
    return result;
}
