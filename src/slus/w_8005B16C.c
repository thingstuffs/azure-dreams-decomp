#include "common.h"

/* Marks D_80085F98 "busy", scans D_80085458 (stride 0x78, count
 * D_80073734[0]) for active MIDI-ish channel slots (f06 < 0x10 && f1a != 0)
 * and dispatches each with a type=3 request (flags = D_80073740[i], plus
 * the slot's f10/f12 fields) via func_8005F134. Afterward marks slot arg0
 * of D_80086C00 active (field_2 = 1), sets D_800737A4, clears D_80085F98.
 * Matches gcc 2.7.2-cdk -O2 default flags; requires the `i` loop counter
 * pinned to $17 and the request's literal `3` pinned to $2 (real GNU
 * register-variable hints, not inline asm) to reproduce retail's exact
 * register roles/rematerialization; see globals for the reconciled
 * D_80085458/D_80086C00/request-struct layouts. */
typedef struct {
    s16 field_0;
    s16 field_2;
    s32 field_4;
    u16 field_8;
    u16 field_A;
} S_80086C00;

typedef struct {
    s32 field_0;
    s32 field_4;
    u16 field_8;
    u16 field_A;
    u8 pad0C[0x40 - 0x0C];
} S_8005B16C_req;

extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern s32 D_800737A4[4];
extern u8 D_80085458[0x78 * 64];
extern s32 D_80085F98[4];
extern S_80086C00 D_80086C00[8];

extern void func_8005F134(S_8005B16C_req *arg0);

void func_8005B16C(s16 arg0)
{
    S_8005B16C_req req;
    u8 *p;
    register s32 i ASM_REG("$17");   /* MATCH pin: slus-diff */
    s32 *q;
    S_80086C00 *base;

    i = 0;
    D_80085F98[0] = 1;
    if (D_80073734[0] > 0) {
        q = D_80073740;
        p = D_80085458;
    loop:
        if (*(u16 *)(p + 6) < 0x10U) {
            if (*(u16 *)(p + 0x1A) != 0) {
                s32 three;
                three = 3;
                req.field_4 = three;
                req.field_0 = *q;
                req.field_8 = *(u16 *)(p + 0x10);
                req.field_A = *(u16 *)(p + 0x12);
                func_8005F134(&req);
            }
        }
        q++;
        p += 0x78;
        {
            s32 lim = D_80073734[0];
            i++;
            if (i < lim) goto loop;
        }
    }
    base = D_80086C00;
    base[arg0].field_2 = 1;
    D_800737A4[0] = 1;
    D_80085F98[0] = 0;
}
