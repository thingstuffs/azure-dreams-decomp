#include "common.h"

/* Advances an entity's position (unk14/unk18) by a signed velocity derived
 * from D_80083CA8's fields while its countdown timer is running, then
 * ticks the timer down and decays the accumulator toward 0. */
#include "common.h"

/* D_80083160: shared state table (own view). Only the flags halfword at
 * offset 0x4 is touched here (bit0/bit1 select add-vs-subtract direction
 * for the two axis offsets below). */
typedef struct {
    char pad0[4];
    u16 flags;    /* offset 0x4 */
    char pad6[6]; /* keep total size > 8B so hi/lo (not $gp) addressing is used */
} S_80041900_D80083160;

extern S_80041900_D80083160 D_80083160;

/* D_80083CA8: sibling struct of code2.c's func_800419EC (which documents
 * offset 0 = rate/quotient, offset 4 = accumulator, offset 6 = short
 * (aka D_80083CAE), offset 8 = countdown timer). func_80041900 reads the
 * offset-4 accumulator both as a full 32-bit int AND, via the same bytes,
 * as the offset-6 short -- modeled with a union so both views are legal. */
typedef struct {
    s32 field0;   /* offset 0x0 -- rate/quotient */
    union {
        s32 accum;      /* offset 0x4 -- full 32-bit accumulator */
        struct {
            u16 pad4;     /* offset 0x4 */
            u16 field6;   /* offset 0x6 */
        } h;
    } u;
    u16 field8;   /* offset 0x8 -- countdown timer */
} S_80041900_D80083CA8;

extern S_80041900_D80083CA8 D_80083CA8;

/* Same address as D_80083CA8.u.h.field6 (0x80083CA8+6 == 0x80083CAE), but
 * retail refetches it via a fresh hi/lo instead of reusing the already
 * -materialized D_80083CA8 base register, so it must be its own symbol. */
extern u16 D_80083CAE;

typedef struct {
    char pad0[0x14];
    s32 unk14;
    s32 unk18;
} S_80041900_Obj;

void func_80041900(S_80041900_Obj *arg0)
{
    S_80041900_D80083160 *p2 = &D_80083160;
    S_80041900_D80083CA8 *p1 = &D_80083CA8;

    if (p1->field8 != 0) {
        if (p2->flags & 2) {
            arg0->unk18 += (s16)p1->u.h.field6 >> 1;
        } else {
            arg0->unk18 -= (s16)p1->u.h.field6 >> 1;
        }

        if (p2->flags & 1) {
            arg0->unk14 += (s16)D_80083CAE >> 2;
        } else {
            arg0->unk14 -= (s16)D_80083CAE >> 2;
        }

        D_80083CA8.field8 -= 1;
        if (D_80083CA8.field8 == 0 ||
            (D_80083CA8.u.accum -= D_80083CA8.field0, D_80083CA8.u.accum < 0)) {
            D_80083CA8.u.accum = 0;
        }
    }
}
