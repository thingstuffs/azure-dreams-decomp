#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

extern u8 D_80083498[];
extern u8 D_80045340[];
extern s16 D_80083228[5];
void *func_8003FD64();
M2C_UNK func_8004491C();
void func_80047784();
extern M2C_UNK D_80170D44;
extern u8 D_80173EB4[8];

void func_80170E18(void *unused, void *arg1, void *arg2, void *arg3) {
    s32 temp_t0;
    void *temp_s0;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    void *var_a2;
    Block16 *src;
    Block16 *dst;
    Block16 *end;

    temp_v0 = func_8003FD64(0x112, D_80083498);
    var_a2 = arg2;
    if (temp_v0 != NULL) {
        temp_v1 = temp_v0 + 0x20;
        M2C_FIELD(temp_v1, s16 *, 0x96) = 7;
        M2C_FIELD(temp_v1, s16 *, 0xA8) = 7;
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_80170D44;
        M2C_FIELD(temp_v1, void **, 0xAC) = arg1;
        temp_s0 = M2C_FIELD(temp_v0, void **, 0xC);
        src = (Block16 *)var_a2;
        dst = (Block16 *)temp_s0;
        end = src + 3;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_s0, s8 *, 0xE) = 0x50;
        M2C_FIELD(temp_s0, s8 *, 0xD) = 0x50;
        M2C_FIELD(temp_s0, s8 *, 0xC) = 0x50;
        M2C_FIELD(temp_s0, s16 *, 0x10) = 0x20;
        M2C_FIELD(temp_s0, u16 *, 0x12) = 0xFF80;
        M2C_FIELD(temp_s0, u16 *, 0x22) = 0xFFF1;
        M2C_FIELD(temp_s0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0, u16 *, 0x14) | 0xC);
        func_8004491C(temp_v0, D_80045340, src, dst);
        M2C_FIELD(temp_s0, M2C_UNK **, 0x2C) = &D_80173EB4;
        func_80047784(temp_s0, *((((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + D_80173EB4), 0);
        temp_v1_2 = M2C_FIELD(temp_v0, void **, 8);
        M2C_FIELD(temp_v1_2, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 2);
        M2C_FIELD(temp_v1_2, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 6);
        M2C_FIELD(temp_v1_2, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0xA);
    }
}
