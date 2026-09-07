#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Input6 {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 w5;
} Input6;

typedef struct Tail {
    s16 pad0;
    s16 arg2;
    s32 copy;
    s32 arg0;
} Tail;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80045340[];
extern u8 D_80024020[];
extern u8 D_80024C78[];


void *func_8003FC64(u32);
void func_8004491C(void *, u8 *);
s32 rand(void);

s32 func_80024134(s32 arg0, void *arg1, s16 arg2) {
    s32 temp_v1;
    s32 var_v0;
    void *temp_v0;
    Tail *temp_s2;
    void *temp_s0;
    void *temp_v0_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s2 = (Tail *)((s8 *)temp_v0 + 0x20);
        M2C_FIELD(temp_v0, void **, 0x10) = D_80024020;
        temp_s2->arg0 = arg0;
        M2C_FIELD(temp_v0, s16 *, 0x20) = 0;
        temp_s2->arg2 = arg2;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_s0, u8 *, 0xE) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xD) = 0x80;
        M2C_FIELD(temp_s0, u8 *, 0xC) = 0x80;
        M2C_FIELD(temp_s0, void **, 8) = D_80024C78;
        M2C_FIELD(temp_s0, s16 *, 0x12) = 0x7E02;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0x100);
        var_v0 = rand();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        M2C_FIELD(temp_s0, s16 *, 0x1A) = (s16) (temp_v1 - ((var_v0 >> 0xC) << 0xC));
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x800;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x800;
        func_8004491C(temp_v0, D_80045340);
        temp_v0_2 = M2C_FIELD(temp_v0, void **, 8);
        *(Input6 *)temp_v0_2 = *(Input6 *)arg1;
        temp_v1 = *(volatile s32 *)((s8 *)temp_v0_2 + 8);
        temp_s2->copy = temp_v1;
        return (s32)temp_v0;
    }
    return 0;
}
