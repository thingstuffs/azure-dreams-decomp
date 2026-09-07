#include "common.h"

extern void bzero(void *dst, int n);
extern void *func_8004B404(u32 size);
extern s32 allocBufferArray(s32 *a0, s32 a1);
extern void func_8004CC38(s32 *a0, s32 a1);

/* Rebuilds a0's field0 buffer (0x104 bytes, allocated fresh via
   func_8004B404) and populates it with a1 pointer-pair entries built from
   two banks of up to 16 sub-buffer bases (buf[0..15], buf[16..31]) read
   back from a0's trailing flexible array, itself populated in two passes
   by allocBufferArray(a0+1..., (a1>>4)+1). arg2 only sizes the zeroing of the
   PRE-EXISTING a0[0] buffer before it is replaced. Each output entry is a
   pointer into bank1's sub-buffer (offset by (i&0xF)*16); that same
   sub-buffer's word at +4 is overwritten with the matching bank2 pointer.
   Returns the new buffer (a0[0]) or NULL on either allocation failure. */
s32 *reallocField0Buffer(s32 *a0, s32 a1, s32 a2)
{
    s32 *s1;
    s32 *v1;
    s32 v0;
    s32 buf[32];

    bzero((void *) a0[0], a2 * 4);
    s1 = (s32 *) func_8004B404(0x104);
    a0[0] = (s32) s1;
    a0 += 1;
    if (s1 == 0)
        goto done;
    if (allocBufferArray(a0, (s32)((u32) a1 >> 4) + 1) == 0)
        goto fail;
    if (*(volatile s32 *) a0 != 0) {
        v1 = buf;
        v0 = *a0;
        do {
            a0++;
            *v1 = v0;
            v0 = *a0;
            v1++;
        } while (v0 != 0);
    }
    if (allocBufferArray(a0, (s32)((u32) a1 >> 4) + 1) != 0)
        goto cont;
fail:
    s1 = 0;
    goto done;
cont:
    if (*(volatile s32 *) a0 != 0) {
        v1 = buf;
        v0 = *a0;
        do {
            a0++;
            v1[16] = v0;
            v0 = *a0;
            v1++;
        } while (v0 != 0);
    }
    if (a1 > 0) {
        s32 i = 0;
        s32 *bp = buf;
        s32 *a2p = s1;
        s32 *rec;
        do {
            s32 idx = (u32) i >> 4;
            s32 off = (i & 0xF) << 4;
            i++;
            rec = (s32 *)(bp[idx] + off);
            *a2p = (s32) rec;
            rec[1] = bp[idx + 16] + off;
            a2p++;
        } while (i < a1);
    }
    func_8004CC38(s1, a1);
done:
    return s1;
}
