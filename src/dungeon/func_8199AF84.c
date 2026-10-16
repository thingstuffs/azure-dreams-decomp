#include "common.h"
#include "m2c_compat.h"
extern s32 func_80069EF8(void);
/* The 0x54-byte ring ends at the adjacent weights-table address.
 * Name the bounded ring without guessing the following table's extent. */
typedef struct { u8 packets[0x54]; } PacketRing;
extern s8 D_80024AE0[];

extern u16 D_80024A70;
extern s32 D_800814A0;
void func_80024784(void *arg0, void *arg1, void *arg2) {
    s32 var_s0;
    u16 *var_s1;
    s32 jitter;
    s32 fade;
    u16 temp_v0;
    u16 temp_v0_3;
    u32 temp_v0_2;
    u8 temp_v0_4;
    void *temp_a0;
    void *var_s2;

    temp_a0 = M2C_FIELD(arg0, void **, 0x14);
    D_80024A70 += 1;
    if (temp_a0 != NULL) {
        M2C_FIELD(arg1, u16 *, 0xE) = (u16) M2C_FIELD(temp_a0, u16 *, 2);
        M2C_FIELD(arg1, u16 *, 0x12) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), u16 *, 6);
        M2C_FIELD(arg1, u16 *, 0x16) = (u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x14), u16 *, 0xA);
    }
    var_s2 = arg1;
    var_s1 = arg0 + 0x18;
    var_s0 = 3;
    do {
        var_s0 -= 1;
        jitter = (func_80069EF8() & 0xF) - 8;
        temp_v0 = *var_s1;
        var_s1 += 1;
        M2C_FIELD(var_s2, s16 *, 2) = (s16) (temp_v0 + (jitter * D_80024AE0[M2C_FIELD(arg0, s16 *, 0x32)]));
        var_s2 += 4;
    } while (var_s0 > 0);
    temp_v0_2 = M2C_FIELD(arg2, u32 *, 8) + 0xC;
    M2C_FIELD(arg2, u32 *, 8) = temp_v0_2;
    if (temp_v0_2 >= (u32)D_80024AE0) {
        M2C_FIELD(arg2, u32 *, 8) = (u32)((PacketRing *)((u8 *)D_80024AE0 - sizeof(PacketRing)))->packets;
    }
    temp_v0_3 = M2C_FIELD(arg2, u16 *, 0x1E) - (M2C_FIELD(arg2, u16 *, 0x1E) / 24);
    M2C_FIELD(arg2, u16 *, 0x1E) = temp_v0_3;
    M2C_FIELD(arg2, u16 *, 0x1C) = temp_v0_3;
    fade = M2C_FIELD(arg0, u16 *, 0x3C);
    fade -= 8;
    M2C_FIELD(arg0, u16 *, 0x3C) = fade + ((s16) (u16) M2C_FIELD(arg0, s16 *, 0x32) / 2);
    temp_v0_4 = (u8) M2C_FIELD(arg0, u16 *, 0x3C);
    M2C_FIELD(arg2, u8 *, 0xE) = temp_v0_4;
    M2C_FIELD(arg2, u8 *, 0xD) = temp_v0_4;
    M2C_FIELD(arg2, u8 *, 0xC) = temp_v0_4;
    if ((s16) M2C_FIELD(arg0, u16 *, 0x3C) <= 0) {
        M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
        D_800814A0 |= 0x8000;
    }
}
