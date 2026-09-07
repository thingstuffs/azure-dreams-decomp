#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s16 GetTPage(s32, s32, s32, s32);
extern s16 GetClut(s32, s32);
extern s32 func_8003DE58(void *, void *, s16 *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800644B8(s32);
extern s32 rand(void);

extern u8 D_80024ACC[];
extern u8 D_80045340[];
extern s32 D_800814A0;
extern u8 D_80082E80[];
extern u8 D_80083498[];
extern u8 D_80083780[];
extern u8 D_800DEA68[];

void func_8002466C(void *arg0)
{
    s16 sp10[3];
    s16 state;
    s32 var_s0;
    s32 var_s3;
    s32 temp_link;
    u16 temp_v0;
    void *owner;
    void *ctx1;
    void *ctx2;
    void *coords1;
    void *coords2;
    void *obj;
    void *ent;
    void *draw;
    void *pal;
    void *disp;

    owner = FIELD(arg0, void *, 0);
    FIELD(arg0, u16, 0x48) = FIELD(arg0, u16, 0x48) + 1;
    FIELD(owner, u16, 0x52) |= 0x8000;
    var_s0 = -1;
    state = FIELD(arg0, s16, 0x4C);
    switch (state) {
        case 0:
            FIELD(arg0, u16, 0x50) = GetTPage(0, 1, 0x2C0, 0x100);
            FIELD(arg0, u16, 0x52) = GetClut(0xC0, 0x1F7);
            FIELD(arg0, s16, 0x46) = 0x1F;
            FIELD(arg0, s16, 0x44) = 0x1F;
            FIELD(arg0, u16, 0x48) = 0;
            FIELD(arg0, u16, 0x4E) = 0x30;
            FIELD(arg0, s16, 0x4C) = FIELD(arg0, u16, 0x4C) + 1;
        case 1:
            var_s0 = 0xE;
            ctx1 = D_80082E80;
            if (func_8003DE58(FIELD(ctx1, void *, 8), ctx1, sp10, 0) != 0) {
                coords1 = D_80083780;
                FIELD(arg0, s32, 0x1C) +=
                    ((sp10[0] + FIELD(coords1, s16, 2)) -
                     FIELD(arg0, s16, 0x1E)) << 14;
                FIELD(arg0, s32, 0x20) +=
                    ((sp10[1] + FIELD(coords1, s16, 6)) -
                     FIELD(arg0, s16, 0x22)) << 14;
                FIELD(arg0, s32, 0x24) +=
                    ((sp10[2] + FIELD(coords1, s16, 0xA)) -
                     FIELD(arg0, s16, 0x26)) << 14;
                FIELD(arg0, s32, 0x24) -=
                    func_800644B8((FIELD(arg0, s16, 0x48) << 11) / 10) << 9;
            }
            if (FIELD(arg0, s16, 0x48) >= 0xA) {
                FIELD(arg0, u16, 0x4A) = 0x10;
                FIELD(arg0, s16, 0x4C) = FIELD(arg0, u16, 0x4C) + 1;
            }
            break;

        case 2:
            var_s0 = 9;
            if (FIELD(arg0, s16, 0x48) >= 0xB) {
                var_s0 = 4;
            }
            FIELD(arg0, u16, 0x4E) += 2;
            ctx2 = D_80082E80;
            if (func_8003DE58(FIELD(ctx2, void *, 8), ctx2, sp10, 0) != 0) {
                coords2 = D_80083780;
                FIELD(arg0, s32, 0x1C) +=
                    ((sp10[0] + FIELD(coords2, s16, 2)) -
                     FIELD(arg0, s16, 0x1E)) << 15;
                FIELD(arg0, s32, 0x20) +=
                    ((sp10[1] + FIELD(coords2, s16, 6)) -
                     FIELD(arg0, s16, 0x22)) << 15;
                FIELD(arg0, s32, 0x24) +=
                    ((sp10[2] + FIELD(coords2, s16, 0xA)) -
                     FIELD(arg0, s16, 0x26)) << 15;
            }
            if (FIELD(arg0, s16, 0x48) >= 0xD) {
                FIELD(arg0, u16, 0x48) = 8;
            }
            temp_v0 = FIELD(arg0, u16, 0x4A) - 1;
            FIELD(arg0, u16, 0x4A) = temp_v0;
            if (((s32)(temp_v0 << 16) <= 0) &&
                (FIELD(arg0, s16, 0x48) == 0xC)) {
                FIELD(arg0, s16, 0x4C) = FIELD(arg0, u16, 0x4C) + 1;
            }
            break;

        case 3:
            var_s0 = 5;
            if (FIELD(arg0, s16, 0x48) == 0xF) {
                FIELD(arg0, u16, -2) |= 0x8000;
                D_800814A0 |= 0x8000;
            }
            break;
    }
    var_s3 = var_s0;

    FIELD(arg0, s16, 0x40) = ((FIELD(arg0, u16, 0x48) & 3) << 5) + 0x80;
    FIELD(arg0, s16, 0x42) =
        (((s32)(FIELD(arg0, u16, 0x48) << 16) >> 18) << 5) + 0x80;
    if (var_s3 >= 0) {
        pal = D_80024ACC;
        disp = D_800DEA68;
        do {
            obj = func_8003FD64(0x312, D_80083498);
            if (obj != NULL) {
                FIELD(obj, void *, 0x10) = pal;
                func_8004491C(obj, D_80045340);
                draw = FIELD(obj, void *, 0xC);
                FIELD(FIELD(obj, void *, 8), s32, 0) =
                    FIELD(arg0, s32, 0x1C) +
                    (((rand() & 0x3FF) - 0x1FF) << 12);
                FIELD(FIELD(obj, void *, 8), s32, 4) =
                    FIELD(arg0, s32, 0x20) +
                    (((rand() & 0x3FF) - 0x1FF) << 12);
                FIELD(FIELD(obj, void *, 8), s32, 8) =
                    FIELD(arg0, s32, 0x24) +
                    (((rand() & 0x3FF) - 0x1FF) << 11);
                FIELD(draw, s16, 0x1E) = 0x1000;
                FIELD(draw, s16, 0x1C) = 0x1000;
                FIELD(draw, s16, 0x10) = 0x60;
                FIELD(draw, void *, 0) = disp;
                FIELD(draw, u16, 0x14) |= 0xC;
                temp_link = FIELD(disp, s32, 4);
                FIELD(draw, u8, 4) = 0;
                FIELD(draw, u8, 5) = 0;
                FIELD(draw, s32, 0xC) = 0x808080;
                FIELD(draw, s32, 8) = temp_link;
                FIELD(obj, void *, 0x20) = FIELD(arg0, void *, 0);
                ASM_SCHED_BARRIER();
                ent = (u8 *)obj + 0x20;
                ASM_KEEP(ent);
                FIELD(ent, s16, 0x4C) = 0;
            }
            var_s3 -= 1;
        } while (var_s3 >= 0);
    }
}

/* MECHANISM: (1) held-base locals ctx1/ctx2 for D_80082E80 keep retail's
   lui/addiu/lw 8(a1) triple instead of gcc folding D+8 into one %lo; (2) the
   /10 divide is written inline off the s16 field so gcc emits lh + sll 11, not
   lhu + sll 16 / sra 5 (an s16 temp costs an extra word); (3) the sprite-tail
   order puts the two sb 0 stores after the disp link load; (4) obj+0x20:
   gcc always folds (obj+0x20)+0x4c into one 0x6c displacement, so the
   materialisation is forced with ASM_KEEP(ent) and the preceding
   ASM_SCHED_BARRIER keeps the addiu below the sw, leaving retail's load-delay
   nop (both devices measured: dropping the barrier costs a word, 4 -> 11).
   RESIDUE: 276/280 words byte-identical; the only 4 diffs are this function's
   OWN local j words, all solving true link base 0x8002466C vs the synthetic
   0x819B2E6C - a rowbase base shift, not a C or compiler gap. */

