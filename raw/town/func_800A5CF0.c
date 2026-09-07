#include "common.h"

extern void *func_8003FD64(s32, void *);
extern u8 D_80083498[];
extern u8 D_800A34E0[];
extern u8 D_800A3508[];

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void *func_800A3450(void *arg0, s16 arg1)
{
    void *object;
    void *copy;
    register void *result ASM_REG("$2");

    object = func_8003FD64(0x136, D_80083498);
    result = 0;
    if (object != 0) {
        copy = FIELD(object, void *, 8);
        FIELD(copy, s32, 0) = FIELD(arg0, s32, 0);
        FIELD(copy, s32, 4) = FIELD(arg0, s32, 4);
        result = object;
        FIELD(copy, s32, 8) = FIELD(arg0, s32, 8);
        FIELD(result, void *, 0x10) = D_800A34E0;
        FIELD(result, void *, 0x20) = D_800A3508;
        FIELD(result, s16, 0x42) = arg1;
    }
    return result;
}
