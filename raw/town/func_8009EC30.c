#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern s32 func_8003FD64();
extern void *func_8009C3DC();
extern void *func_8009C44C();

void *func_8009C390(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    void *temp_a0;
    void *temp_a1;
    void *temp_a2;
    void *temp_v0;

    if (arg0 != 0) {
        register void *temp_v1 ASM_REG("$3");
        temp_v1 = (void *)func_8003FD64(0x116, arg0);
        ASM_TAILSLOT_PIN(temp_v1);
        return func_8009C3DC();
    }
    temp_v0 = func_8003FC64(0x116);
    temp_a0 = temp_v0 + 0x20;
    if (temp_v0 == NULL) {
        func_8009C44C(temp_a0);
        return NULL;
    }
    temp_a1 = M2C_FIELD(temp_v0, void **, 8);
    temp_a2 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg2;
    ASM_KEEP(arg0);
    M2C_FIELD(temp_a0, s32 *, 0x50) = arg3;
    if (arg0 != 0) {
        M2C_FIELD(temp_a0, s32 *, 0x9C) = (s32)(arg0 + 0x20);
    }
    if (arg1 != NULL) {
        M2C_FIELD(temp_a1, s32 *, 0) = M2C_FIELD(arg1, s32 *, 0);
        M2C_FIELD(temp_a1, s32 *, 4) = M2C_FIELD(arg1, s32 *, 4);
        M2C_FIELD(temp_a1, s32 *, 8) = M2C_FIELD(arg1, s32 *, 8);
    }
    M2C_FIELD(temp_a2, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_a2, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_a2, s32 *, 0xC) = 0x808080;
    return temp_v0;
}
