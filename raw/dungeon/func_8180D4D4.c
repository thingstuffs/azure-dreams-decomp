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
    u8 unk00[8];
    void *addr;
    u8 unk0c[4];
    s16 unk10;
    s16 unk12;
    u16 flags;
    u8 unk16[6];
    s16 unk1c;
    s16 unk1e;
} NodeA;

extern u8 D_80083498[];
extern u8 D_80028808;
extern u8 D_800260DC[];
extern u8 D_800CEF54[];

void *func_8003FD64(s32, void *);
M2C_UNK func_8004491C(void *, void *);

void *func_800264D4(void *arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 var_s1;
    s32 index;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_a2;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    register u16 temp_v0_8 ASM_REG("$3");
    void *temp_a0;
    void *temp_a0_2;
    void *temp_a1;
    void *temp_v0;
    void *var_s4;
    void *var_v1;
    u8 *page_base;

    var_s4 = NULL;
    var_s1 = 0;
    page_base = &D_800260DC[0];
    index = (arg2 << 0x10) >> 16;
loop_1:
    temp_v0 = func_8003FD64(0x12, D_80083498);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = page_base;
        func_8004491C(temp_v0, &D_800CEF54);
        temp_a1 = M2C_FIELD(temp_v0, void **, 8);
        temp_v0_2 = M2C_FIELD(arg0, u16 *, 2);
        M2C_FIELD(temp_a1, u16 *, 2) = temp_v0_2;
        M2C_FIELD(temp_a1, u16 *, 0xE) = temp_v0_2;
        temp_v0_3 = M2C_FIELD(arg0, u16 *, 6);
        M2C_FIELD(temp_a1, u16 *, 6) = temp_v0_3;
        M2C_FIELD(temp_a1, u16 *, 0x12) = temp_v0_3;
        temp_v0_4 = M2C_FIELD(arg0, u16 *, 0xA);
        M2C_FIELD(temp_a1, u16 *, 0xA) = temp_v0_4;
        M2C_FIELD(temp_a1, u16 *, 0x16) = temp_v0_4;
        temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
        temp_v0_8 = M2C_FIELD(temp_a0, u16 *, 0x14);
        M2C_FIELD(temp_a0, void **, 8) = (void *) ((index * 0xC) + &D_80028808);
        M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_a0, s16 *, 0x10) = 0x60;
        M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (temp_v0_8 | 0xC);
        temp_a0_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_a0_2, s32 *, 4) = arg1;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_a0_2, s16 *, 0x66) = 0x20;
        M2C_FIELD(temp_a0_2, s16 *, 0x6E) = var_s1;
        temp_v0_5 = M2C_FIELD(temp_a1, s32 *, 0);
        M2C_FIELD(temp_a0_2, s32 *, 0x18) = temp_v0_5;
        M2C_FIELD(temp_a0_2, s32 *, 0xC) = temp_v0_5;
        temp_v0_6 = M2C_FIELD(temp_a1, s32 *, 4);
        var_a2 = 0;
        M2C_FIELD(temp_a0_2, s32 *, 0x1C) = temp_v0_6;
        M2C_FIELD(temp_a0_2, s32 *, 0x10) = temp_v0_6;
        var_v1 = temp_a0_2;
        temp_v0_7 = M2C_FIELD(temp_a1, s32 *, 8);
        M2C_FIELD(temp_a0_2, s32 *, 0x20) = temp_v0_7;
        M2C_FIELD(temp_a0_2, s32 *, 0x14) = temp_v0_7;
        do {
            M2C_FIELD(var_v1, u16 *, 0x24) = (u16) M2C_FIELD(temp_a1, u16 *, 2);
            M2C_FIELD(var_v1, u16 *, 0x26) = (u16) M2C_FIELD(temp_a1, u16 *, 6);
            var_a2 += 1;
            M2C_FIELD(var_v1, u16 *, 0x28) = (u16) M2C_FIELD(temp_a1, u16 *, 0xA);
            var_v1 += 8;
        } while (var_a2 < 8);
        M2C_FIELD(temp_a0_2, void **, 8) = var_s4;
        var_s4 = temp_v0;
        var_s1 += 1;
        M2C_FIELD(temp_a0_2, s16 *, 0x72) = arg3;
        if (var_s1 >= 6) {

        } else {
            goto loop_1;
        }
    }
    return temp_v0;
}
