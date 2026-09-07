#include "common.h"

extern s32 func_800BCB04(u16, u16, s16, void *);
extern void *D_800814A8[3];
extern u8 D_8008333C[32];
extern u8 D_800EA000[];

s16 func_800D175C(s32 arg0, s32 arg1)
{
    u8 *base;
    u8 *state;
    u8 *table;
    u16 reference;
    s32 height;
    s32 rounded;
    register s32 fallback ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    base = D_8008333C;
    state = base - 0x1C4;
    table = D_800EA000;
    arg1 = (s16)arg1;
    arg0 = (s16)arg0;
    ASM_KEEP(base);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(state);   /* MATCH pin: retail immediate-load split depends on it */
    reference = *(u16 *)(table +
        ((arg1 << *(s16 *)(base + 0x14)) + arg0) * 6 + 2);
    height = func_800BCB04(*(u16 *)(state + 0xA4),
                           *(u16 *)(state + 0xA6),
                           (s16)(*(u16 *)(state + 0xA8) - 0x20),
                           state);
    if ((s16)height < 0x201) {
        rounded = height + 0x3F;
    } else {
        fallback = *(u16 *)((u8 *)D_800814A8[0] + 0x88);
        rounded = fallback + 0x3F;
    }
    return (s16)(((reference + rounded) & -0x40) - reference);
}

/* MECHANISM: Kept byte bases plus distinct state/fallback roles recover v0/v1/a3.
   A >G8 pointer extern restores the hi/lo fallback; s0 alone holds the table halfword.
   Wide args normalize arg1 then arg0 before grouped keeps, placing saves at words 10-11.
   The four-arg callee stays wide; an explicit narrow true arm recovers return-copy. */
