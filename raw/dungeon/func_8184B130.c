#include "common.h"

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern u32 func_80065590(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern u8 D_80083160[];

s32 func_80024930(void *arg0, void *arg1, s32 arg2, s16 arg3,
                  s32 arg4, s16 arg5, u8 arg6, u8 arg7)
{
    u8 *scratch = (u8 *)0x1F800000;
    s32 edge;
    s16 i;
    void **global_page = (void **)D_80083160;

    FIELD(scratch, void *, 0x18) = (u8 *)(*global_page) + 0xB0;
    edge = FIELD(arg1, u16, 0xA) - arg4 + 1;
    FIELD(scratch, s16, 0x70) = edge;
    FIELD(scratch, s16, 0x68) = edge;
    edge = FIELD(arg1, u16, 0xA);
    FIELD(scratch, s16, 0x78) = edge;
    FIELD(scratch, s16, 0x80) = edge;

    for (i = 0; i < 16; i++) {
        register u8 *prim;
        register s32 angle1 ASM_REG("$16");
        register s32 scaled ASM_REG("$2");
        register s32 rawAngle ASM_REG("$4");
        register s32 adjusted ASM_REG("$5");
        s32 angle0;

        prim = FIELD(*global_page, u8 *, 0x8D0);
        ASM_KEEP(prim);

        FIELD(*global_page, u8 *, 0x8D0) = prim + 0x34;
        FIELD(prim, u8, 3) = 12;
        FIELD(prim, u8, 7) = 0x3C;

        if (arg6 == 4) {
            FIELD(prim, u16, 0x1A) = func_80066460(0, 0, 0x280, 0x100);
        } else {
            FIELD(prim, u8, 7) = 0x3E;
            FIELD(prim, u16, 0x1A) =
                func_80066460(0, arg6, 0x280, 0x100);
        }

        {
            register s32 flag ASM_REG("$3") = 0x3F;

            FIELD(prim, u8, 0xC) = 0;
            FIELD(prim, u8, 0x18) = flag;
            FIELD(prim, u8, 0x24) = 0;
            FIELD(prim, u8, 0x30) = flag;
        }
        FIELD(prim, u8, 4) = 0;
        FIELD(prim, u8, 5) = 0;
        FIELD(prim, u8, 6) = 0;
        FIELD(prim, u8, 0x10) = 0;
        FIELD(prim, u8, 0x11) = 0;
        FIELD(prim, u8, 0x12) = 0;
        FIELD(prim, u8, 0x1C) = arg7;
        FIELD(prim, u8, 0x1D) = arg7;
        FIELD(prim, u8, 0x1E) = arg7;
        FIELD(prim, u8, 0x28) = arg7;
        FIELD(prim, u8, 0x29) = arg7;
        FIELD(prim, u8, 0x2A) = arg7;

        scaled = (s16)i * 0x100;
        ASM_KEEP_NV(scaled);
        rawAngle = scaled + arg3;
        adjusted = rawAngle;
        ASM_KEEP_NV(adjusted);
        FIELD(prim, u16, 0xE) = 0x7E00;
        FIELD(prim, u8, 0xD) = 0x80;
        FIELD(prim, u8, 0x19) = 0x80;
        FIELD(prim, u8, 0x25) = 0xBF;
        FIELD(prim, u8, 0x31) = 0xBF;
        if (rawAngle < 0) {
            adjusted = rawAngle + 0xFFF;
        }
        scaled = (adjusted >> 12) << 12;
        ASM_KEEP_NV(scaled);
        angle0 = rawAngle - scaled;

        FIELD(scratch, s16, 0x74) = FIELD(arg1, u16, 2) +
            ((func_800644B8(angle0) >> 4) * arg5 >> 8);
        FIELD(scratch, s16, 0x64) = FIELD(scratch, s16, 0x74);

        angle1 = ((((s16)i + 1) % 16) * 0x100 + arg3) % 0x1000;
        ASM_KEEP(angle1);
        FIELD(scratch, s16, 0x7C) = FIELD(arg1, u16, 2) +
            ((func_800644B8(angle1) >> 4) * arg5 >> 8);
        FIELD(scratch, s16, 0x6C) = FIELD(scratch, s16, 0x7C);

        FIELD(scratch, s16, 0x76) = FIELD(arg1, u16, 6) +
            ((func_80064584(angle0) >> 4) * arg5 >> 8);
        FIELD(scratch, s16, 0x66) = FIELD(scratch, s16, 0x76);

        FIELD(scratch, s16, 0x7E) = FIELD(arg1, u16, 6) +
            ((func_80064584(angle1) >> 4) * arg5 >> 8);
        FIELD(scratch, s16, 0x6E) = FIELD(scratch, s16, 0x7E);

        FIELD(scratch, u32, 0xB4) = func_80065590(
            scratch + 0x64, scratch + 0x6C, scratch + 0x74, scratch + 0x7C,
            scratch + 0xD8, scratch + 0xDC, scratch + 0xE0, scratch + 0xE4,
            scratch + 0x84, scratch + 0x88);

        FIELD(prim, u16, 8) = FIELD(scratch, u16, 0xD8);
        FIELD(prim, u16, 0xA) = FIELD(scratch, u16, 0xDA);
        FIELD(prim, u16, 0x14) = FIELD(scratch, u16, 0xDC);
        FIELD(prim, u16, 0x16) = FIELD(scratch, u16, 0xDE);
        FIELD(prim, u16, 0x20) = FIELD(scratch, u16, 0xE0);
        FIELD(prim, u16, 0x22) = FIELD(scratch, u16, 0xE2);
        FIELD(prim, u16, 0x2C) = FIELD(scratch, u16, 0xE4);
        FIELD(prim, u16, 0x2E) = FIELD(scratch, u16, 0xE6);

        {
            u32 index = FIELD(scratch, u32, 0xB4);

            if (index < 0x1E0U) {
                register u32 lowMask ASM_REG("$4") = 0x00FFFFFFU;
                u32 offset = index * 4;

                index = 0xFF000000U;
                offset += (u32)FIELD(scratch, u8 *, 0x18);
                FIELD(prim, u32, 0) = (FIELD(prim, u32, 0) & index) |
                    (FIELD((void *)offset, u32, 0) & lowMask);
                FIELD(FIELD(scratch, u8 *, 0x18), u32,
                      FIELD(scratch, u32, 0xB4) * 4) =
                    (FIELD(FIELD(scratch, u8 *, 0x18), u32,
                           FIELD(scratch, u32, 0xB4) * 4) & index) |
                    ((u32)prim & lowMask);
            }
        }
    }

    return 0;
}
