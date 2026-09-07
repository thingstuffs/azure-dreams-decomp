#include "common.h"

typedef struct S_8195F43C_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
    u8 pad_24[0x10];
    u32 unk_34;
    u8 pad_38[0x18];
    s16 unk_50;
    u8 pad_52[0x6];
    s16 unk_58;
    u8 pad_5A[0x16];
    s16 unk_70;
    s16 unk_72;
    s16 unk_74;
    u8 pad_76[0x2];
    s16 unk_78;
    s16 unk_7A;
    s16 unk_7C;
    u8 pad_7E[0x2];
    s16 unk_80;
    s16 unk_82;
    s16 unk_84;
    u8 pad_86[0x2];
    s16 unk_88;
    s16 unk_8A;
    s16 unk_8C;
    u8 pad_8E[0x32];
    u32 unk_C0;
    u8 pad_C4[0x20];
    s32 unk_E4;
    s32 unk_E8;
    s32 unk_EC;
} S_8195F43C_0;   /* scratch in func_8195F43C */

typedef struct S_8195F43C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195F43C_1;   /* arg1 in func_8195F43C */

typedef struct S_8195F43C_2 {
    u16 unk_00;
    u16 unk_02;
} S_8195F43C_2;   /* table in func_8195F43C */

typedef struct S_8195F43C_3 {
    u16 unk_00;
    u16 unk_02;
} S_8195F43C_3;   /* table2 in func_8195F43C */

typedef struct S_8195F43C_4 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8195F43C_4;   /* base in func_8195F43C */

typedef struct S_8195F43C_5 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u32 unk_0C;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8195F43C_5;   /* object in func_8195F43C */

typedef struct S_8195F43C_6 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    u16 unk_04;
    u8 pad_06[0x2];
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
} S_8195F43C_6;   /* texture in func_8195F43C */

