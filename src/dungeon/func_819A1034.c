#include "common.h"

typedef struct S_819A1034_0 {
    u8 pad_00[0x3A];
    union { u16 s; s16 u; } unk_3A;   /* accessed as both */
    s16 unk_3C;
} S_819A1034_0;   /* base in func_819A1034 */

typedef struct S_819A1034_1 {
    u8 pad_00[0x61B0];
    s16 unk_61B0;
} S_819A1034_1;   /* page in func_819A1034 */

typedef struct S_819A1034_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u8 unk_1C;
    u8 unk_1D;
    u8 unk_1E;
} S_819A1034_2;   /* p in func_819A1034 */


extern s16 D_800261B0;
extern s32 D_800814A0;


void func_819A1034(void *arg0)
{
    void *base;
    s32 i;
    register u8 *p ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *page;
    u16 count;

    base = arg0;
    do { i = 0; } while (0);
    p = base;
#ifdef NON_MATCHING
    page = (u8 *)&D_800261B0 - 0x5FF4;
#else
    page = (u8 *)0x80020000;
#endif
    ASM_KEEP(page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    count = ((S_819A1034_0 *)base)->unk_3A.s;
    ((S_819A1034_1 *)page)->unk_61B0 = 1;
    count--;
    ((S_819A1034_0 *)base)->unk_3A.s = count;
    do {
        ((S_819A1034_2 *)p)->unk_0C =
            ((S_819A1034_2 *)p)->unk_1C * ((S_819A1034_0 *)base)->unk_3A.u /
            ((S_819A1034_0 *)base)->unk_3C;
        ((S_819A1034_2 *)p)->unk_0D =
            ((S_819A1034_2 *)p)->unk_1D * ((S_819A1034_0 *)base)->unk_3A.u /
            ((S_819A1034_0 *)base)->unk_3C;
        i++;
        ((S_819A1034_2 *)p)->unk_0E =
            ((S_819A1034_2 *)p)->unk_1E * ((S_819A1034_0 *)base)->unk_3A.u /
            ((S_819A1034_0 *)base)->unk_3C;
        p += 4;
    } while (i < 4);
    if (((S_819A1034_0 *)base)->unk_3A.u <= 0) {
        (*(u16 *)((u8 *)base + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
