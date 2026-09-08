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

/* Apply masked SPU master volume and CD/external input volume, reverb, and mixing settings. */
void func_8005EDA0(SpuCommonAttr *attr)
{
    u32 mask;
    s32 set_all;
    register u16 left_volume ASM_REG("$6");   /* MATCH pin: slus-diff */
    register u16 right_volume ASM_REG("$8");   /* MATCH pin: slus-diff */
    u32 mode_bits;
    u16 spu_control;
    s32 left_mode;
    s32 right_mode;
    s16 left_level;
    register s32 right_level ASM_REG("$6");   /* MATCH pin: slus-diff */
    s16 right_level_s16;
    static void *const keepalive_l[] = {
        &&plain_l, &&l_1, &&l_2, &&l_3, &&l_4, &&l_5, &&l_6, &&l_7
    };
    static void *const keepalive_r[] = {
        &&plain_r, &&r_1, &&r_2, &&r_3, &&r_4, &&r_5, &&r_6, &&r_7
    };
    (void)keepalive_l;
    (void)keepalive_r;

    left_volume = 0;
    right_volume = 0;
    mask = attr->mask;
    set_all = (mask == 0);

    if (set_all || (mask & 0x1)) {
        if (set_all || (mask & 0x4)) {
            left_mode = attr->mvolmode.left;
            if ((u32)left_mode < 8) {
                goto *jtbl_8003323C[left_mode];
            }
        }
        goto plain_l;
    l_1: mode_bits = 0x8000; goto have_l;
    l_2: mode_bits = 0x9000; goto have_l;
    l_3: mode_bits = 0xA000; goto have_l;
    l_4: mode_bits = 0xB000; goto have_l;
    l_5: mode_bits = 0xC000; goto have_l;
    l_6: mode_bits = 0xD000; goto have_l;
    l_7: mode_bits = 0xE000; goto have_l;
    plain_l:
        left_volume = attr->mvol.left;
        mode_bits = 0;
    have_l:
        if (mode_bits != 0) {
            left_level = attr->mvol.left;
            if (left_level > 0x7F) {
                left_volume = 0x7F;
            } else if (left_level < 0) {
                left_volume = 0;
            } else {
                left_volume = left_level;
            }
        }
        D_80079958->mvoll = (left_volume & 0x7FFF) | mode_bits;
    }

    if (set_all || (mask & 0x2)) {
        if (set_all || (mask & 0x8)) {
            right_mode = attr->mvolmode.right;
            if ((u32)right_mode < 8) {
                goto *jtbl_8003325C[right_mode];
            }
        }
        goto plain_r;
    r_1: mode_bits = 0x8000; goto have_r;
    r_2: mode_bits = 0x9000; goto have_r;
    r_3: mode_bits = 0xA000; goto have_r;
    r_4: mode_bits = 0xB000; goto have_r;
    r_5: mode_bits = 0xC000; goto have_r;
    r_6: mode_bits = 0xD000; goto have_r;
    r_7: mode_bits = 0xE000; goto have_r;
    plain_r:
        right_volume = attr->mvol.right;
        mode_bits = 0;
    have_r:
        if (mode_bits != 0) {
            right_level = attr->mvol.right;
            right_level_s16 = attr->mvol.right;
            if (right_level > 0x7F) {
                right_volume = 0x7F;
            } else if (right_level < 0) {
                right_volume = 0;
            } else {
                right_volume = right_level_s16;
            }
        }
        D_80079958->mvolr = (right_volume & 0x7FFF) | mode_bits;
    }

    if (set_all || (mask & 0x40)) {
        D_80079958->cdvoll = attr->cd.volume.left;
    }
    if (set_all || (mask & 0x80)) {
        D_80079958->cdvolr = attr->cd.volume.right;
    }
    if (set_all || (mask & 0x400)) {
        D_80079958->extvoll = attr->ext.volume.left;
    }
    if (set_all || (mask & 0x800)) {
        D_80079958->extvolr = attr->ext.volume.right;
    }
    if (set_all || (mask & 0x100)) {
        if (attr->cd.reverb == 0) {
            spu_control = D_80079958->spucnt;
            spu_control &= 0xFFFB;
            D_80079958->spucnt = spu_control;
        } else {
            spu_control = D_80079958->spucnt;
            spu_control |= 0x4;
            D_80079958->spucnt = spu_control;
        }
    }
    if (set_all || (mask & 0x200)) {
        if (attr->cd.mix == 0) {
            spu_control = D_80079958->spucnt;
            spu_control &= 0xFFFE;
            D_80079958->spucnt = spu_control;
        } else {
            spu_control = D_80079958->spucnt;
            spu_control |= 0x1;
            D_80079958->spucnt = spu_control;
        }
    }
    if (set_all || (mask & 0x1000)) {
        if (attr->ext.reverb == 0) {
            spu_control = D_80079958->spucnt;
            spu_control &= 0xFFF7;
            D_80079958->spucnt = spu_control;
        } else {
            spu_control = D_80079958->spucnt;
            spu_control |= 0x8;
            D_80079958->spucnt = spu_control;
        }
    }
    if (set_all || (mask & 0x2000)) {
        if (attr->ext.mix == 0) {
            spu_control = D_80079958->spucnt;
            spu_control &= 0xFFFD;
            D_80079958->spucnt = spu_control;
        } else {
            spu_control = D_80079958->spucnt;
            spu_control |= 0x2;
            D_80079958->spucnt = spu_control;
        }
    }
}
