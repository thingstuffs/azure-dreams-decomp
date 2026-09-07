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

typedef struct {
    s16 field0;
    s16 field2;
} TableEntry;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern u8 D_80013611[];
extern M2C_UNK D_80045340;
extern M2C_UNK D_800777F4;
extern M2C_UNK D_8016E528;
extern void *D_80174704[];
extern TableEntry D_80174708[];

void func_8016ECE4(void) {
    volatile s32 frame_pad[2];
    s32 var_v0;
    s32 var_v0_2;
    u32 mode;
    u32 page;
    u32 one;
    register void *temp_a0;
    void *temp_s1;
    void *temp_s2;
    void *temp_s3;
    void *temp_v0;
    void *temp_v1;
    void *base;

    base = D_80174704[0];
    page = 0x80010000;
    ASM_KEEP_NV(page);
    one = 1;
    ASM_KEEP_DEP_NV(one, base);
    ASM_USE2_NV(page, base);
    ASM_SCHED_BARRIER();
    mode = page;
    mode = *(u8 *)(mode + 0x3611);
    ASM_KEEP_NV(mode);
    temp_s2 = M2C_FIELD(base, void **, 8);
    temp_s3 = base + 0x20;
    if (((mode & 3) == one) && !(func_80069EF8(base) & 1)) {
        temp_v0 = func_8003FC64(0x12);
        if (temp_v0 != NULL) {
            temp_s1 = temp_v0 + 0x20;
            M2C_FIELD(temp_s1, s16 *, 0x12) = 3;
            M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016E528;
            func_8004491C(temp_v0, &D_80045340);
            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) & 0xFFF3);
            M2C_FIELD(temp_s1, void **, 0x24) = temp_s3;
            temp_v1 = M2C_FIELD(temp_v0, void **, 8);
            M2C_FIELD(temp_v1, u16 *, 2) = (u16) M2C_FIELD(temp_s2, u16 *, 2);
            M2C_FIELD(temp_v1, u16 *, 6) = (u16) M2C_FIELD(temp_s2, u16 *, 6);
            M2C_FIELD(temp_v1, s16 *, 0xA) = (s16) (M2C_FIELD(temp_s2, u16 *, 0xA) - 0x80);
            M2C_FIELD(temp_s1, s32 *, 0x50) = 0;
            M2C_FIELD(temp_s1, s32 *, 0x4C) = 0;
            M2C_FIELD(temp_s1, s32 *, 0x54) = 0;
            M2C_FIELD(temp_s1, s32 *, 0x60) = 0;
            M2C_FIELD(temp_s1, s16 *, 0x18) = (s16) (((u16) M2C_FIELD(temp_s3, u16 *, 0x2A) >> 9) & 7);
            temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
            M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x1000;
            M2C_FIELD(temp_a0, s16 *, 6) = (s16) (D_80174708[((u16) M2C_FIELD(temp_s3, u16 *, 0x2A) >> 9) & 7].field2 * 6);
            M2C_FIELD(temp_s3, s16 *, 0xAA) = 0x4D;
            var_v0 = M2C_FIELD(temp_s2, s16 *, 2);
            if (var_v0 < 0) {
                var_v0 += 0x3F;
            }
            M2C_FIELD(temp_s1, s8 *, 0x48) = (s8) (var_v0 >> 6);
            var_v0_2 = M2C_FIELD(temp_s2, s16 *, 6);
            if (var_v0_2 < 0) {
                var_v0_2 += 0x3F;
            }
            M2C_FIELD(temp_s1, s8 *, 0x49) = (s8) (var_v0_2 >> 6);
            M2C_FIELD(temp_a0, u8 *, 0xE) = 0x80;
            M2C_FIELD(temp_a0, u8 *, 0xD) = 0x80;
            M2C_FIELD(temp_a0, u8 *, 0xC) = 0x80;
            M2C_FIELD(temp_a0, M2C_UNK **, 8) = &D_800777F4;
            M2C_FIELD(temp_a0, u16 *, 0x14) = (u16) (M2C_FIELD(temp_a0, u16 *, 0x14) | 0x80);
            M2C_FIELD(temp_s1, s8 *, 0x44) = 3;
            M2C_FIELD(temp_s1, s8 *, 0x45) = 6;
            M2C_FIELD(temp_s1, s8 *, 0x46) = 0;
            M2C_FIELD(temp_s1, s8 *, 0x47) = 0;
        }
    }
}
