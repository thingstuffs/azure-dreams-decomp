#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))
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
    FIELD(scratch, u8 *, 0x20) = base + 0xB0;
    FIELD(scratch, s32, 0xE4) = FIELD(arg1, s16, 2) + ((arg3 - 3) << 6);
    FIELD(scratch, s32, 0xE8) = FIELD(arg1, s16, 6) + ((arg4 - 3) << 6);
    FIELD(scratch, s32, 0xEC) = FIELD(arg1, s16, 0xA);

    table = (u8 *)((u32)(arg4 * 2) +
        (u32)(tableBase + arg3 * 0x10));
    tableBase += 0x10;
    table2 = (u8 *)((u32)(arg4 * 2) +
        (u32)(tableBase + arg3 * 0x10));
    {
        register u32 rawTableValue ASM_REG("$2");

        rawTableValue = FIELD(table, u16, 0);
        FIELD(scratch, s16, 0x74) = (s16)rawTableValue / 2;
    }
    FIELD(scratch, s16, 0x7C) = (s16)FIELD(table2, u16, 0) / 2;
    FIELD(scratch, s16, 0x84) = (s16)FIELD(table, u16, 2) / 2;
    FIELD(scratch, s16, 0x8C) = (s16)FIELD(table2, u16, 2) / 2;

    packet = FIELD(base, u8 *, 0x8D0);
    func_800649A0();

    VFIELD(scratch, u32, 0x30) = FIELD(object, u16, 0x1C) * 2;
    objectY = FIELD(object, u16, 0x1E);
    VFIELD(scratch, u32, 0x38) = 0x2000;
    VFIELD(scratch, u16, 0x102) = 0;
    VFIELD(scratch, u16, 0x104) = 0;
    VFIELD(scratch, u16, 0x100) = 0;
    FIELD(scratch, u32, 0x34) = objectY * 2;
    func_80065820(scratch + 0x100, scratch + 0xD0);
    func_80064AE0(scratch + 0x11C);
    func_80064840(scratch + 0x11C, scratch + 0xD0, scratch + 0x50);
    func_80064BC0(scratch + 0x50, scratch + 0x30);
    func_80064D80(scratch + 0x50);
    func_80064CF0(scratch + 0x50);

    texture = FIELD(object, u8 *, 8);
    x0 = (s8)FIELD(texture, u8, 2);
    FIELD(scratch, s16, 0x80) = x0;
    FIELD(scratch, s16, 0x70) = x0;
    x1 = x0 + FIELD(texture, u8, 0xA);
    FIELD(scratch, s16, 0x88) = x1;
    FIELD(scratch, s16, 0x78) = x1;
    y0 = (s8)FIELD(texture, u8, 3);
    FIELD(scratch, s16, 0x7A) = y0;
    FIELD(scratch, s16, 0x72) = y0;
    y1 = y0 + FIELD(texture, u8, 0xB);
    FIELD(scratch, s16, 0x8A) = y1;
    FIELD(scratch, s16, 0x82) = y1;

    index = func_80065590(scratch + 0x70, scratch + 0x78,
                          scratch + 0x80, scratch + 0x88,
                          packet + 8, packet + 0x10,
                          packet + 0x18, packet + 0x20,
                          scratch + 0x90, scratch + 0x94);
    FIELD(scratch, u32, 0xC0) = index;

    if (index < 0x1E0U) {
        visible0 = 0;
        if ((u16)(FIELD(packet, u16, 8) + 0x20) < 0x181U) {
            visible0 = (u16)(FIELD(packet, u16, 0xA) + 0x20) < 0x121U;
        }
        visible1 = 0;
        if ((u16)(FIELD(packet, u16, 0x10) + 0x20) < 0x181U) {
            visible1 = (u16)(FIELD(packet, u16, 0x12) + 0x20) < 0x121U;
        }
        visible01 = visible0 | visible1;
        visible2 = 0;
        if ((u16)(FIELD(packet, u16, 0x18) + 0x20) < 0x181U) {
            visible2 = (u16)(FIELD(packet, u16, 0x1A) + 0x20) < 0x121U;
        }
        visible012 = visible01 | visible2;
        visible3 = 0;
        if ((u16)(FIELD(packet, u16, 0x20) + 0x20) < 0x181U) {
            visible3 = (u16)(FIELD(packet, u16, 0x22) + 0x20) < 0x121U;
        }

        if ((visible012 | visible3) != 0) {
            VFIELD(scratch, s32, 8) = FIELD(texture, u8, 8);
            VFIELD(scratch, s32, 0x10) = FIELD(texture, u8, 0xA);
            VFIELD(scratch, s32, 0xC) = FIELD(texture, u8, 9);
            VFIELD(scratch, s32, 0x14) = FIELD(texture, u8, 0xB);

            FIELD(packet, u16, 0xE) = FIELD(object, u16, 0x12) + FIELD(texture, u16, 6);
            objectValue = FIELD(object, u16, 0x10);
            if (objectValue != 0) {
                register u32 tailValue ASM_REG("$2");
                tailValue = objectValue + (FIELD(texture, u16, 4) & 0xFF9F);
                ASM_TAILSLOT_PIN(tailValue);
                func_80024FEC();
                return;
            }
            FIELD(packet, u16, 0x16) = FIELD(texture, u16, 4);

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
                register s32 y ASM_REG("$2");
                register u16 packed ASM_REG("$3");
                register u16 packedOffset ASM_REG("$4");

                {
                    register s32 coord ASM_REG("$4");

                    {
                        s32 x;
                        register s32 dx ASM_REG("$3");

                        x = VFIELD(scratch, s32, 0x10);
                        dx = VFIELD(scratch, s32, 8);
                        coord = VFIELD(scratch, s32, 0xC);
                        VFIELD(scratch, s32, 0x10) = x + dx;
                    }
                    {
                        register s32 shifted ASM_REG("$3");

                        shifted = coord;
                        ASM_USE(shifted);
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
                FIELD(packet, u16, 0xC) = packed + packedOffset;
            }
            FIELD(packet, u16, 0x14) = VFIELD(scratch, u16, 0xC) + VFIELD(scratch, u16, 0x10);
            FIELD(packet, u16, 0x1C) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 8);
            FIELD(packet, u16, 0x24) = VFIELD(scratch, u16, 0x14) + VFIELD(scratch, u16, 0x10);

            if (FIELD(scratch, s16, 0x50) >= 0x1800) {
                temp = FIELD(packet, u8, 0x24);
                {
                    register s32 faded ASM_REG("$2");

                    faded = temp + 0xFF;
                    ASM_USE(faded);
                    FIELD(packet, u8, 0x24) = faded;
                }
                FIELD(packet, u8, 0x14) = temp;
            }
            if (FIELD(scratch, s16, 0x58) >= 0x1800) {
                temp = FIELD(packet, u8, 0x25);
                {
                    register s32 faded ASM_REG("$2");

                    faded = temp + 0xFF;
                    ASM_USE(faded);
                    FIELD(packet, u8, 0x25) = faded;
                }
                FIELD(packet, u8, 0x1D) = temp;
            }
            if (FIELD(packet, s16, 8) > FIELD(packet, s16, 0x20)) {
                FIELD(packet, u8, 0x14)--;
                FIELD(packet, u8, 0x24)--;
            }
            if (FIELD(packet, s16, 0xA) > FIELD(packet, s16, 0x22)) {
                FIELD(packet, u8, 0x1D)--;
                FIELD(packet, u8, 0x25)--;
            }

            FIELD(packet, u32, 4) = FIELD(object, u32, 0xC);
            FIELD(packet, u8, 3) = 9;
            FIELD(packet, u8, 7) = 0x2C;
            if (FIELD(object, u16, 0x14) & 4) {
                FIELD(packet, u8, 7) = 0x2E;
            }

            lowMask = 0x00FFFFFF;
            highMask = 0xFF000000;
            FIELD(packet, u32, 0) = (FIELD(packet, u32, 0) & highMask) |
                (FIELD(FIELD(scratch, u8 *, 0x20), u32,
                       FIELD(scratch, u32, 0xC0) * 4) & lowMask);
            FIELD(FIELD(scratch, u8 *, 0x20), u32,
                  FIELD(scratch, u32, 0xC0) * 4) =
                (FIELD(FIELD(scratch, u8 *, 0x20), u32,
                       FIELD(scratch, u32, 0xC0) * 4) & highMask) |
                ((u32)packet & lowMask);
            packet += 0x28;
        }
    }

    func_80064A40();
    FIELD(*global, u8 *, 0x8D0) = packet;
}
