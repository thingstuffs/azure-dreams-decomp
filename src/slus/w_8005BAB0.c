#include "common.h"

/* Scans D_80085458 for active slots (f1a != 0) whose channel index is NOT a
 * direct MIDI channel (f06 >= 0x10) and whose key fields match the caller's
 * device/channel id (encoded in arg0/arg1); for each match, clears the
 * active flags and re-dispatches the note twice via func_80056D44 while
 * OR-accumulating D_80073740[i] into a flags word passed to func_8005E97C. */
/* D_80085458 table element, stride 0x78 bytes. Fields at 0x0A and 0x5C are
 * newly touched here (not referenced by other reconciled siblings); rest of
 * the layout matches the canonical struct established in src/w_80056A08.c
 * and friends. */
typedef struct {
    /* 0x00 */ s16 f00, f02;
    /* 0x04 */ u16 f04;
    /* 0x06 */ u16 f06;
    /* 0x08 */ u8 pad08[2];
    /* 0x0A */ u16 f0a;
    /* 0x0C */ u8 pad0c[0xC];
    /* 0x18 */ s16 f18;
    /* 0x1A */ u16 f1a;
    /* 0x1C */ s8 f1c, f1d;
    /* 0x1E */ u8 pad1e[8];
    /* 0x26 */ s8 f26, f27, f28;
    /* 0x29 */ u8 pad29[3];
    /* 0x2C */ s32 f2c, f30;
    /* 0x34 */ u8 pad34[8];
    /* 0x3C */ s32 f3c;
    /* 0x40 */ u8 pad40[2];
    /* 0x42 */ s8 f42, f43, f44;
    /* 0x45 */ u8 pad45[3];
    /* 0x48 */ s32 f48, f4c;
    /* 0x50 */ u8 pad50[0xC];
    /* 0x5C */ u16 f5c;
    /* 0x5E */ u8 pad5e[0x12];
    /* 0x70 */ s32 f70, f74;
} S_8005BAB0_85458;

extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern S_8005BAB0_85458 D_80085458[64];
extern s32 D_80085F98[4]; /* forced hi/lo access via size > 8 */

extern s32 func_80056D44(s32 a0, S_8005BAB0_85458 *a1);
extern void func_8005E97C(s32 a0, s32 a1);

void func_8005BAB0(s32 arg0, s32 arg1)
{
    S_8005BAB0_85458 *p;
    s32 *q;
    s32 acc;
    s32 i;

    i = 0;
    acc = i;
    D_80085F98[0] = 1;

    if (D_80073734[0] <= 0) {
        goto done;
    }

    q = D_80073740;
    p = D_80085458;
loop:
    if (p->f1a == 0) {
        goto next;
    }
    if ((u16)p->f06 < 0x10) {
        goto next;
    }
    if (p->f0a != (arg1 >> 8)) {
        goto next;
    }
    if (p->f5c != (arg0 >> 8)) {
        goto next;
    }
    if (p->f04 != (u16)(arg0 & 0x7F)) {
        goto next;
    }
    acc |= *q;
    p->f1a = 0;
    p->f0a = 0;
    func_80056D44(i, p);
    func_8005E97C(0, *q);
    func_80056D44(i, p);
    func_8005E97C(0, *q);
    acc |= *q;
next:
    q++;
    p++;
    i++;
    if (i < D_80073734[0]) {
        goto loop;
    }

done:

    func_8005E97C(0, acc);
    D_80085F98[0] = 0;
}
