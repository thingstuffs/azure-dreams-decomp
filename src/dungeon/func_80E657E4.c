#include "common.h"

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define LEGACY_ASM_KEEP(value) \
    ASM_KEEP(value)
#else
#define LEGACY_ASM_KEEP(value) ASM_KEEP(value)
#endif

extern void func_80047784(void *, s32, s32);
extern void func_80099EA4(void *);
extern void func_800A4ACC(void *);

extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_801755B4[];
extern u8 D_80175660[];

void func_80174FE4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register u8 *base ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    register u8 *page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *table;
    s32 index;

    base = D_80175660;
    *(u16 *)(base + 0x6C) = *(u16 *)((u8 *)arg3 + 0x6C);
    *(u16 *)(base + 0x6E) = *(u16 *)((u8 *)arg3 + 0x6E);
    func_80099EA4(base);

    if (*(s8 *)(base + 0x6D) != 0) {
        *(u8 *)((u8 *)arg3 + 0x71) &= 0x7F;
        ASM_USE(base);   /* MATCH pin: retail basic-block layout depends on it */
        page = (u8 *)0x80080000;
        LEGACY_ASM_KEEP(page);
        base = page + 0x3460;
        if (!(*(u16 *)(base + 2) & 0x2000)) {
            table = D_801755B4;
            *(s8 *)((u8 *)arg0 + 0x9A) = 0x17;
            *(s32 *)((u8 *)arg0 + 0x8C) = 0;
            *(s8 *)((u8 *)arg0 + 0x9B) = 0;
            *(s16 *)((u8 *)arg0 + 0x96) = 0;

            *(u8 **)((u8 *)arg2 + 0x2C) = table;
            index = (D_80083228[0] + *(s16 *)((u8 *)arg3 + 0x2A) + 0x100) >> 9;
            func_80047784(arg2, table[index & 7], 0);
            func_800A4ACC(arg3);
            *(u8 *)((u8 *)arg3 + 0x6D) -= 1;
            *(u16 *)(base + 0xA) += 1;
        }
    }
}
