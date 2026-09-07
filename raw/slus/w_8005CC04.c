#include "common.h"

typedef struct {
    volatile u16 voll;    /* 0x0 */
    volatile u16 volr;    /* 0x2 */
    volatile u16 pitch;   /* 0x4 */
    volatile u16 addr;    /* 0x6 */
    volatile u16 adsr1;   /* 0x8 */
    volatile u16 adsr2;   /* 0xA */
    volatile u16 curvol;  /* 0xC */
    volatile u16 repaddr; /* 0xE */
} SpuVoiceRegs;

typedef struct {
    SpuVoiceRegs voice[24];   /* 0x000 .. 0x17F */
    volatile u16 mvoll;       /* 0x180 */
    volatile u16 mvolr;       /* 0x182 */
    volatile u16 rvoll;       /* 0x184 */
    volatile u16 rvolr;       /* 0x186 */
    volatile u16 keyon_lo;    /* 0x188 */
    volatile u16 keyon_hi;    /* 0x18A */
    volatile u16 keyoff_lo;   /* 0x18C */
    volatile u16 keyoff_hi;   /* 0x18E */
    volatile u16 fm_lo;       /* 0x190 */
    volatile u16 fm_hi;       /* 0x192 */
    volatile u16 noise_lo;    /* 0x194 */
    volatile u16 noise_hi;    /* 0x196 */
    volatile u16 rev_lo;      /* 0x198 */
    volatile u16 rev_hi;      /* 0x19A */
    u8  pad19C[0x1AA - 0x19C];
    volatile u16 spucnt;      /* 0x1AA */
    volatile u16 dt_ctrl;     /* 0x1AC */
    volatile u16 spustat;     /* 0x1AE */
    u8  pad1B0[0x1B0 - 0x1B0];
    volatile u16 cdvoll;      /* 0x1B0 */
    volatile u16 cdvolr;      /* 0x1B2 */
    volatile u16 extvoll;     /* 0x1B4 */
    volatile u16 extvolr;     /* 0x1B6 */
} SpuRegs;

extern SpuRegs *D_80079958;
extern s32 *D_80079968;
extern u16 D_80079970;
extern s32 D_80079974;
extern s32 D_80079978;
extern s32 D_8007997C;
extern s32 D_80079980;
extern s32 D_80079984;
extern s32 D_80079988;
extern s32 D_8007998C;
extern volatile s32 D_80079990;
extern volatile s32 D_80079994;
extern u16 D_80079998[8];
extern volatile u16 D_80086D58[10];
extern char D_800331F4[];
extern char D_80033204[];

extern void func_8005D730(void);
extern s32 func_8005CE98(u16 *src, u32 size);
extern void printf();

/* PsyQ 4.0 LIBSPU: _SpuInit */
s32 func_8005CC04(s32 warm)
{
    s32 i;
    s32 ret;
    u32 tries;
    volatile u16 *p;
    SpuRegs *r;

    *D_80079968 |= 0xB0000;
    D_80079974 = 0;
    D_80079978 = 0;
    D_80079970 = 0;
    D_80079958->mvoll = 0;
    D_80079958->mvolr = 0;
    D_80079958->spucnt = 0;
    func_8005D730();
    D_80079958->mvoll = 0;
    D_80079958->mvolr = 0;
    tries = 0;
    while (D_80079958->spustat & 0x7FF) {
        if (++tries >= 0xF01) {
            printf(D_800331F4, D_80033204);
            break;
        }
    }
    D_8007997C = 2;
    D_80079980 = 3;
    D_80079984 = 8;
    D_80079988 = 7;
    D_80079958->dt_ctrl = 4;
    D_80079958->rvoll = 0;
    D_80079958->rvolr = 0;
    D_80079958->keyoff_lo = 0xFFFF;
    D_80079958->keyoff_hi = 0xFFFF;
    D_80079958->rev_lo = 0;
    D_80079958->rev_hi = 0;
    i = 0;
    p = D_80086D58;
    for (; i < 10; i++) {
        *p = 0;
        p++;
    }
    if (warm == 0) {
        D_80079970 = 0x200;
        D_80079958->fm_lo = 0;
        D_80079958->fm_hi = 0;
        D_80079958->noise_lo = 0;
        D_80079958->noise_hi = 0;
        D_80079958->cdvoll = 0;
        D_80079958->cdvolr = 0;
        D_80079958->extvoll = 0;
        D_80079958->extvolr = 0;
        func_8005CE98(D_80079998, 0x10);
        r = D_80079958;
        for (i = 0; i < 24; i++) {
            r->voice[i].voll = 0;
            r->voice[i].volr = 0;
            r->voice[i].pitch = 0x3FFF;
            r->voice[i].addr = 0x200;
            r->voice[i].adsr1 = 0;
            r->voice[i].adsr2 = 0;
        }
        D_80079958->keyon_lo = 0xFFFF;
        D_80079958->keyon_hi = 0xFF;
        func_8005D730();
        func_8005D730();
        func_8005D730();
        func_8005D730();
        D_80079958->keyoff_lo = 0xFFFF;
        D_80079958->keyoff_hi = 0xFF;
        func_8005D730();
        func_8005D730();
        func_8005D730();
        func_8005D730();
    }
    ret = 0;
    D_8007998C = 1;
    D_80079958->spucnt = 0xC000;
    D_80079990 = 0;
    D_80079994 = 0;
    return ret;
}
