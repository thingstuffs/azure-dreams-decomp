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
struct D83460_VIEW { s16 pad[3]; s16 divisor[1]; };

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_800889C0[];
void func_80048A44();
s32 func_8009074C();
s32 func_80094EA4();
M2C_UNK func_80099F04();
M2C_UNK func_80099F70();
M2C_UNK func_800A2B04();
M2C_UNK func_800B653C();
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8008ACDC;
extern u8 D_800DD018[];
extern u8 D_800DD020[];
extern u8 D_800DD028[];

void func_80092018(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c16, &&jt_c17, &&jt_c18, &&jt_c19 };
    s16 temp_a0_2;
    s16 temp_v0_3;
    s32 temp_a0;
    s32 temp_v0_6;
    s32 temp_v1_5;
    u16 temp_v0_2;
    u16 temp_v0_4;
    u16 temp_v1_3;
    u8 temp_v1;
    void *temp_v1_2;
    M2C_UNK *temp_s4;
    void *temp_v0_5;
    u16 temp_v1_4;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 0x14U) {
        goto block_29;
    }
    (void)jt_keep; goto *D_800889C0[(u32)(temp_v1)];
jt_c0:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_5;
    }
    if (M2C_FIELD(arg2, u8 **, 0x2C) == D_800DD028) {
        goto block_27;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD028;
    func_80048A44(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + D_800DD028), 0, 1);
    return;
block_5:
    temp_a0 = func_8009074C(M2C_FIELD(arg0, s16 *, 0x9E), arg0 + 0xA2, arg3 + 0x2A) << 0x10;
    if ((temp_a0 >> 0x10) == 0xFFF) {
        goto block_29;
    }
    if ((((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 9) & 7) == ((temp_a0 >> 0x19) & 7)) {
        goto block_29;
    }
    if ((func_80094EA4(temp_a0) << 0x10) == 0) {
        goto block_29;
    }
    goto block_28;
jt_c16:
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) (*((s16 *)(D_8006CCD8 + (((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE))) * 8);
    M2C_FIELD(arg1, s16 *, 0x12) = (s16) (*((s16 *)(D_8006CCE8 + (((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE))) * 8);
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_2;
    if ((temp_v0_2 << 0x10) > 0) {
        goto block_29;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD018;
    func_80048A44(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + D_800DD018), 0, 1);
    temp_v1_2 = M2C_FIELD(arg0, void **, 0x124);
    M2C_FIELD(temp_v1_2, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x1C) | 0x100);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), u16 *, 0x6A) = (u16) M2C_FIELD(arg3, s16 *, 0x2A);
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x124), void **, 0x60) = arg3;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    return;
jt_c17:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_13;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD020;
    func_80048A44(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + D_800DD020), 0, 1);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c18:
block_13:
    temp_s4 = &D_80083460;
    if (M2C_FIELD(temp_s4, s16 *, 4) == 0) {
        goto block_15;
    }
    temp_a0 = M2C_FIELD(arg1, s16 *, 2);
    {
        s32 coordinate;
        s32 table_value;
        coordinate = M2C_FIELD(arg2, u8 *, 0x24) << 6;
        table_value = *((s16 *)(D_8006CCD8 + (((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE))) * 0x10;
        table_value += 0x20;
        coordinate += table_value;
        coordinate -= temp_a0;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((coordinate << 0x10) / (s16) M2C_FIELD(temp_s4, s16 *, 4));
    }
    temp_a0 = M2C_FIELD(arg1, s16 *, 6);
    {
        s32 coordinate;
        s32 table_value;
        coordinate = M2C_FIELD(arg2, u8 *, 0x25) << 6;
        table_value = *((s16 *)(D_8006CCE8 + (((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE))) * 0x10;
        table_value += 0x20;
        coordinate += table_value;
        coordinate -= temp_a0;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((coordinate << 0x10) / ((struct D83460_VIEW *) temp_s4)->divisor[-1]);
    }
block_15:
    if ((u16) M2C_FIELD(temp_s4, s16 *, 4) & 3) {
        goto block_17;
    }
    func_800B653C(arg1, M2C_FIELD(arg3, s16 *, 0x2A));
block_17:
    temp_v0_3 = (u16) M2C_FIELD(temp_s4, s16 *, 4) - 1;
    M2C_FIELD(temp_s4, s16 *, 4) = temp_v0_3;
    if ((temp_v0_3 << 0x10) > 0) {
        goto block_29;
    }
    M2C_FIELD(temp_s4, s16 *, 4) = 0;
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    M2C_FIELD(arg2, u8 **, 0x2C) = D_800DD028;
    func_80048A44(arg2, *((((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + D_800DD028), 0, 1);
    M2C_FIELD(arg0, u16 *, 0x96) = 2U;
    M2C_FIELD(arg0, u8 *, 0x9B) = 0x13U;
    return;
jt_c19:
    temp_a0_2 = (s16) M2C_FIELD(arg0, u16 *, 0x96);
    if (temp_a0_2 == 0) {
        goto block_23;
    }
    {
        s32 coordinate;
        s32 origin;
        coordinate = M2C_FIELD(arg2, u8 *, 0x24) << 6;
        origin = M2C_FIELD(arg1, s16 *, 2);
        origin -= 0x20;
        coordinate -= origin;
        M2C_FIELD(arg1, s32 *, 0xC) = (s32) ((coordinate << 0x10) / temp_a0_2);
    }
    {
        s32 coordinate;
        s32 origin;
        origin = M2C_FIELD(arg1, s16 *, 6);
        origin -= 0x20;
        coordinate = M2C_FIELD(arg2, u8 *, 0x25) << 6;
        coordinate -= origin;
        M2C_FIELD(arg1, s32 *, 0x10) = (s32) ((coordinate << 0x10) / (s16) M2C_FIELD(arg0, u16 *, 0x96));
    }
    if (M2C_FIELD(arg0, s16 *, 0x96) == 0) {
        goto block_23;
    }
    temp_v0_4 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_4;
    if ((temp_v0_4 << 0x10) != 0) {
        goto block_23;
    }
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
block_23:
    temp_v1_3 = M2C_FIELD(arg2, u16 *, 0x14);
    if (temp_v1_3 & 0x8000) {
        goto block_26;
    }
    if (!(temp_v1_3 & 0x6000)) {
        goto block_29;
    }
    if (M2C_FIELD(arg0, s16 *, 0x96) != 0) {
        goto block_29;
    }
block_26:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    func_80099F70(M2C_FIELD(arg3, s32 *, 0x5C));
    func_80099F04(M2C_FIELD(arg3, s32 *, 0x5C));
    {
        register void *rmw_base ASM_REG("$2") = &D_80083460;
        register u16 rmw_value ASM_REG("$3");
        rmw_value = M2C_FIELD(rmw_base, u16 *, 2);
        rmw_value = (u16) (rmw_value | 0x812);
        M2C_FIELD(rmw_base, u16 *, 2) = rmw_value;
    }
block_27:
block_28:
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_8008ACDC;
block_29:
    return;
}
