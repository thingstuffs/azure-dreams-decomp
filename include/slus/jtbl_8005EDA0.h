#ifndef SLUS_JTBL_8005EDA0_H
#define SLUS_JTBL_8005EDA0_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

/* PsyQ 4.0 LIBSPU: SpuSetCommonAttr */
typedef struct {
    s16 left;
    s16 right;
} SpuVolume;

typedef struct {
    SpuVolume volume;
    s32 reverb;
    s32 mix;
} SpuExtAttr;

typedef struct {
    u32 mask;            /* 0x00 */
    SpuVolume mvol;      /* 0x04 */
    SpuVolume mvolmode;  /* 0x08 */
    SpuVolume mvolx;     /* 0x0C */
    SpuExtAttr cd;       /* 0x10 */
    SpuExtAttr ext;      /* 0x1C */
} SpuCommonAttr;

typedef struct {
    u8  pad000[0x180];
    u16 mvoll;    /* 0x180 */
    u16 mvolr;    /* 0x182 */
    u8  pad184[0x1AA - 0x184];
    u16 spucnt;   /* 0x1AA */
    u8  pad1AC[0x1B0 - 0x1AC];
    u16 cdvoll;   /* 0x1B0 */
    u16 cdvolr;   /* 0x1B2 */
    u16 extvoll;  /* 0x1B4 */
    u16 extvolr;  /* 0x1B6 */
} SpuRegs;

extern SpuRegs *D_80079958;

/* Apply masked SPU master volume and CD/external input volume, reverb, and mixing settings. */

void func_8005EDA0(SpuCommonAttr *attr);

extern s32 D_800794F8;
extern s32 D_800794FC;
extern u32 D_80079500;
s32 func_8005D9DC(u32 value);
s32 func_8005D88C(s32 enable);

#endif