typedef struct S_8195F43C_7 {
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_00;   /* overlapping accesses */
    union { struct { u32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    union { u16 u; s16 s; } unk_08;   /* accessed as both */
    union { u16 u; s16 s; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u8 unk_14;
    u8 pad_15[0x3];
    u16 unk_18;
    u16 unk_1A;
    u8 pad_1C[0x1];
    u8 unk_1D;
    u8 pad_1E[0x2];
    union { u16 u; s16 s; } unk_20;   /* accessed as both */
    union { u16 u; s16 s; } unk_22;   /* accessed as both */
    u8 unk_24;
    u8 unk_25;
} S_8195F43C_7;   /* packet in func_8195F43C */

typedef struct S_8195F43C_8 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_8195F43C_8;   /* *global in func_8195F43C */


#define VFIELD(p, type, offset) (*(volatile type *)((u8 *)(p) + (offset)))

extern void func_80024FEC(void) __attribute__((noreturn));
extern void func_80064840(void *, void *, void *);
extern void func_800649A0(void);
extern void func_80064A40(void);
extern void func_80064AE0(void *);
extern void func_80064BC0(void *, void *);
extern void func_80064CF0(void *);
extern void func_80064D80(void *);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void func_80065820(void *, void *);
extern u8 D_8002745C[];
extern u8 D_80083160[];

void func_8195F43C(void *arg0, void *arg1, u8 *object, s16 arg3, s16 arg4)
{
    u8 **global = (u8 **)D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *tableBase = D_8002745C;
    u8 *base;
    u8 *packet;
    u8 *texture;
    u8 *table;
    u8 *table2;
    u32 index;
    s16 x0;
    s16 x1;
    s16 y0;
    s16 y1;
    s32 visible0;
    s32 visible1;
    s32 visible2;
    s32 visible3;
    s32 visible01;
    s32 visible012;
    s32 temp;
    s32 temp2;
    u32 lowMask;
    u32 highMask;
    u16 objectValue;
    s32 objectY;

    (void)arg0;
    base = *global;
    ((S_8195F43C_0 *)scratch)->unk_20 = base + 0xB0;
    ((S_8195F43C_0 *)scratch)->unk_E4 = ((S_8195F43C_1 *)arg1)->unk_02 + ((arg3 - 3) << 6);
    ((S_8195F43C_0 *)scratch)->unk_E8 = ((S_8195F43C_1 *)arg1)->unk_06 + ((arg4 - 3) << 6);
    ((S_8195F43C_0 *)scratch)->unk_EC = ((S_8195F43C_1 *)arg1)->unk_0A;

    table = (u8 *)((u32)(arg4 * 2) +
        (u32)(tableBase + arg3 * 0x10));
    tableBase += 0x10;
    table2 = (u8 *)((u32)(arg4 * 2) +
        (u32)(tableBase + arg3 * 0x10));
    {
        register u32 rawTableValue ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

        rawTableValue = ((S_8195F43C_2 *)table)->unk_00;
        ((S_8195F43C_0 *)scratch)->unk_74 = (s16)rawTableValue / 2;
    }
    ((S_8195F43C_0 *)scratch)->unk_7C = (s16)((S_8195F43C_3 *)table2)->unk_00 / 2;
    ((S_8195F43C_0 *)scratch)->unk_84 = (s16)((S_8195F43C_2 *)table)->unk_02 / 2;
    ((S_8195F43C_0 *)scratch)->unk_8C = (s16)((S_8195F43C_3 *)table2)->unk_02 / 2;

    packet = ((S_8195F43C_4 *)base)->unk_8D0;
    func_800649A0();

    VFIELD(scratch, u32, 0x30) = ((S_8195F43C_5 *)object)->unk_1C * 2;
    objectY = ((S_8195F43C_5 *)object)->unk_1E;
    VFIELD(scratch, u32, 0x38) = 0x2000;
    VFIELD(scratch, u16, 0x102) = 0;
    VFIELD(scratch, u16, 0x104) = 0;
    VFIELD(scratch, u16, 0x100) = 0;
    ((S_8195F43C_0 *)scratch)->unk_34 = objectY * 2;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(scratch + 0x11C);
    func_80064840(scratch + 0x11C, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    texture = ((S_8195F43C_5 *)object)->unk_08;
    x0 = (s8)((S_8195F43C_6 *)texture)->unk_02;
    ((S_8195F43C_0 *)scratch)->unk_80 = x0;
    ((S_8195F43C_0 *)scratch)->unk_70 = x0;
    x1 = x0 + ((S_8195F43C_6 *)texture)->unk_0A;
    ((S_8195F43C_0 *)scratch)->unk_88 = x1;
    ((S_8195F43C_0 *)scratch)->unk_78 = x1;
    y0 = (s8)((S_8195F43C_6 *)texture)->unk_03;
    ((S_8195F43C_0 *)scratch)->unk_7A = y0;
    ((S_8195F43C_0 *)scratch)->unk_72 = y0;
    y1 = y0 + ((S_8195F43C_6 *)texture)->unk_0B;
    ((S_8195F43C_0 *)scratch)->unk_8A = y1;
    ((S_8195F43C_0 *)scratch)->unk_82 = y1;

    index = func_80065590(scratch + 0x70, scratch + 0x78,
                          scratch + 0x80, scratch + 0x88,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0x90, scratch + 0x94);
    ((S_8195F43C_0 *)scratch)->unk_C0 = index;

    if (index < 0x1E0U) {
        visible0 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_08.u + 0x20) < 0x181U) {
            visible0 = (u16)(((S_8195F43C_7 *)packet)->unk_0A.u + 0x20) < 0x121U;
        }
        visible1 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_10 + 0x20) < 0x181U) {
            visible1 = (u16)(((S_8195F43C_7 *)packet)->unk_12 + 0x20) < 0x121U;
        }
        visible01 = visible0 | visible1;
        visible2 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_18 + 0x20) < 0x181U) {
            visible2 = (u16)(((S_8195F43C_7 *)packet)->unk_1A + 0x20) < 0x121U;
        }
        visible012 = visible01 | visible2;
        visible3 = 0;
        if ((u16)(((S_8195F43C_7 *)packet)->unk_20.u + 0x20) < 0x181U) {
            visible3 = (u16)(((S_8195F43C_7 *)packet)->unk_22.u + 0x20) < 0x121U;
        }

        if ((visible012 | visible3) != 0) {
            VFIELD(scratch, s32, 8) = ((S_8195F43C_6 *)texture)->unk_08;
            VFIELD(scratch, s32, 0x10) = ((S_8195F43C_6 *)texture)->unk_0A;
            VFIELD(scratch, s32, 0xC) = ((S_8195F43C_6 *)texture)->unk_09;
            VFIELD(scratch, s32, 0x14) = ((S_8195F43C_6 *)texture)->unk_0B;

            ((S_8195F43C_7 *)packet)->unk_0E = ((S_8195F43C_5 *)object)->unk_12 + (*(u16 *)((u8 *)texture + 6));
            objectValue = ((S_8195F43C_5 *)object)->unk_10;
            if (objectValue != 0) {
                u32 tailValue;
                tailValue = objectValue + (((S_8195F43C_6 *)texture)->unk_04 & 0xFF9F);
                ASM_TAILSLOT_PIN(tailValue);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_80024FEC();
                return;
            }
            (*(u16 *)((u8 *)packet + 0x16)) = ((S_8195F43C_6 *)texture)->unk_04;

            {
                s32 low;
                s32 high;

                low = VFIELD(scratch, s32, 8);
                high = VFIELD(scratch, s32, 0x10);
                if (low + high >= 0x100) {
                    VFIELD(scratch, s32, 0x10) = high - 1;
                }
            }
            {
                s32 low;
                s32 high;

                low = VFIELD(scratch, s32, 0xC);
                high = VFIELD(scratch, s32, 0x14);
                if (low + high >= 0x100) {
                    VFIELD(scratch, s32, 0x14) = high - 1;
                }
            }

            {
                s32 y;
                u16 packed;
                register u16 packedOffset ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

                {
                    register s32 coord ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

                    {
                        s32 x;
                        register s32 dx ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                        x = VFIELD(scratch, s32, 0x10);
                        dx = VFIELD(scratch, s32, 8);
                        coord = VFIELD(scratch, s32, 0xC);
                        VFIELD(scratch, s32, 0x10) = x + dx;
                    }
                    {
                        register s32 shifted ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

                        shifted = coord;
                        ASM_USE(shifted);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                        y = VFIELD(scratch, s32, 0x14);
                        shifted <<= 8;
                        VFIELD(scratch, s32, 0xC) = shifted;
                        packed = VFIELD(scratch, u16, 0xC);
                        y += coord;
                    }
                }
                packedOffset = VFIELD(scratch, u16, 8);
                VFIELD(scratch, s32, 0x14) = y;
                VFIELD(scratch, s32, 0x14) = y << 8;
                (*(u16 *)((u8 *)packet + 0xC)) = packed + packedOffset;
            }
            (*(u16 *)((u8 *)packet + 0x14)) = VFIELD(scratch, u16, 0xC) + VFIELD(scratch, u16, 0x10);
            (*(u16 *)((u8 *)packet + 0x1C)) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 8);
            (*(u16 *)((u8 *)packet + 0x24)) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 0x10);

            if (((S_8195F43C_0 *)scratch)->unk_50 >= 0x1800) {
                temp = ((S_8195F43C_7 *)packet)->unk_24;
                {
                    s32 faded;

                    faded = temp + 0xFF;
                    ((S_8195F43C_7 *)packet)->unk_24 = faded;
                }
                ((S_8195F43C_7 *)packet)->unk_14 = temp;
            }
            if (((S_8195F43C_0 *)scratch)->unk_58 >= 0x1800) {
                temp = ((S_8195F43C_7 *)packet)->unk_25;
                {
                    s32 faded;

                    faded = temp + 0xFF;
                    ((S_8195F43C_7 *)packet)->unk_25 = faded;
                }
                ((S_8195F43C_7 *)packet)->unk_1D = temp;
            }
            if (((S_8195F43C_7 *)packet)->unk_08.s > ((S_8195F43C_7 *)packet)->unk_20.s) {
                ((S_8195F43C_7 *)packet)->unk_14--;
                ((S_8195F43C_7 *)packet)->unk_24--;
            }
            if (((S_8195F43C_7 *)packet)->unk_0A.s > ((S_8195F43C_7 *)packet)->unk_22.s) {
                ((S_8195F43C_7 *)packet)->unk_1D--;
                ((S_8195F43C_7 *)packet)->unk_25--;
            }

            ((S_8195F43C_7 *)packet)->unk_04.at00.v = ((S_8195F43C_5 *)object)->unk_0C;
            ((S_8195F43C_7 *)packet)->unk_00.at03.v = 9;
            ((S_8195F43C_7 *)packet)->unk_04.at03.v = 0x2C;
            if (((S_8195F43C_5 *)object)->unk_14 & 4) {
                ((S_8195F43C_7 *)packet)->unk_04.at03.v = 0x2E;
            }

            lowMask = 0x00FFFFFF;
            highMask = 0xFF000000;
            ((S_8195F43C_7 *)packet)->unk_00.at00.v = (((S_8195F43C_7 *)packet)->unk_00.at00.v & highMask) |
                ((*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20) + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) & lowMask);
            (*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20) + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) =
                ((*(u32 *)((u8 *)(((S_8195F43C_0 *)scratch)->unk_20) + ((S_8195F43C_0 *)scratch)->unk_C0 * 4)) & highMask) |
                ((u32)packet & lowMask);
            packet += 0x28;
        }
    }

    func_80064A40();
    ((S_8195F43C_8 *)(*global))->unk_8D0 = packet;
}
