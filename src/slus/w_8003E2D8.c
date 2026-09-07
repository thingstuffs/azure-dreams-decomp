#include "common.h"

/* D_80083160: shared state table (own view here). field_8 (cur reading) is
 * accessed directly on the base struct; a separate history view starting
 * at the SAME offset+8 holds cur again at +0 (unused via this view), the
 * previous reading (old, +4) and the trg mask (+8). */
struct S_8003E2D8 {
    char pad0[8];
    s32 field_8;
    s32 field_C;
    s32 field_10;
};

typedef struct {
    s32 cur;
    s32 old;
    s32 trg;
} Hist_8003E2D8;

extern struct S_8003E2D8 D_80083160;

extern s32 func_8003E240(s32 a0);

/* Reads controller/pad state via func_8003E240(0). Saves the previous
 * field_8 reading into the history's old slot, stores the new reading
 * into field_8 (clearing it if the top nibble reads 0xF, e.g. no
 * controller present), then recomputes the trg mask as the newly-set
 * bits: (new ^ old) & new. */
void func_8003E2D8(void)
{
    struct S_8003E2D8 *base = &D_80083160;
    Hist_8003E2D8 *h = (Hist_8003E2D8 *)&base->field_8;
    s32 old = base->field_8;
    s32 v;

    h->old = old;
    base->field_8 = func_8003E240(0);

    if ((base->field_8 & 0xF000) == 0xF000) {
        base->field_8 = 0;
    }

    v = base->field_8;
    h->trg = (v ^ h->old) & v;
}
