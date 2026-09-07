#include "common.h"
typedef long long s64;

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80170838[];
void func_80047784();
M2C_UNK func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
M2C_UNK func_800AD594();
void func_801727D0() __attribute__((noreturn));
void func_801727E8();  /* LEAD 29: NOT noreturn -- expose LEAD-22 SHAPE-B shared-epilogue jal for the 2-arg pinned sibcall */
void func_8017281C() __attribute__((noreturn));
void func_80172820() __attribute__((noreturn));
void func_801728AC() __attribute__((noreturn));
void func_8017291C() __attribute__((noreturn));
extern u8 D_8006CCD8;
extern u8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_8008346C;
extern M2C_UNK D_80170E9C;
extern u8 D_80174F30;
extern u8 D_80174F38;
extern u8 D_80174F40;

void func_80172524(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5 };
    u16 temp_v0;
    u16 temp_v0_2;
    u8 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 6U) {
        goto block_31;
    }
    (void)jt_keep; goto *D_80170838[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_5;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
    func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
    func_8017291C();
    return;
block_5:
    /* LEAD 29: keep block_5's D_8006CCD8 base lui out of the beqz delay slot
     * (retail fills that slot with the fall-through move a0,s3). */
    __asm__ __volatile__("" ::: "memory");
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(s16 *)(&D_8006CCD8 + (((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE)) << 0x14);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (*(s16 *)(&D_8006CCE8 + (((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE)) << 0x14);
    func_8017281C();
    return;
jt_c1:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0xC) >> 1);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x10) >> 1);
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_31;
    }
    {
        register void *call_a0 ASM_REG("$4");
        register void *tail_arg ASM_REG("$5") = &D_80174F30;
        func_801727E8(call_a0, tail_arg);
    }
    return;
jt_c2:
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0xC) >> 1);
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((s32) M2C_FIELD(arg1, s32 *, 0x10) >> 1);
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_31;
    }
    func_800A56E0(0x808);
    {
        register void *call_a0 ASM_REG("$4");
        register void *tail_arg ASM_REG("$5") = &D_80174F38;
        func_801727E8(call_a0, tail_arg);
    }
    return;
jt_c3:
    if (M2C_FIELD(arg2, s8 *, 4) != 2) {
        goto block_17;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x1000)) {
        goto block_17;
    }
    func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
    {
        register u16 six ASM_REG("$3") = 6;
        (void) M2C_FIELD(arg0, volatile u8 *, 0x9B);
        M2C_FIELD(arg0, u16 *, 0x96) = six;
    }
    func_80172820();
    return;
block_17:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_31;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80174F40;
    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80174F40), 0);
    func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
    M2C_FIELD(arg0, u8 *, 0x9B) = 5U;
    M2C_FIELD(arg0, u16 *, 0x96) = 0;
    func_8017291C();
    return;
jt_c4:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((s16) temp_v0 <= 0) {
        goto block_23;
    }
    {
        s32 coord = M2C_FIELD(arg2, u8 *, 0x24) << 6;
        s32 current = M2C_FIELD(arg1, s16 *, 2) - 0x20;
        M2C_FIELD(arg1, s32 *, 0xC) = ((coord - current) << 0x10) / (s16) temp_v0;
    }
    {
        s32 coord = M2C_FIELD(arg2, u8 *, 0x25) << 6;
        s32 current = M2C_FIELD(arg1, s16 *, 6) - 0x20;
        M2C_FIELD(arg1, s32 *, 0x10) = ((coord - current) << 0x10) / M2C_FIELD(arg0, s16 *, 0x96);
    }
    func_801727D0((s16) temp_v0);
    return;
block_23:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_31;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_80174F40;
    func_80047784(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + &D_80174F40), 0);
    M2C_FIELD(arg0, u8 *, 0x9B)++;
    func_8017291C();
    return;
jt_c5:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((s16) temp_v0_2 <= 0) {
        goto block_29;
    }
    {
        s32 coord = M2C_FIELD(arg2, u8 *, 0x24) << 6;
        s32 current = M2C_FIELD(arg1, s16 *, 2) - 0x20;
        M2C_FIELD(arg1, s32 *, 0xC) = ((coord - current) << 0x10) / (s16) temp_v0_2;
    }
    {
        s32 coord = M2C_FIELD(arg2, u8 *, 0x25) << 6;
        s32 current = M2C_FIELD(arg1, s16 *, 6) - 0x20;
        M2C_FIELD(arg1, s32 *, 0x10) = ((coord - current) << 0x10) / M2C_FIELD(arg0, s16 *, 0x96);
    }
    func_801728AC((s16) temp_v0_2);
    return;
block_29:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_31;
    }
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
    func_800AD594(arg3, 0x100);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80170E9C;
    D_8008346C = 0;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    func_800A4ACC(arg3);
block_31:
    return;
}
