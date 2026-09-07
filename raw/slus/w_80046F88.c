#include "common.h"

#include "common.h"

/* Object self-relocation: if live address != last-known anchor at +0x24,
 * add the byte delta to every embedded absolute pointer inside the object
 * and the two trailing arrays it owns. Returns the applied delta (0 if
 * the object had not moved). */
typedef struct S_80046F88 {
    /*0x00*/ s32 *arr;
    /*0x04*/ s32 count;
    /*0x08*/ s32 *end;
    /*0x0C*/ s32 val0C;
    /*0x10*/ s32 unk10;
    /*0x14*/ s32 val14;
    /*0x18*/ s32 unk18;
    /*0x1C*/ s32 val1C;
    /*0x20*/ s32 unk20;
    /*0x24*/ void *anchor;
} S_80046F88;

s32 func_80046F88(void *arg0)
{
    S_80046F88 *obj = (S_80046F88 *)arg0;
    /* delta must live in $a3; counter i takes $a2. Guarded pin for PC port. */
    register s32 delta ASM_REG("$7");
    s32 t14;
    s32 tmp;
    s32 i;
    s32 *p;
    s32 *q;

    delta = 0;
    if (arg0 != obj->anchor) {
        delta = (s32)arg0 - (s32)obj->anchor;
        /* Single tmp chains through arr/end/val0C/val1C so v0 is reused,
         * forcing a memory reload of p after the arr store (retail shape).
         * t14 holds val14 then is reused for count — that reuse assigns
         * t14/count to v1 and tmp to v0 (opposite of separate locals). */
        tmp = (s32)obj->arr;
        t14 = obj->val14;
        i = 0;
        obj->anchor = arg0;
        tmp = tmp + delta;
        obj->arr = (s32 *)tmp;
        tmp = (s32)obj->end;
        p = obj->arr;
        tmp = tmp + delta;
        obj->end = (s32 *)tmp;
        tmp = obj->val0C;
        t14 = t14 + delta;
        obj->val14 = t14;
        tmp = tmp + delta;
        obj->val0C = tmp;
        tmp = obj->val1C;
        t14 = obj->count;
        tmp = tmp + delta;
        obj->val1C = tmp;
        if (t14 > 0) {
            do {
                i++;
                *p += delta;
                p++;
            } while (i < obj->count);
        }
        if ((u32)p < (u32)obj->end) {
            q = p + 1;
            do {
                p += 2;
                *q += delta;
                q += 2;
            } while ((u32)p < (u32)obj->end);
        }
    }
    return delta;
}
