#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
#define SCRATCH(type, offset) (*(type *)((u8 *)scratch + (offset)))
#define VSCRATCH(type, offset) (*(volatile type *)((u8 *)scratch + (offset)))

typedef struct {} EmptyArg;

extern s32 func_800654B0();
extern s32 func_80066460();
extern s32 func_8006649C();
extern void func_8006658C();
extern void func_80066640();
extern void func_800666E0();
extern void func_800666F4();
extern void func_80067F20();
extern void func_800A130C();
extern void func_800A1330();
extern u8 *D_80083160;
extern u8 D_1F800000[];
extern s16 D_800D0A40;

void func_800A17CC(void *arg0, s32 arg1) {
    s16 work[4];
    s32 first_value;
    s32 coord_y;
    s32 actor_y;
    register s32 value3;
    register u8 *root ASM_REG("$3");
    u8 *packet40;
    u8 *packet24;
    u8 *packet12;
    EmptyArg empty;
    register void *pE8 ASM_REG("$13");
    register void *pEC ASM_REG("$12");
    register void *pF0 ASM_REG("$11");
    register void *pF4 ASM_REG("$10");
    register void *p94 ASM_REG("$9");
    register void *p98 ASM_REG("$8");
    void *p84;
    void *p8C;
    register s32 work_size ASM_REG("$2");
    register s32 color ASM_REG("$5");
    register u8 *call_packet ASM_REG("$4");
    register u8 *scratch ASM_REG("$19");

    color = 0x800000;
    ASM_KEEP_NV(color);
    root = D_80083160;
    work_size = 0x80;
    work[1] = 0;
    work[0] = 0;
    work[2] = work_size;
    work[3] = work_size;

    packet40 = FIELD(root, u8 *, 0x8D0);
    call_packet = packet40;
    ASM_KEEP_NV(call_packet);
    FIELD(root, u8 *, 0x8D0) = packet40 + 0x28;
    color |= 0x8080;
    ASM_KEEP(color);
    FIELD(packet40, s32, 4) = color;
    func_800666F4(call_packet, color);

    first_value = func_80066460(1, 0,
        FIELD(arg0, s16, 0x6C) & 0xFF80, FIELD(arg0, s16, 0x6E));
    FIELD(packet40, s16, 0x16) = first_value;
    FIELD(packet40, s16, 0xE) = func_8006649C(0, 0x1EF);

    {
        s32 x1;
        s32 rem1;

        x1 = FIELD(arg0, s16, 0x6C);
        ASM_KEEP_NV(x1);
        scratch = (u8 *)0x1F800000;
        ASM_KEEP(scratch);
        rem1 = (s16)(x1 % 0x80);
        rem1 /= 2;
        FIELD(packet40, s8, 0x1C) = rem1;
        FIELD(packet40, s8, 0xC) = rem1;
    }
    {
        s32 x2;
        s16 rem2;
        s32 result2;

        x2 = FIELD(arg0, s16, 0x6C);
        rem2 = x2 % 0x80;
        result2 = (rem2 / 2) + FIELD(arg0, u8, 0x70);
        FIELD(packet40, s8, 0x24) = result2;
        FIELD(packet40, s8, 0x14) = result2;
    }
    {
        s32 x3;
        s32 rem3;

        x3 = FIELD(arg0, s16, 0x6E);
        rem3 = x3 % 0x100;
        FIELD(packet40, s8, 0x15) = rem3;
        FIELD(packet40, s8, 0xD) = rem3;
    }

    coord_y = FIELD(arg0, s16, 0x6E);
    {
        s32 adjusted_y;

        adjusted_y = (coord_y % 0x100) + FIELD(arg0, u8, 0x72);
        FIELD(packet40, s8, 0x25) = adjusted_y;
        FIELD(packet40, s8, 0x1D) = adjusted_y;
    }

    func_800A130C((void *)0x1F800074, arg1, coord_y);
    func_800A130C((void *)0x1F80007C, arg1);
    func_800A130C((void *)0x1F800084, arg1);
    func_800A1330((void *)0x1F80008C, (void *)0x1F800074);

    pE8 = (void *)0x1F8000E8;
    pEC = (void *)0x1F8000EC;
    pF0 = (void *)0x1F8000F0;
    pF4 = (void *)0x1F8000F4;
    p94 = (void *)0x1F800094;
    p98 = (void *)0x1F800098;
    ASM_KEEP_NV(pE8);
    ASM_KEEP_NV(pEC);
    ASM_KEEP_NV(pF0);
    ASM_KEEP_NV(pF4);
    ASM_KEEP_NV(p94);
    ASM_KEEP_NV(p98);

    {
        s32 value0;

        value0 = SCRATCH(u16, 0x8E) - 0x30;
        p84 = (void *)0x1F800084;
        SCRATCH(u16, 0x8E) = value0;
        SCRATCH(u16, 0x86) = value0;
        SCRATCH(u16, 0x7E) = value0;
        SCRATCH(u16, 0x76) = value0;
    }
    {
        s32 value1;

        value1 = SCRATCH(u16, 0x74) - FIELD(arg0, u16, 0x78);
        SCRATCH(u16, 0x74) = value1;
        SCRATCH(u16, 0x84) = value1;
    }
    {
        s32 value2;

        value2 = SCRATCH(u16, 0x7C) + FIELD(arg0, u16, 0x78);
        p8C = (void *)0x1F80008C;
        SCRATCH(u16, 0x7C) = value2;
        SCRATCH(u16, 0x8C) = value2;
    }
    actor_y = FIELD(arg0, s16, 0x7A);
    SCRATCH(s32, 0xC4) = func_800654B0(
        (void *)0x1F800074, (void *)0x1F80007C,
        p84, p8C,
        pE8, pEC, pF0, pF4, p94, p98,
        (value3 = SCRATCH(u16, 0x78),
            actor_y *= 2,
            value3 -= actor_y,
            SCRATCH(u16, 0x78) = value3,
            SCRATCH(u16, 0x80) = value3,
            empty)) - 8;

    FIELD(packet40, u16, 8) = SCRATCH(u16, 0xE8);
    FIELD(packet40, u16, 0xA) = SCRATCH(u16, 0xEA);
    FIELD(packet40, u16, 0x10) = SCRATCH(u16, 0xEC);
    FIELD(packet40, u16, 0x12) = SCRATCH(u16, 0xEE);
    FIELD(packet40, u16, 0x18) = SCRATCH(u16, 0xF0);
    FIELD(packet40, u16, 0x1A) = SCRATCH(u16, 0xF2);
    FIELD(packet40, u16, 0x20) = SCRATCH(u16, 0xF4);
    FIELD(packet40, u16, 0x22) = SCRATCH(u16, 0xF6);

    root = D_80083160;
    packet24 = FIELD(root, u8 *, 0x8D0);
    FIELD(root, u8 *, 0x8D0) = packet24 + 0x18;
    FIELD(packet24, u8, 4) = FIELD(arg0, u8, 0x12);
    FIELD(packet24, u8, 5) = FIELD(arg0, u8, 0x12);
    FIELD(packet24, u8, 6) = FIELD(arg0, u8, 0x12);
    func_800666E0(packet24);
    func_80066640(packet24, 1);
    FIELD(packet24, u16, 8) = SCRATCH(u16, 0xE8);
    FIELD(packet24, u16, 0xA) = SCRATCH(u16, 0xEA);
    FIELD(packet24, u16, 0xC) = SCRATCH(u16, 0xEC);
    FIELD(packet24, u16, 0xE) = SCRATCH(u16, 0xEE);
    FIELD(packet24, u16, 0x10) = SCRATCH(u16, 0xF0);
    FIELD(packet24, u16, 0x12) = SCRATCH(u16, 0xF2);
    FIELD(packet24, u16, 0x14) = SCRATCH(u16, 0xF4);
    FIELD(packet24, u16, 0x16) = SCRATCH(u16, 0xF6);

    root = D_80083160;
    SCRATCH(u32, 0x24) = (s32)(root + 0xB0);
    packet12 = FIELD(root, u8 *, 0x8D0);
    FIELD(root, u8 *, 0x8D0) = packet12 + 0xC;
    func_80067F20(packet12, 1, 0, first_value & 0xFFFF, &D_800D0A40);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet12);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet24);

    root = D_80083160;
    packet12 = FIELD(root, u8 *, 0x8D0);
    FIELD(root, u8 *, 0x8D0) = packet12 + 0xC;
    func_80067F20(packet12, 1, 0,
        func_80066460(0, 1, 0x140, 0) & 0xFFFF, 0);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet12);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet40);

    root = D_80083160;
    packet12 = FIELD(root, u8 *, 0x8D0);
    FIELD(root, u8 *, 0x8D0) = packet12 + 0xC;
    func_80067F20(packet12, 1, 0, first_value & 0xFFFF, work);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet12);
}
