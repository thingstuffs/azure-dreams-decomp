#include "common.h"

/* Advances past a filled field: fills arg0[0..2*arg1) via func_8004E9EC, then
 * appends 2 bytes of the D_80080B70 pattern right after via strncpy, and
 * returns a pointer to that appended position. */
/* D_80080B70: a small pattern buffer; only bytes 0..2 are ever read (by
 * sibling func_8004E9EC as a 3-byte fill pattern). Declared >8B so its
 * address is materialised via %hi/%lo instead of $gp-relative. */
typedef struct S_80080B70 {
    /* 0x0 */ s8 b0;
    /* 0x1 */ s8 b1;
    /* 0x2 */ s8 b2;
    /* 0x3 */ s8 pad[13];
} S_80080B70; /* size 0x10 */

extern S_80080B70 D_80080B70;

extern void func_8004E9EC(u8 *arg0, s32 arg1);
extern char *strncpy(char *dst, const char *src, u32 n);

char *func_8004EA70(u8 *arg0, s32 arg1) {
    u8 *base = arg0;
    s32 off = arg1;

    func_8004E9EC(arg0, arg1);
    base = base + (off << 1);
    strncpy((char *)base, (char *)&D_80080B70, 2);
    return (char *)base;
}
