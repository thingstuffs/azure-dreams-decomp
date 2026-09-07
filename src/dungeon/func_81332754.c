#include "common.h"

extern s32 D_800814A0;
extern void *D_80164900[];

extern s32 rand(void);
extern void func_800A56E0(s32);
extern void func_801656F8(void *, s32, s32, s32, s32, s32, s32);
extern void func_8016583C(void *, s32, s32, s32, s32, s32, s32);
extern void func_80165D0C(void *, s32, s32, s32, s32, s32, s32);
extern void func_80165F00(void *);
extern void func_8016604C(void *);
extern void func_80166204(void *, s32, s32, s32, s32, s32, s32);

void func_80169754(void *arg0)
{
    u8 *p = arg0;
    s32 i;
    s32 state;

    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c34, &&jt_c34
    };
    (void)jt_keep;

    state = *(s16 *)(p + 0x12);
    if ((u32)state >= 5) {
        goto done;
    }
    goto *D_80164900[(u32)state];

jt_c0:
        *(u16 *)(p + 0x12) += 1;
        *(s32 *)(p + 0x64) = (s32)0xFFE80000;

jt_c1:
    {
        u16 old;
        s32 next;
        s32 under;

        for (i = 0; i < 3; i++) {
            s32 x;
            s32 y;
            x = (s16)((rand() & 0xF) - 8);
            y = (s16)((rand() & 0xF) - 8);
            func_801656F8(p - 0x20, 0, 0x2040F0, x, y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(p + 0x64));
        }

        for (i = 0; i < 5; i++) {
            s32 x;
            s32 y;
            x = (s16)((rand() & 0xF) - 8);
            y = (s16)((rand() & 0xF) - 8);
            func_8016583C(p - 0x20, 0, 0x2020F0, x, y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(p + 0x64));
        }

        for (i = 0; i < 4; i++) {
            s32 x;
            s32 y;
            x = (s16)((rand() & 0xF) - 8);
            y = (s16)((rand() & 0xF) - 8);
            func_80166204(p - 0x20, 0, 0x2020F0, x, y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(p + 0x64));
        }

        *(s32 *)(p + 0x64) += 0xA000;
        {
            s32 x;
            s32 y;
            x = (s16)((rand() & 0xF) - 8);
            y = (s16)((rand() & 0xF) - 8);
            func_80165D0C(p - 0x20, 0, 0x2020F0, x, y,
                         ~((~(rand() & 0xF)) & 0x3F),
                         *(s32 *)(p + 0x64));
        }

        if ((*(u16 *)(p + 0x18) & 7) == 0) {
            func_800A56E0(0x81D);
        }
        old = *(u16 *)(p + 0x18);
        next = old + 1;
        under = (s16)old < 0x14;
        goto increment_common;

jt_c2:
        for (i = 0; i < 2; i++) {
            s32 x;
            s32 y;
            x = (s16)((rand() & 0xF) - 8);
            y = (s16)((rand() & 0xF) - 8);
            func_8016583C(p - 0x20, 0, 0x2020F0, x, y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(p + 0x64));
        }
        for (i = 0; i < 2; i++) {
            s32 x;
            s32 y;
            x = (s16)((rand() & 0xF) - 8);
            y = (s16)((rand() & 0xF) - 8);
            func_80166204(p - 0x20, 0, 0x2020F0, x, y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(p + 0x64));
        }
        *(s32 *)(p + 0x64) += 0x2000;
        if ((u16)(*(u16 *)(p + 0x18) - 0xF) < 0xB) {
            func_8016604C(p - 0x20);
        }
        if (*(s16 *)(p + 0x18) == 0xF ||
            *(s16 *)(p + 0x18) == 0x14 ||
            *(s16 *)(p + 0x18) == 0x19) {
            func_80165F00(p - 0x20);
        }
        if (*(s16 *)(p + 0x18) < 0x1F &&
            (*(u16 *)(p + 0x18) & 1) == 0) {
            s32 x;
            s32 y;
            x = (s16)((rand() & 0xF) - 8);
            y = (s16)((rand() & 0xF) - 8);
            func_80165D0C(p - 0x20, 0, 0x2020F0, x, y,
                         (rand() & 0xF) | -0x40,
                         *(s32 *)(p + 0x64));
        }
        if ((*(u16 *)(p + 0x18) & 7) == 0) {
            func_800A56E0(0x81D);
        }
        old = *(u16 *)(p + 0x18);
        next = old + 1;
        under = (s16)old < 0x28;

increment_common:
        *(u16 *)(p + 0x18) = next;
        if (under) {
            goto done;
        }
        *(u16 *)(p + 0x18) = 0;
        *(u16 *)(p + 0x12) += 1;
        goto done;
    }

jt_c34:
    {
        u16 old;
        s32 next;
        s32 under;

        old = *(u16 *)(p + 0x18);
        next = old + 1;
        under = (s16)old < 0xA;
        goto increment_short;

increment_short:
        *(u16 *)(p + 0x18) = next;
        if (!under) {
            *(u16 *)(p - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }

done:
        return;
}
