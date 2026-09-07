#include "common.h"

typedef struct S_80053A88_TILE {
    u32 tag;
    u32 code;
    s16 x0;
    s16 y0;
    s16 w;
    s16 h;
} S_80053A88_TILE;
typedef struct S_80053A88_DRTPAGE {
    u32 tag;
    u16 code[4];
} S_80053A88_DRTPAGE;
typedef struct S_80053A88_Base {
    u8 pad_000[0x74];
    u32 unk74;
    u8 pad_078[0x8D0 - 0x78];
    void *unk8D0;
} S_80053A88_Base;
typedef struct S_80053A88_Node {
    u8 pad_00[0x8];
    u32 unk8;
    u16 unkC;
    u16 unkE;
    u16 unk10;
    u16 unk12;
    s16 unk14;
    u16 unk16;
} S_80053A88_Node;
extern S_80053A88_Base *D_80083160[3];
extern void SetTile(S_80053A88_TILE *p);
extern void SetSemiTrans(void *p, s32 abe);
extern s32 GetTPage(s32 tp, s32 abr, s32 x, s32 y);
extern void SetDrawMode(S_80053A88_DRTPAGE *p, s32 a1, s32 a2, s32 a3, s32 a4);

s32 func_80053A88(S_80053A88_Node *a0)
{
    S_80053A88_Base **parr;
    S_80053A88_Node *s1;
    S_80053A88_Base *base;
    S_80053A88_TILE *tile;
    S_80053A88_DRTPAGE *drtp;
    s32 tp;
    register void *next ASM_REG("$4");   /* MATCH pin: slus-diff */
    u32 low_mask;
    u32 high_mask;
    s1 = a0;
    parr = &D_80083160[0];
    ASM_KEEP_NV(parr);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    low_mask = 0x00FFFFFF;
    high_mask = 0xFF000000;
    ASM_USE_NV(low_mask);   /* MATCH pin: slus-diff */
    ASM_USE_NV(low_mask);   /* MATCH pin: slus-diff */
    ASM_USE_NV(low_mask);   /* MATCH pin: slus-diff */
    ASM_USE_NV(low_mask);   /* MATCH pin: slus-diff */
    ASM_USE_NV(low_mask);   /* MATCH pin: slus-diff */
    ASM_USE_NV(low_mask);   /* MATCH pin: slus-diff */
    do {
        base = (*parr);
        tile = (S_80053A88_TILE *)base->unk8D0;
        base->unk8D0 = (void *)(((u8 *)tile) + 0x10);
        tile->x0 = s1->unkC;
        tile->y0 = s1->unkE;
        tile->w = s1->unk10;
        tile->h = s1->unk12;
        tile->code = s1->unk8;
        SetTile(tile);
        if (s1->unk16 & 1) {
            SetSemiTrans(tile, 1);
        }
        if (!(s1->unk16 & 2)) {
            tile->tag = (tile->tag & high_mask) | ((*parr)->unk74 & low_mask);
            (*parr)->unk74 = ((*parr)->unk74 & high_mask) | (((u32)tile) & low_mask);
        }
        base = (*parr);
        drtp = (S_80053A88_DRTPAGE *)base->unk8D0;
        base->unk8D0 = (void *)(((u8 *)drtp) + 0xC);
        tp = GetTPage(0, s1->unk14, 0, 0);
        SetDrawMode(drtp, 0, 0, tp & 0xFFFF, 0);
        if (!(s1->unk16 & 2)) {
            drtp->tag = (drtp->tag & high_mask) | ((*parr)->unk74 & low_mask);
            (*parr)->unk74 = ((*parr)->unk74 & high_mask) | (((u32)drtp) & low_mask);
        }
        next = *((void **)(((u8 *)s1) - 8));
        s1 = (S_80053A88_Node *)(((u8 *)next) + 0x20);
    } while (next != 0);
    ASM_KEEP(next);   /* MATCH pin: slus-diff */
    return 0;
}
