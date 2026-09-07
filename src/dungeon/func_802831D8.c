#include "common.h"

typedef struct {
    u32 unk00;
    u8 pad04[0x10];
    u16 unk14;
    u16 unk16;
    u16 unk18;
    u16 unk1A;
    u16 unk1C;
    u16 unk1E;
} InitBlock;

typedef struct {
    u8 pad00[0xA8];
    u32 unkA8;
    u8 padAC[0x130];
    InitBlock unk1DC;
} GlobalState;

extern GlobalState D_80083160;
extern u8 D_80080AA0[16];
extern u8 D_800EA000[16];

extern void func_80018A70(void *, u32, u32);
extern void func_80099188(void *);

void func_800161D8(void) {
    u32 y = 0x2C808080;
    GlobalState *g = &D_80083160;
    InitBlock *p = &g->unk1DC;
    u32 x = 0x3F;
    u32 z = 6;

    ASM_KEEP(y);   /* MATCH pin: retail immediate-load split depends on it */
    ASM_KEEP(p);   /* MATCH pin: retail schedule: same instructions, different order without it */

    p->unk14 = z;
    ASM_KEEP(z);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    p->unk16 = 6;
    p->unk1C = 0x180;
    p->unk1E = 0x180;
    p->unk18 = x;
    p->unk1A = x;
    g->unkA8 = y;
    g->unk1DC.unk00 = (u32)D_800EA000;
    func_80018A70(g, x, y);
    D_80080AA0[0] = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    {
        u8 *page = (u8 *)0x800E0000;

        ASM_KEEP(page);   /* MATCH pin: retail schedule: same instructions, different order without it */
        page[0x3D20] = 0;
        func_80099188(D_800EA000 - 0x9C14);
    }
}

/* MECHANISM: Preserve the 0x18 frame, pinned early register roles, and exact store order.
   Fence after D_80080AA0, then keep an unpinned 0x800E0000 page local so its lui precedes
   the final-call address setup while its zero store remains in the jal delay slot. */
