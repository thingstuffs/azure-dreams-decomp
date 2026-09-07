#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
#define VFIELD(p, type, offset) (*(volatile type *)((u8 *)(p) + (offset)))

extern void func_8003DB6C(void *, void *, s32);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern void func_80065320(void *, void *, void *);
extern void func_80065820(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_800666E0(void *);
extern void func_800666F4(void *);
extern void func_80067E2C(void *, void *);
extern void func_80067F20(void *, s32, s32, s32, s32);

extern u8 D_80083160[];
extern u8 D_801C9E40[16];

s32 func_8009E798(void *arg0, void *arg1, void *arg2)
{
    register u8 *var_s4 ASM_REG("$20") = arg0;
    register u8 *var_s2 ASM_REG("$18") = arg2;
    u8 **global = (u8 **)D_80083160;
    u8 *state = *global;
    u8 *scratch = (u8 *)0x1F800000;
    register u8 *packet ASM_REG("$16") = FIELD(state, u8 *, 0x8D0);
    register u8 *var_s1 ASM_REG("$17");
    register u8 *temp ASM_REG("$5");
    register u8 *ret_state ASM_REG("$3");
    s32 shifted = state != D_801C9E40;
    s16 value;
    s16 value2;
    u16 rect[4];

    FIELD(scratch, u8 *, 0x20) = state + 0xB0;
    FIELD(scratch, s32, 0x38) = 0x1000;
    FIELD(scratch, s32, 0x48) = 0;

    func_80067E2C(packet, state);
    func_8006658C(FIELD(scratch, u8 *, 0x20) + FIELD(arg1, s16, 0xA) * 4,
                  packet);

    FIELD(scratch, s32, 0x30) = FIELD(var_s2, u16, 0x1C);
    FIELD(scratch, s32, 0x34) = FIELD(var_s2, u16, 0x1E);
    FIELD(scratch, u16, 0) = FIELD(arg1, u16, 2);
    FIELD(scratch, u16, 2) = FIELD(arg1, u16, 6);
    var_s1 = FIELD(var_s2, u8 *, 8);
    FIELD(scratch, u16, 0x24) = FIELD(var_s2, u16, 0x14);
    func_800649A0();

    FIELD(scratch, u16, 0x98) = 0;
    FIELD(scratch, u16, 0x9A) = 0;
    FIELD(scratch, u16, 0x9C) = FIELD(D_80083160, u16, 0xC8);
    func_80065820(scratch + 0x98, scratch + 0xD0);
    func_80064BC0(scratch + 0xD0, scratch + 0x30);

    FIELD(scratch, s32, 0xEC) = 0;
    FIELD(scratch, s32, 0xE4) = FIELD(scratch, s16, 0);
    FIELD(scratch, s32, 0xE8) = (s16)FIELD(scratch, u16, 2);
    func_80064CF0(scratch + 0xD0);
    func_80064D80(scratch + 0xD0);

    FIELD(scratch, s16, 0x28) = 0x20 - FIELD(var_s2, u16, 0x20);
    FIELD(scratch, s16, 0x2A) = 0x20 - FIELD(var_s2, u16, 0x22);
    FIELD(scratch, s16, 0x2C) = 0;
    func_80065320(scratch + 0x28, scratch + 0x100, scratch + 0x94);

    packet += 0xC;
    FIELD(scratch, u16, 0x100) -= FIELD(scratch, u16, 0);
    FIELD(scratch, u16, 0x102) -= FIELD(scratch, u16, 2);

    FIELD(scratch, s32, 8) = FIELD(var_s1, u8, 8);
    FIELD(scratch, s32, 0xC) = FIELD(var_s1, u8, 9);
    FIELD(scratch, s32, 0x10) = FIELD(var_s1, u8, 0xA);
    FIELD(scratch, s32, 0x14) = FIELD(var_s1, u8, 0xB);

    value2 = (s8)FIELD(var_s1, u8, 2);
    FIELD(scratch, s16, 0x80) = value2;
    FIELD(scratch, s16, 0x70) = value2;
    value2 += VFIELD(scratch, u16, 0x10);
    FIELD(scratch, s16, 0x88) = value2;
    FIELD(scratch, s16, 0x78) = value2;

    value = (s8)FIELD(var_s1, u8, 3);
    FIELD(scratch, s16, 0x8C) = 0;
    FIELD(scratch, s16, 0x84) = 0;
    FIELD(scratch, s16, 0x7C) = 0;
    FIELD(scratch, s16, 0x74) = 0;
    FIELD(scratch, s16, 0x7A) = value;
    FIELD(scratch, s16, 0x72) = value;
    value += VFIELD(scratch, u16, 0x14);
    FIELD(scratch, s16, 0x8A) = value;
    FIELD(scratch, s16, 0x82) = value;

    func_80065320(scratch + 0x70, packet + 8, scratch + 0x94);
    func_80065320(scratch + 0x78, packet + 0x10, scratch + 0x94);
    func_80065320(scratch + 0x80, packet + 0x18, scratch + 0x94);
    func_80065320(scratch + 0x88, packet + 0x20, scratch + 0x94);

    FIELD(packet, u16, 8) += VFIELD(scratch, u16, 0x100);
    FIELD(packet, u16, 0x10) += VFIELD(scratch, u16, 0x100);
    FIELD(packet, u16, 0x18) += VFIELD(scratch, u16, 0x100);
    FIELD(packet, u16, 0x20) += VFIELD(scratch, u16, 0x100);
    FIELD(packet, u16, 0xA) += VFIELD(scratch, u16, 0x102);
    FIELD(packet, u16, 0x12) += VFIELD(scratch, u16, 0x102);
    FIELD(packet, u16, 0x1A) += VFIELD(scratch, u16, 0x102);
    FIELD(packet, u16, 0x22) += VFIELD(scratch, u16, 0x102);

    FIELD(scratch, s32, 0x10) += FIELD(scratch, s32, 8);
    FIELD(scratch, s32, 0x14) =
        (FIELD(scratch, s32, 0x14) + FIELD(scratch, s32, 0xC)) << 8;
    FIELD(scratch, s32, 0xC) <<= 8;

    FIELD(packet, u16, 0xE) = FIELD(var_s2, u16, 0x12) + FIELD(var_s1, u16, 6);
    FIELD(packet, u16, 0xC) = VFIELD(scratch, u16, 0xC) + VFIELD(scratch, u16, 8);
    FIELD(packet, s32, 0x14) = VFIELD(scratch, s32, 0xC) +
        VFIELD(scratch, s32, 0x10) +
        ((FIELD(var_s2, u16, 0x10) | FIELD(var_s1, s16, 4)) << 16);
    FIELD(packet, u16, 0x1C) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 8);
    FIELD(packet, u16, 0x24) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 0x10);
    FIELD(packet, s32, 4) = FIELD(var_s2, s32, 0xC);
    func_800666F4(packet);

    var_s2 = packet;
    var_s2 += 0x28;
    func_8003DB6C(var_s2, packet, 0xA);
    var_s1 = var_s2 + 0x28;
    FIELD(packet, u8, 7) |= 2;
    FIELD(var_s2, u8, 0xD) = (FIELD(var_s2, u8, 0x15) += 0x40);
    FIELD(var_s2, u8, 0x1D) = (FIELD(var_s2, u8, 0x25) += 0x40);
    FIELD(var_s2, u16, 0x16) |= 0x100;

    func_8006658C(FIELD(scratch, u8 *, 0x20) + FIELD(arg1, s16, 0xA) * 4,
                  var_s2);
    func_8006658C(FIELD(scratch, u8 *, 0x20) + FIELD(arg1, s16, 0xA) * 4,
                  var_s2 - 0x28);

    FIELD(var_s1, u32, 4) = 0x00606060;
    FIELD(var_s1, u32, 8) = FIELD(var_s1, u32, -0x20);
    FIELD(var_s1, u32, 0xC) = FIELD(var_s1, u32, -0x18);
    FIELD(var_s1, u32, 0x10) = FIELD(var_s1, u32, -0x10);
    FIELD(var_s1, u32, 0x14) = FIELD(var_s1, u32, -8);
    FIELD(var_s1, u8, 4) >>= 1;
    FIELD(var_s1, u8, 5) >>= 1;
    FIELD(var_s1, u8, 6) >>= 1;
    func_800666E0(var_s1);
    FIELD(var_s1, u8, 7) |= 2;

    temp = var_s1;
    var_s1 = var_s2 + 0x40;
    func_8006658C(FIELD(scratch, u8 *, 0x20) + FIELD(arg1, s16, 0xA) * 4,
                  temp);
    func_80067F20(var_s1, 0, 0, 0x40, 0);
    func_8006658C(FIELD(scratch, u8 *, 0x20) + FIELD(arg1, s16, 0xA) * 4,
                  var_s1);

    rect[0] = FIELD(var_s4, u16, 4);
    rect[1] = FIELD(var_s4, u16, 6);
    rect[2] = FIELD(var_s4, u16, 8);
    rect[3] = FIELD(var_s4, u16, 0xA);
    var_s1 = var_s2 + 0x4C;
    if (shifted) {
        rect[1] += 0xE0;
    }

    func_80067E2C(var_s1, rect);
    temp = var_s1;
    var_s1 = var_s2 + 0x58;
    ASM_KEEP(var_s1);
    func_8006658C(FIELD(scratch, u8 *, 0x20) + FIELD(arg1, s16, 0xA) * 4,
                  temp);
    ASM_KEEP(var_s4);
    ASM_KEEP(var_s2);
    ASM_KEEP(packet);
    func_80064A40();
    ret_state = *global;
    FIELD(ret_state, u8 *, 0x8D0) = var_s1;
    return 0;
}
