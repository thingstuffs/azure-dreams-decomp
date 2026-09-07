#include "common.h"

extern u16 D_80111FA8[];
extern u8 D_80110EC8[];
extern u8 D_801110C8[];
extern u8 D_801112C8[];
extern u8 D_801114C8[];
extern void *D_800893A0[];

extern void func_800B7F58(void *, void *);
extern void LoadImage(void *, void *);

void func_800B7E78(u16 *arg0) {
    u16 value;
    s32 index;
    static void *const keepalive[] = { &&L0, &&L4, &&L8, &&L12 };

    value = *arg0 + 1;
    *arg0 = value;
    if ((s16)value >= 24) {
        *arg0 = 0;
    }

    index = (s16)*arg0 % 24;
    if ((u32)index >= 21) {
        return;
    }
    goto *D_800893A0[index];

L0:
    {
#ifndef NON_MATCHING
        register s32 page ASM_REG("$3") = (s32)0x80110000;   /* MATCH pin: load-bearing for the whole function shape */
        void *rect;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        rect = (void *)(page + 0x1FA8);
#else
        void *rect = D_80111FA8;
#endif
        func_800B7F58(rect, D_80110EC8);
        return;
    }

L4:
    {
#ifndef NON_MATCHING
        register s32 page ASM_REG("$3") = (s32)0x80110000;   /* MATCH pin: load-bearing for the whole function shape */
        void *rect;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        rect = (void *)(page + 0x1FA8);
#else
        void *rect = D_80111FA8;
#endif
        func_800B7F58(rect, D_801110C8);
        return;
    }

L8:
    {
#ifndef NON_MATCHING
        register s32 page ASM_REG("$3") = (s32)0x80110000;   /* MATCH pin: load-bearing for the whole function shape */
        void *rect;
        ASM_KEEP(page);   /* MATCH pin: load-bearing for the whole function shape */
        rect = (void *)(page + 0x1FA8);
#else
        void *rect = D_80111FA8;
#endif
        func_800B7F58(rect, D_801112C8);
        return;
    }

L12:
    D_80111FA8[0] = 808;
    D_80111FA8[1] = 128;
    D_80111FA8[2] = 8;
    D_80111FA8[3] = 32;
    LoadImage(D_80111FA8, D_801114C8);
}
