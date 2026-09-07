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
extern void *jtbl_8003323C[];
extern void *jtbl_8003325C[];

void func_8005EDA0(SpuCommonAttr *attr)
{
    u32 mask;
    s32 none;
    register u16 vl ASM_REG("$6");
    register u16 vr ASM_REG("$8");
    u32 mode;
    u16 rmw;
    s32 ml;
    s32 mr;
    s16 tl;
    register s32 tr ASM_REG("$6");
    s16 trc;
    static void *const keepalive_l[] = {
        &&plain_l, &&l_1, &&l_2, &&l_3, &&l_4, &&l_5, &&l_6, &&l_7
    };
    static void *const keepalive_r[] = {
        &&plain_r, &&r_1, &&r_2, &&r_3, &&r_4, &&r_5, &&r_6, &&r_7
    };
    (void)keepalive_l;
    (void)keepalive_r;

    vl = 0;
    vr = 0;
    mask = attr->mask;
    none = (mask == 0);

    if (none || (mask & 0x1)) {
        if (none || (mask & 0x4)) {
            ml = attr->mvolmode.left;
            if ((u32)ml < 8) {
                goto *jtbl_8003323C[ml];
            }
        }
        goto plain_l;
    l_1: mode = 0x8000; goto have_l;
    l_2: mode = 0x9000; goto have_l;
    l_3: mode = 0xA000; goto have_l;
    l_4: mode = 0xB000; goto have_l;
    l_5: mode = 0xC000; goto have_l;
    l_6: mode = 0xD000; goto have_l;
    l_7: mode = 0xE000; goto have_l;
    plain_l:
        vl = attr->mvol.left;
        mode = 0;
    have_l:
        if (mode != 0) {
            tl = attr->mvol.left;
            if (tl > 0x7F) {
                vl = 0x7F;
            } else if (tl < 0) {
                vl = 0;
            } else {
                vl = tl;
            }
        }
        D_80079958->mvoll = (vl & 0x7FFF) | mode;
    }

    if (none || (mask & 0x2)) {
        if (none || (mask & 0x8)) {
            mr = attr->mvolmode.right;
            if ((u32)mr < 8) {
                goto *jtbl_8003325C[mr];
            }
        }
        goto plain_r;
    r_1: mode = 0x8000; goto have_r;
    r_2: mode = 0x9000; goto have_r;
    r_3: mode = 0xA000; goto have_r;
    r_4: mode = 0xB000; goto have_r;
    r_5: mode = 0xC000; goto have_r;
    r_6: mode = 0xD000; goto have_r;
    r_7: mode = 0xE000; goto have_r;
    plain_r:
        vr = attr->mvol.right;
        mode = 0;
    have_r:
        if (mode != 0) {
            tr = attr->mvol.right;
            trc = attr->mvol.right;
            if (tr > 0x7F) {
                vr = 0x7F;
            } else if (tr < 0) {
                vr = 0;
            } else {
                vr = trc;
            }
        }
        D_80079958->mvolr = (vr & 0x7FFF) | mode;
    }

    if (none || (mask & 0x40)) {
        D_80079958->cdvoll = attr->cd.volume.left;
    }
    if (none || (mask & 0x80)) {
        D_80079958->cdvolr = attr->cd.volume.right;
    }
    if (none || (mask & 0x400)) {
        D_80079958->extvoll = attr->ext.volume.left;
    }
    if (none || (mask & 0x800)) {
        D_80079958->extvolr = attr->ext.volume.right;
    }
    if (none || (mask & 0x100)) {
        if (attr->cd.reverb == 0) {
            rmw = D_80079958->spucnt;
            rmw &= 0xFFFB;
            D_80079958->spucnt = rmw;
        } else {
            rmw = D_80079958->spucnt;
            rmw |= 0x4;
            D_80079958->spucnt = rmw;
        }
    }
    if (none || (mask & 0x200)) {
        if (attr->cd.mix == 0) {
            rmw = D_80079958->spucnt;
            rmw &= 0xFFFE;
            D_80079958->spucnt = rmw;
        } else {
            rmw = D_80079958->spucnt;
            rmw |= 0x1;
            D_80079958->spucnt = rmw;
        }
    }
    if (none || (mask & 0x1000)) {
        if (attr->ext.reverb == 0) {
            rmw = D_80079958->spucnt;
            rmw &= 0xFFF7;
            D_80079958->spucnt = rmw;
        } else {
            rmw = D_80079958->spucnt;
            rmw |= 0x8;
            D_80079958->spucnt = rmw;
        }
    }
    if (none || (mask & 0x2000)) {
        if (attr->ext.mix == 0) {
            rmw = D_80079958->spucnt;
            rmw &= 0xFFFD;
            D_80079958->spucnt = rmw;
        } else {
            rmw = D_80079958->spucnt;
            rmw |= 0x2;
            D_80079958->spucnt = rmw;
        }
    }
}
