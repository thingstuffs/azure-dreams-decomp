#include "common.h"

/* Entity pointed to by arg0 */
typedef struct Entity {
    u8    pad0[0xC];
    void *unkC;      /* 0x0C -> Sub */
    s32   unk10;     /* 0x10 */
    u8    pad14[4];
    s32   unk18;     /* 0x18 state selector */
    u8    pad1C[8];
    s16   unk24;     /* 0x24 countdown */
    u16   unk26;     /* 0x26 */
} Entity;

typedef struct Sub {
    u8  pad0[2];
    s16 f2;   /* 0x02 */
    u8  pad4[2];
    s16 f6;   /* 0x06 */
    u8  pad8[2];
    s16 fA;   /* 0x0A */
} Sub;

/* View over the D_80083178 dispatch/blend record (fields not in game.h struct) */
typedef struct G {
    u8  pad0[0x98];
    s16 f98;   /* 0x98 */
    u8  pad9a[0xA4 - 0x9A];
    s16 fA4;   /* 0xA4 */
    s16 fA6;   /* 0xA6 */
    s16 fA8;   /* 0xA8 */
    u8  padAA[2];
    s16 fAC;   /* 0xAC */
    u8  padAE[2];
    s16 fB0;   /* 0xB0 */
} G;

extern s16 D_800120A2;
extern s16 D_800DD264[];
extern s32 D_800E3D7C[];
extern u16 D_80083460[];
extern u8  D_80083780[];
extern s16 D_800DCE66[5];

extern void func_800C77D0(void *a0, void *a1, s32 a2, s16 a3);
extern void func_800C7D44(void);

void func_800C7B38(void *arg0) {
    Entity *p = arg0;
    G *g = (G *)&D_80083178;
    s32 st = p->unk18;

    if (st == 0) goto case0;
    if (st == 1) goto case1;
    func_800C7D44();
    return;

case0:
    if (p->unk24 > 0) {
        s16 half;
        p->unk10 -= p->unk10 >> 2;
        g->f98 = p->unk26 + (u16)p->unk10;
        g->fAC = (u16)g->fAC + (D_800DD264[D_800120A2] - g->fAC) / p->unk24;
        g->fB0 = (u16)g->fB0 + (0 - g->fB0) / p->unk24;
        g->fA4 = (u16)g->fA4 + (((Sub *)p->unkC)->f2 - g->fA4) / p->unk24;
        g->fA6 = (u16)g->fA6 + (((Sub *)p->unkC)->f6 - g->fA6) / p->unk24;
        half = (s16)(u16)p->unk24 / 2;
        if (half != 0) {
            g->fA8 = (u16)g->fA8 + (((Sub *)p->unkC)->fA - g->fA8) / half;
        }
        {
            s16 nc = (u16)p->unk24 - 1;
            p->unk24 = nc;
            if (nc > 0) {
                return;
            }
        }
    }
    g->fAC = (u16)D_800DD264[D_800120A2];
    g->fB0 = 0;
    g->f98 = p->unk26;
    p->unk18 += 1;
    func_800C7D44();
    return;

case1:
    func_800C77D0((void *)(D_800E3D7C[0] - 0x20), D_80083780, 8, D_800DCE66[0]);
    D_80083460[5] = D_80083460[5] - 1;
}
