#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Copy24 {
    s32 words[6];
} Copy24;

extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_8002420C;
extern s32 D_80045340;
extern s32 D_800E2178;

void *func_81892AF0(s32 arg0, Copy24 *arg1, s16 arg2) {
    Copy24 *temp_a1;
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_2;
    register void *var_v0 ASM_REG("$2");

    temp_v0 = func_8003FC64(0x212);
    var_v0 = NULL;
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 **, 0x10) = &D_8002420C;
        temp_v0_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, s32 *, 0x20) = arg0;
        M2C_FIELD(temp_v0_2, s16 *, 4) = 0;
        M2C_FIELD(temp_v0_2, s16 *, 6) = arg2;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        func_8003DB94(temp_s0, &D_800E2178, 0);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1800;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1800;
        func_8004491C(temp_v0, &D_80045340);
        temp_a1 = M2C_FIELD(temp_v0, Copy24 **, 8);
        var_v0 = temp_v0;
        *temp_a1 = *arg1;
        M2C_FIELD(temp_a1, s32 *, 0x14) = 0x10000;
        M2C_FIELD(temp_a1, s32 *, 8) += 0xFD010000;
    }
    return var_v0;
}
