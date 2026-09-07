#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern u8 D_80083160[];
extern s32 rand(void);
extern s32 func_80065530(void *, void *, void *, void *, void *, void *, void *, void *);

void func_80175A90(void *arg0, void *arg1)
{
    void **context_p = (void **)D_80083160;
    u8 *scratch = (u8 *)0x1F800000;
    u8 *prim;
    s32 i = 0;
    s32 color = 0xC0;
    u32 mask = 0x00FFFFFF;
    u32 high_mask = 0xFF000000;

    FIELD(scratch, void *, 0x18) = (u8 *)*context_p + 0xB0;

    do {
        void *context = *context_p;
        s32 amount;

        prim = FIELD(context, u8 *, 0x8D0);
        FIELD(context, u8 *, 0x8D0) = prim + 0x20;

        FIELD(prim, u8, 7) = 0x58;
        FIELD(prim, u8, 3) = 7;
        FIELD(prim, u32, 0x1C) = 0x55555555;
        FIELD(prim, u8, 7) |= 2;

        FIELD(scratch, u16, 0x64) = FIELD(arg0, u16, 2);
        FIELD(scratch, u16, 0x66) = FIELD(arg0, u16, 6);
        FIELD(scratch, u16, 0x68) = FIELD(arg0, u16, 0xA);

        FIELD(scratch, s16, 0x6C) =
            (FIELD(arg0, s16, 2) + FIELD(arg1, s16, 2)) / 2;
        FIELD(scratch, s16, 0x6E) =
            (FIELD(arg0, s16, 6) + FIELD(arg1, s16, 6)) / 2;
        FIELD(scratch, s16, 0x70) =
            (FIELD(arg0, s16, 0xA) + FIELD(arg1, s16, 0xA)) / 2;

        FIELD(scratch, u16, 0x74) = FIELD(arg1, u16, 2);
        FIELD(scratch, u16, 0x76) = FIELD(arg1, u16, 6);
        FIELD(scratch, u16, 0x78) = FIELD(arg1, u16, 0xA);

        amount = (rand() % 9) + 4;
        switch (i) {
        case 0:
            FIELD(scratch, u16, 0x64) -= 2;
            FIELD(scratch, u16, 0x6C) += amount;
            FIELD(scratch, u16, 0x74) -= amount;
            break;
        case 1:
            FIELD(scratch, u16, 0x66) -= 2;
            FIELD(scratch, u16, 0x6E) += amount;
            FIELD(scratch, u16, 0x76) -= amount;
            break;
        case 2:
            FIELD(scratch, u16, 0x68) -= 2;
            FIELD(scratch, u16, 0x70) += amount;
            FIELD(scratch, u16, 0x78) -= amount;
            break;
        case 3:
            FIELD(scratch, u16, 0x64) += 2;
            FIELD(scratch, u16, 0x6C) -= amount;
            FIELD(scratch, u16, 0x74) += amount;
            break;
        case 4:
            FIELD(scratch, u16, 0x66) += 2;
            FIELD(scratch, u16, 0x6E) -= amount;
            FIELD(scratch, u16, 0x76) += amount;
            break;
        case 5:
            FIELD(scratch, u16, 0x68) += 2;
            FIELD(scratch, u16, 0x70) -= amount;
            FIELD(scratch, u16, 0x78) += amount;
            break;
        case 6:
            break;
        }

        FIELD(prim, u8, 5) = 0x40;
        FIELD(prim, u8, 6) = 0x40;
        FIELD(prim, u8, 0xC) = 0x40;
        FIELD(prim, u8, 0x15) = 0x40;
        FIELD(prim, u8, 0x16) = 0x40;
        FIELD(prim, u8, 4) = color;
        FIELD(prim, u8, 0xD) = 0;
        FIELD(prim, u8, 0xE) = 0;
        FIELD(prim, u8, 0x14) = color;

        FIELD(scratch, s32, 0xB4) = func_80065530(
            scratch + 0x64, scratch + 0x6C, scratch + 0x74,
            scratch + 0xD8, scratch + 0xDC, scratch + 0xE0,
            scratch + 0x84, scratch + 0x88);

        FIELD(prim, u16, 8) = FIELD(scratch, u16, 0xD8);
        FIELD(prim, u16, 0xA) = FIELD(scratch, u16, 0xDA);
        FIELD(prim, u16, 0x10) = FIELD(scratch, u16, 0xDC);
        FIELD(prim, u16, 0x12) = FIELD(scratch, u16, 0xDE);
        FIELD(prim, u16, 0x18) = FIELD(scratch, u16, 0xE0);
        FIELD(prim, u16, 0x1A) = FIELD(scratch, u16, 0xE2);

        {
            u32 otz = FIELD(scratch, u32, 0xB4);
            if (otz < 0x1E0) {
                FIELD(prim, u32, 0) =
                    (FIELD(prim, u32, 0) & high_mask) |
                    (FIELD(FIELD(scratch, u32 *, 0x18), u32, otz * 4) & mask);
                FIELD(FIELD(scratch, u32 *, 0x18), u32,
                      FIELD(scratch, u32, 0xB4) * 4) =
                    (FIELD(FIELD(scratch, u32 *, 0x18), u32,
                           FIELD(scratch, u32, 0xB4) * 4) & high_mask) |
                    ((u32)prim & mask);
            }
        }

        i++;
    } while (i < 7);
}
