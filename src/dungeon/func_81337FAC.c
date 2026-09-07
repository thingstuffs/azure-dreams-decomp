#include "common.h"

extern void func_8009A028(void *);
extern u16 func_800A0818(u8, u8, u8, u8, s32 *);
extern void func_80164BA4(void *);
extern void func_8017394C(void);

extern u16 D_80013714;
extern s16 D_80013716;
extern s16 D_80013718;
extern s16 D_8001371A;
extern void *D_8001371C;
extern u8 D_80082E80[];
extern u8 D_80083460[];
extern u16 D_800834E2;
extern s32 D_800E296C;
extern u8 D_80173C8C[];
extern u8 D_80173D74[];
extern u8 *D_80175D50[3];
extern s32 D_80175DC4;
extern s16 D_80175DC8;

void func_8016EFAC(void)
{
    s32 stack_arg;
    s32 i;
    u16 result;
    u8 *page;
    u8 *page137;
    u8 *object;
    u8 *target;
    u8 *nested;
    u8 *entry;
    u8 *record;
    u8 *page83460;
    u32 high_bit;

    i = 0;
    page = (u8 *)0x800E0000;
    page137 = (u8 *)0x80010000;
    high_bit = 0x80000000;
    D_80175D50[0][0xCF] = 1;
    *(s16 *)(page137 + 0x371A) = 0;
    *(s16 *)(page137 + 0x3718) = 0;
    *(s16 *)(page137 + 0x3716) = 0;
    page83460 = D_80083460;
    *(u16 *)(page83460 + 0xA) = *(u16 *)(page83460 + 0xA) - 1;
    *(u16 *)(page137 + 0x3714) =
        (*(u16 *)(page137 + 0x3714) | 9) & 0xFFEF;
    *(void **)(page137 + 0x371C) =
        *(void **)(D_80173C8C + ((D_800834E2 >> 7) & 0x1C));
    object = D_80175D50[0];
    nested = *(u8 **)(object + 0xC);
    D_800E296C |= 0x200000;
    target = object + 0x20;
    result = func_800A0818(nested[0x24], nested[0x25],
                           D_80082E80[0x24], D_80082E80[0x25], &stack_arg);
    *(u16 *)(target + 0x2A) = result;
    D_80175DC8 = 0;
    D_80175DC4 =
        *(s32 *)(D_80173D74 + ((result >> 7) & 0x1C));

    do {
        entry = *(u8 **)(page + 0x3D7C) + i * 4;
        record = *(u8 **)(entry + 0xAC);
        if (record != 0) {
            func_80164BA4(record);
            entry = *(u8 **)(page + 0x3D7C) + i * 4;
            func_8009A028(*(void **)(entry + 0xAC));
            entry = *(u8 **)(page + 0x3D7C) + i * 4;
            record = *(u8 **)(entry + 0xAC) - 0x20;
            *(u32 *)(record + 0x10) |= high_bit;
        }
        i++;
    } while (i < 2);
    func_8017394C();
}

/* MECHANISM: The 0x800e page is held across the loop while the high-bit literal
   stays live across calls; separate scalar globals expose the retail hi/lo CSE.
   A five-argument call owns the 0x18 stack local and forces the 0x38 frame. */
