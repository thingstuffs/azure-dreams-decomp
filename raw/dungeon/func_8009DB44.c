#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
struct S_800E3E48 {
  u8 pad00[0x14];
  s32 unk14;
  u8 pad18[0x1C - 0x18];
  s32 unk1C;
  u8 pad20[0x8C - 0x20];
};
struct S_16 {
  s32 w0;
  s32 w4;
  s32 w8;
  s32 wC;
};
struct S_12 {
  s32 w0;
  s32 w4;
  s32 w8;
};
typedef struct S_800E3E48 S_800E3E48;
extern S_800E3E48 D_800E3E48[];
extern s32 D_800E3DF0[];
extern s32 D_80083460[3];
extern void func_80042B68(void *, s32);
extern M2C_UNK func_800A18E8();
extern M2C_UNK func_800A31D0();
extern s32 func_800A3418();
extern s32 func_800A347C(void *);

s32 func_800A32A4(void *arg0) {
    register M2C_UNK var_s1 ASM_REG("$17");
    s32 *temp_a0_2;
    register s32 temp_a1_2 ASM_REG("$5");
    s32 temp_v1;
    s32 temp_v1_2;
    register s32 flag_value ASM_REG("$3");
    s32 tail_w0;
    s32 tail_w4;
    s32 tail_w8;
    volatile s32 *tail_src;
    s32 var_v1;
    register void *computed_dest ASM_REG("$2");
    void *temp_a0;
    void *temp_s2;
    void *var_a2;
    void *var_a3;
    register u8 *page_base ASM_REG("$6");
    register u8 *status_page ASM_REG("$2");
    register s32 flags_mask ASM_REG("$7");
    S_800E3E48 *copy_base;
    s32 *registry;
    register void *copy_end ASM_REG("$8");

    var_s1 = 0;
    ASM_KEEP_NV(var_s1);
    temp_s2 = 0;
    func_80042B68(arg0, 0x1A);
    func_80042B68(arg0, 0x1C);
    func_80042B68(arg0, 0x1D);
    if (!(M2C_FIELD(arg0, s32 *, 0x14) & 0x20000000)) {
        func_800A31D0(arg0);
        var_v1 = 0;
        page_base = (u8 *)0x80080000;
        flags_mask = ~0x4000;
        registry = D_800E3DF0;
        copy_base = D_800E3E48;
        copy_end = arg0 + 0x80;
loop_2:
        temp_a1_2 = var_v1 * 4;
        temp_a0 = temp_a1_2 + M2C_FIELD(page_base, s32 *, 0x14A8);
        var_v1 += 1;
        if (M2C_FIELD(temp_a0, s32 *, 0xAC) == arg0) {
            M2C_FIELD(arg0, s32 *, 0x14) = (s32)(M2C_FIELD(arg0, s32 *, 0x14) & flags_mask);
            M2C_FIELD(temp_a0, s32 *, 0xAC) = 0;
            flag_value = M2C_FIELD(arg0, s32 *, 0x1C);
            flag_value |= 0x04000000;
            flag_value |= 0x00020000;
            M2C_FIELD(arg0, s32 *, 0x1C) = flag_value;
            temp_s2 = M2C_FIELD(temp_a0, void **, 0xD0);
            M2C_FIELD(temp_s2, u8 *, 3) = (u8)(M2C_FIELD(temp_s2, u8 *, 3) & 0xDF);
            computed_dest = (void *)M2C_FIELD(page_base, s32 *, 0x14A8);
            computed_dest = (void *)((u32)temp_a1_2 + (u32)computed_dest);
            M2C_FIELD(computed_dest, s32 *, 0xD0) = 0;
            var_s1 = 3;
            var_a3 = arg0;
            temp_v1 = M2C_FIELD(temp_s2, u8 *, 3) & 0x1F;
            ASM_USE(var_s1);
            ASM_KEEP_NV(copy_base);
            computed_dest = (void *)((temp_v1 * sizeof(*copy_base)) + (s32)copy_base);
            var_a2 = computed_dest;
            registry[temp_v1] = (s32)var_a2;
            do {
                *(struct S_16 *)var_a2 = *(struct S_16 *)var_a3;
                var_a3 += 0x10;
                var_a2 += 0x10;
            } while (var_a3 != copy_end);
            tail_src = (volatile s32 *)var_a3;
            tail_w0 = tail_src[0];
            tail_w4 = tail_src[1];
            tail_w8 = tail_src[2];
            M2C_FIELD(var_a2, s32 *, 0) = tail_w0;
            M2C_FIELD(var_a2, s32 *, 4) = tail_w4;
            M2C_FIELD(var_a2, s32 *, 8) = tail_w8;
            return func_800A3418();
        }
        if (var_v1 >= 4) {
            goto block_8;
        }
        goto loop_2;
    }
block_8:
    if (var_s1 == 0) {
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x14);
        var_s1 = 3;
        if (!(temp_v1_2 & 0x4000)) {
            status_page = (u8 *)(temp_v1_2 & 0x2000);
            if (status_page) {
                status_page = (u8 *)0x80080000;
                ASM_KEEP_NV(status_page);
                temp_a0_2 = (s32 *)(status_page + 0x3460);
                if (M2C_FIELD(temp_a0_2, s16 *, 0x1C) != 0) {
                    M2C_FIELD(temp_a0_2, s16 *, 0x1C) = (s16)(M2C_FIELD(temp_a0_2, u16 *, 0x1C) - 1);
                }
                var_s1 = 2;
                ASM_TAILSLOT_PIN(var_s1);
                return func_800A347C(temp_a0_2);
            }
            status_page = (u8 *)0x80080000;
            ASM_KEEP_NV(status_page);
            temp_a0_2 = (s32 *)(status_page + 0x3460);
            if (M2C_FIELD(temp_a0_2, s16 *, 0x1C) != 0) {
                M2C_FIELD(temp_a0_2, s16 *, 0x1C) = (s16)(M2C_FIELD(temp_a0_2, u16 *, 0x1C) - 1);
            }
            var_s1 = 1;
            goto block_18;
        }
    }
block_18:
    if (!(M2C_FIELD(arg0, s32 *, 0x14) & 0x20000000)) {
        func_800A18E8(M2C_FIELD(arg0, u8 *, 0x13), var_s1);
    }
    return (s32)temp_s2;
}
