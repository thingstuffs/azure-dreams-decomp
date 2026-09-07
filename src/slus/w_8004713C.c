#include "common.h"

#include "common.h"

typedef struct { s16 x, y, w, h; } RECT;

extern int LoadImage(RECT *rect, void *p);

/* Dual-access global: halfword stores via $gp scalars; LoadImage's rect
 * pointer is materialised with %hi/%lo via a >8B neighbour so address-of
 * is not gp_rel (D_80080B00[4] lands on D_80080B08 — same pattern as
 * w_8003F624.c). */
extern s16 D_80080B08;
extern s16 D_80080B0A;
extern s16 D_80080B00[8];

/* Register pins force retail's saved-reg map: s3=full arg2 (re-andi each
 * use), s2=tile, s4=tile<<4, s5=&rect. Without pins, 2.7.2 CSEs
 * (arg2 & 0xFFFF) into a2 early and LICM-hoists tile<<6 into s3. */
void func_8004713C(s32 arg0, s32 arg1, s32 arg2) {
    s32 ptr;
    s32 i;
    register s32 n ASM_REG("$19");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 tile ASM_REG("$18");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 tile4;
    RECT *rect;

    ptr = arg0;
    i = 0;
    n = arg2;
    if ((n & 0xFFFF) != 0) {
        rect = (RECT *)&D_80080B00[4];
        tile = arg1 & 0xFFFF;
        tile4 = tile << 4;
        do {
            s32 x = (tile << 6) & 0x3C0;
            if ((i / 2) != 0) {
                x += 0x20;
            }
            D_80080B08 = x;
            {
                s32 y = tile4 & 0x100;
                if ((i & 1) != 0) {
                    y += 0x80;
                }
                D_80080B0A = y;
            }
            LoadImage(rect, (void *)ptr);
            i += 1;
            ptr += 0x2000;
        } while (i < (n & 0xFFFF));
    }
}
