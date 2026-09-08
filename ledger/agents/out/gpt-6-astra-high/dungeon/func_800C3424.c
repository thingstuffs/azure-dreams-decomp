#include "common.h"

extern s32 func_80099844(void *arg0, void *arg1);
extern s32 func_800C8C1C(void *arg0, s16 arg1, s16 arg2);
extern s32 func_800DC1B8(s32 arg0);
extern s32 D_800DCF14;
extern u8 D_800E191B[];
extern u8 D_800E1A44[];

/* Attempt to apply a status effect and display the result. */
s32 func_800C8B84(void *entity, s16 chance, s16 effect_value) {
    if (func_800C8C1C(entity, chance, effect_value) != 0) {
        func_80099844(entity, D_800E1A44);
        if (*(u8 *)((u8 *)entity + 0x13) == 0) {
            func_800DC1B8(D_800DCF14);
        }
        return 1;
    }
    if ((*(s32 *)((u8 *)entity + 0x1C) & 0x10) == 0) {
        func_80099844(entity, D_800E191B);
    }
    return 0;
}
