#include "common.h"

extern int func_8004D880(int a0);
extern void func_8004D98C(int a0, int a1, void *a2);
extern void func_8004E264(void *a0, int a1);
extern void func_8004D9E0(signed char *a0, int a1, int a2, int a3, int a4);

/* Parses a text-encoded note sequence (a1) into fixed-size (0xC byte) note
 * entries written starting at a0, using a2 as the initial octave. Bytes 0x20
 * (space) accumulate into the length counter; 0x08 sets the octave from the
 * following digit; 0x0A resets the length counter and bumps a tie counter;
 * 0x09 either reads a dot count (if followed by 's') or folds the following
 * digit into the length counter; any other byte pair is decoded via
 * func_8004D880 into a note value and, unless it decodes to a rest (0x20),
 * emitted as a note entry (func_8004D98C/func_8004E264/func_8004D9E0).
 * Returns a0 with the terminal entry's flag byte OR'd with 0x80 if any
 * entries were written, otherwise returns NULL. */
void *func_8004DA74(void *a0, u8 *a1, s32 a2)
{
    s8 *p = (s8 *)a0;
    u8 *s = a1;
    s32 oct = a2;
    s32 len = 0;
    s32 tie = len;
    s32 dot = len;
    s8 *base = (s8 *)a0;
    u8 c;

    if (s == 0) {
        return (void *)len;
    }

    c = *s;
    if (c != 0) {
        do {
            if (c == ' ') {
                s++;
                len++;
            } else if (c == 8) {
                s++;
                oct = *s++ - 0x30;
            } else if (c == 0xA) {
                s++;
                len = 0;
                tie++;
            } else if (c == 9) {
                s++;
                c = *s;
                if (c == 's') {
                    s++;
                    dot = *s - 0x30;
                } else {
                    s32 t = len - 0x30;
                    len = t + c;
                }
                s++;
            } else {
                u8 b0 = s[0];
                u8 b1 = s[1];
                u8 nv = (u8)func_8004D880(b1 | (b0 << 8));
                do { s += 2; } while (0);
                if (nv != ' ') {
                    func_8004D98C(nv, oct, p);
                    func_8004E264(p, oct);
                    func_8004D9E0(p, len, tie, dot, 0);
                    p += 0xC;
                }
                len += 2;
            }
            c = *s;
        } while (c != 0);
    }

    if (p != base) {
        p[-0xC] = p[-0xC] | 0x80;
    } else {
        base = 0;
    }
    return base;
}
