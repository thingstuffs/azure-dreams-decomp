#include "common.h"

typedef struct S_800A17CC_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A17CC_0;   /* root in func_800A17CC */

typedef struct S_800A17CC_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    s8 unk_0C;
    s8 unk_0D;
    s16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    s8 unk_14;
    s8 unk_15;
    s16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    s8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x2];
    u16 unk_20;
    u8 pad_22[0x2];
    s8 unk_24;
    s8 unk_25;
} S_800A17CC_1;   /* packet40 in func_800A17CC */

typedef struct S_800A17CC_2 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x59];
    s16 unk_6C;
    s16 unk_6E;
    u8 unk_70;
    u8 pad_71[0x1];
    u8 unk_72;
    u8 pad_73[0x5];
    u16 unk_78;
    s16 unk_7A;
} S_800A17CC_2;   /* arg0 in func_800A17CC */

typedef struct S_800A17CC_3 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 pad_07[0x1];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
} S_800A17CC_3;   /* packet24 in func_800A17CC */


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
    u8 *root;
    u8 *packet40;
    u8 *packet24;
    u8 *packet12;
    EmptyArg empty;
    void *pE8;
    void *pEC;
    void *pF0;
    void *pF4;
    void *p94;
    void *p98;
    void *p84;
    void *p8C;
    s32 work_size;
    s32 color;
    u8 *call_packet;
    register u8 *scratch ASM_REG("$19");   /* MATCH pin: retail schedule: same instructions, different order without it */

    color = 0x800000;
    ASM_KEEP_NV(color);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    root = D_80083160;
    work_size = 0x80;
    work[1] = 0;
    work[0] = 0;
    work[2] = work_size;
    work[3] = work_size;

    packet40 = ((S_800A17CC_0 *)root)->unk_8D0;
    call_packet = packet40;
    ((S_800A17CC_0 *)root)->unk_8D0 = packet40 + 0x28;
    color |= 0x8080;
    ((S_800A17CC_1 *)packet40)->unk_04 = color;
    func_800666F4(call_packet, color);

    first_value = func_80066460(1, 0,
        ((S_800A17CC_2 *)arg0)->unk_6C & 0xFF80, ((S_800A17CC_2 *)arg0)->unk_6E);
    ((S_800A17CC_1 *)packet40)->unk_16 = first_value;
    ((S_800A17CC_1 *)packet40)->unk_0E = func_8006649C(0, 0x1EF);

    {
        s32 x1;
        s32 rem1;

        x1 = ((S_800A17CC_2 *)arg0)->unk_6C;
        ASM_KEEP_NV(x1);   /* MATCH pin: retail schedule: same instructions, different order without it */
        scratch = (u8 *)0x1F800000;
        ASM_KEEP(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
        rem1 = (s16)(x1 % 0x80);
        rem1 /= 2;
        ((S_800A17CC_1 *)packet40)->unk_1C = rem1;
        ((S_800A17CC_1 *)packet40)->unk_0C = rem1;
    }
    {
        s32 x2;
        s16 rem2;
        s32 result2;

        x2 = ((S_800A17CC_2 *)arg0)->unk_6C;
        rem2 = x2 % 0x80;
        result2 = (rem2 / 2) + ((S_800A17CC_2 *)arg0)->unk_70;
        ((S_800A17CC_1 *)packet40)->unk_24 = result2;
        ((S_800A17CC_1 *)packet40)->unk_14 = result2;
    }
    {
        s32 x3;
        s32 rem3;

        x3 = ((S_800A17CC_2 *)arg0)->unk_6E;
        rem3 = x3 % 0x100;
        ((S_800A17CC_1 *)packet40)->unk_15 = rem3;
        ((S_800A17CC_1 *)packet40)->unk_0D = rem3;
    }

    coord_y = ((S_800A17CC_2 *)arg0)->unk_6E;
    {
        s32 adjusted_y;

        adjusted_y = (coord_y % 0x100) + ((S_800A17CC_2 *)arg0)->unk_72;
        ((S_800A17CC_1 *)packet40)->unk_25 = adjusted_y;
        ((S_800A17CC_1 *)packet40)->unk_1D = adjusted_y;
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

        value1 = SCRATCH(u16, 0x74) - ((S_800A17CC_2 *)arg0)->unk_78;
        SCRATCH(u16, 0x74) = value1;
        SCRATCH(u16, 0x84) = value1;
    }
    {
        s32 value2;

        value2 = SCRATCH(u16, 0x7C) + ((S_800A17CC_2 *)arg0)->unk_78;
        p8C = (void *)0x1F80008C;
        SCRATCH(u16, 0x7C) = value2;
        SCRATCH(u16, 0x8C) = value2;
    }
    actor_y = ((S_800A17CC_2 *)arg0)->unk_7A;
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

    ((S_800A17CC_1 *)packet40)->unk_08 = SCRATCH(u16, 0xE8);
    ((S_800A17CC_1 *)packet40)->unk_0A = SCRATCH(u16, 0xEA);
    ((S_800A17CC_1 *)packet40)->unk_10 = SCRATCH(u16, 0xEC);
    ((S_800A17CC_1 *)packet40)->unk_12 = SCRATCH(u16, 0xEE);
    ((S_800A17CC_1 *)packet40)->unk_18 = SCRATCH(u16, 0xF0);
    ((S_800A17CC_1 *)packet40)->unk_1A = SCRATCH(u16, 0xF2);
    ((S_800A17CC_1 *)packet40)->unk_20 = SCRATCH(u16, 0xF4);
    (*(u16 *)((u8 *)packet40 + 0x22)) = SCRATCH(u16, 0xF6);

    root = D_80083160;
    packet24 = ((S_800A17CC_0 *)root)->unk_8D0;
    ((S_800A17CC_0 *)root)->unk_8D0 = packet24 + 0x18;
    ((S_800A17CC_3 *)packet24)->unk_04 = ((S_800A17CC_2 *)arg0)->unk_12;
    ((S_800A17CC_3 *)packet24)->unk_05 = ((S_800A17CC_2 *)arg0)->unk_12;
    ((S_800A17CC_3 *)packet24)->unk_06 = ((S_800A17CC_2 *)arg0)->unk_12;
    func_800666E0(packet24);
    func_80066640(packet24, 1);
    ((S_800A17CC_3 *)packet24)->unk_08 = SCRATCH(u16, 0xE8);
    ((S_800A17CC_3 *)packet24)->unk_0A = SCRATCH(u16, 0xEA);
    ((S_800A17CC_3 *)packet24)->unk_0C = SCRATCH(u16, 0xEC);
    ((S_800A17CC_3 *)packet24)->unk_0E = SCRATCH(u16, 0xEE);
    ((S_800A17CC_3 *)packet24)->unk_10 = SCRATCH(u16, 0xF0);
    ((S_800A17CC_3 *)packet24)->unk_12 = SCRATCH(u16, 0xF2);
    ((S_800A17CC_3 *)packet24)->unk_14 = SCRATCH(u16, 0xF4);
    (*(u16 *)((u8 *)packet24 + 0x16)) = SCRATCH(u16, 0xF6);

    root = D_80083160;
    SCRATCH(u32, 0x24) = (s32)(root + 0xB0);
    packet12 = ((S_800A17CC_0 *)root)->unk_8D0;
    ((S_800A17CC_0 *)root)->unk_8D0 = packet12 + 0xC;
    func_80067F20(packet12, 1, 0, first_value & 0xFFFF, &D_800D0A40);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet12);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet24);

    root = D_80083160;
    packet12 = ((S_800A17CC_0 *)root)->unk_8D0;
    ((S_800A17CC_0 *)root)->unk_8D0 = packet12 + 0xC;
    func_80067F20(packet12, 1, 0,
        func_80066460(0, 1, 0x140, 0) & 0xFFFF, 0);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet12);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet40);

    root = D_80083160;
    packet12 = ((S_800A17CC_0 *)root)->unk_8D0;
    ((S_800A17CC_0 *)root)->unk_8D0 = packet12 + 0xC;
    func_80067F20(packet12, 1, 0, first_value & 0xFFFF, work);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), packet12);
}
