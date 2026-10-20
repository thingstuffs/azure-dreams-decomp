#ifndef COMMON_H
#define COMMON_H

/* Put each INCLUDE_ASM'd function in its own .text.<name> section so the linker
 * can sort all functions (C + asm, across multi-compiler TU files) back into
 * address order via SORT_BY_NAME(.text.func_*). Defined here (not in the
 * splat-regenerated include_asm.h) so a re-split can't clobber it; the guard
 * makes include_asm.h skip its own plain-.text definition. */
#if !defined(M2CTX) && !defined(PERMUTER)
#define INCLUDE_ASM(FOLDER, NAME) \
    __asm__( \
        ".section .text." #NAME ",\"ax\",@progbits\n" \
        "    .set noat\n" \
        "    .set noreorder\n" \
        "    .include \"" FOLDER "/" #NAME ".s\"\n" \
        "    .set reorder\n" \
        "    .set at\n" \
    )
#endif

#include "include_asm.h"
#include "game.h"
#include "globals.h"

typedef unsigned char  u8;
typedef signed char    s8;
typedef unsigned short u16;
typedef short          s16;
typedef unsigned int   u32;
typedef int            s32;

/* ===========================================================================
 * gte_* -- GTE (COP2) intrinsic family.
 *
 * gcc 2.7.2 has no C lowering for coprocessor 2 -- no intrinsic, no builtin,
 * no pattern -- so the original psyq source could not have contained plain C
 * for these words either: the COP2 stream comes from psyq's own
 * `inline_c.h`/`gtemac.h`, whose gte_* macros are fixed inline-asm templates.
 * The macros below reproduce those templates, so they are the original source
 * construct, not a transcription of the target. Every gte_* body is a fixed
 * psyq template: COP2 transfer/command words only (the %0 operands are gcc's
 * choice), plus the load-delay `nop`s and the `sra`/`sh`/`sw` that belong to a
 * psyq macro's own published body. Both arms below define the same set of
 * macros.
 *
 * MATCHING ARM. Every template is __volatile__ spelled out: gcc 2.7.2 does not
 * treat an output-less asm as implicitly volatile, and every GTE op has side
 * effects on the COP2 register file that gcc cannot see. Stores also carry a
 * "memory" clobber; loads and commands deliberately do not (that is psyq's own
 * shape). Command words are written as the `cop2 <imm25>` mnemonic, which
 * assembles to the exact retail word with mipsel-linux-gnu-as -march=r3000;
 * `.word 0x4Axxxxxx` is the equivalent fallback if a future binutils drops the
 * r3000 cop2 mnemonic. No "+r" constraint is used (gcc 2.7.x rejects `+`).
 *
 * PORT ARM (-DNON_MATCHING) is a REAL GTE, not a no-op: these ops COMPUTE
 * values that the surrounding C then stores and branches on, so a stub would
 * silently corrupt the port. gte_port_* below implements the psx-spx GTE
 * semantics (1/4096 fixed point, saturation, FIFOs, the UNR division) over one
 * shared register file, `g_gte`; exactly one port TU defines the storage with
 *     #define GTE_PORT_STATE_OWNER
 *     #include "common.h"
 * and the ported libgte (SetRotMatrix/SetTransMatrix/SetGeomOffset/...) must
 * write g_gte's control registers -- the ops here only READ them.
 * MODELLED: MAC0-3 and IR0-3 saturation+flags, SZ/SXY/RGB FIFOs, OTZ, and the
 * FLAG register (bit 31 error summary over the documented lanes) because
 * func_800CA184 reads FLAG via gte_stflg. NOT modelled (documented, not
 * accidental): the 44-bit MAC accumulator's wrap-on-overflow (we flag and keep
 * the wide value), per-term overflow detection (we check the accumulated sum),
 * and the RTPS/RTPT lm=1 IR3-flag quirk (every row here uses lm=0 there).
 * =========================================================================== */
#ifdef NON_MATCHING

typedef struct {
    /* control registers -- written by the ported libgte, read-only here */
    s16 rt[9];                  /* cop2c0-4    rotation matrix, row major     */
    s32 tr[3];                  /* cop2c5-7    translation vector             */
    s16 llm[9];                 /* cop2c8-12   light matrix                   */
    s32 bk[3];                  /* cop2c13-15  background colour              */
    s16 lcm[9];                 /* cop2c16-20  light colour matrix            */
    s32 fc[3];                  /* cop2c21-23  far colour                     */
    s32 ofx, ofy;               /* cop2c24-25  screen offset, 1/65536         */
    u16 h;                      /* cop2c26     projection distance            */
    s16 dqa;                    /* cop2c27     depth-cue scale                */
    s32 dqb;                    /* cop2c28     depth-cue offset               */
    s16 zsf3, zsf4;             /* cop2c29-30  average-Z scale factors        */
    u32 flag;                   /* cop2c31     error flags                    */
    /* data registers */
    s16 v[3][3];                /* cop2d0-5    V0/V1/V2                       */
    u8 rgbc[4];                 /* cop2d6      R,G,B,CODE                     */
    u16 otz;                    /* cop2d7                                     */
    s16 ir[4];                  /* cop2d8-11   IR0..IR3                       */
    s16 sx[3], sy[3];           /* cop2d12-14  SXY0..SXY2 FIFO                */
    u16 sz[4];                  /* cop2d16-19  SZ0..SZ3 FIFO                  */
    u8 rgb[3][4];               /* cop2d20-22  RGB0..RGB2 FIFO                */
    s32 mac[4];                 /* cop2d24-27  MAC0..MAC3                     */
} GteState;

#ifdef GTE_PORT_STATE_OWNER
GteState g_gte;
#else
extern GteState g_gte;
#endif

/* FLAG lanes that feed the bit-31 error summary (psx-spx: bits 30..23, 18..13). */
#define GTE_FLAG_ERROR_MASK 0x7F87E000u

/* MAC1..3 <- 44-bit accumulator, flagged, then arithmetic-shifted by `sh`. */
static __inline__ s32 gte_port_setmac(int i, long long v, int sh)
{
    if (v > 0x7FFFFFFFFFFLL) {
        g_gte.flag |= 1u << (31 - i);           /* bits 30/29/28: MAC1/2/3 pos */
    } else if (v < -0x80000000000LL) {
        g_gte.flag |= 1u << (28 - i);           /* bits 27/26/25: MAC1/2/3 neg */
    }
    g_gte.mac[i] = (s32)(v >> sh);
    return g_gte.mac[i];
}

static __inline__ s32 gte_port_setmac0(long long v)
{
    if (v > 2147483647LL) {
        g_gte.flag |= 1u << 16;
    } else if (v < -2147483647LL - 1LL) {
        g_gte.flag |= 1u << 15;
    }
    g_gte.mac[0] = (s32)v;
    return g_gte.mac[0];
}

/* IR1..3 <- MAC, saturated to [lm ? 0 : -8000h, 7FFFh]; flags 24/23/22. */
static __inline__ void gte_port_setir(int i, s32 v, int lm)
{
    s32 lo = lm ? 0 : -32768;
    if (v > 32767) {
        g_gte.flag |= 1u << (25 - i);
        v = 32767;
    } else if (v < lo) {
        g_gte.flag |= 1u << (25 - i);
        v = lo;
    }
    g_gte.ir[i] = (s16)v;
}

static __inline__ void gte_port_begin(void)
{
    g_gte.flag = 0;                             /* hardware clears FLAG per op */
}

static __inline__ void gte_port_end(void)
{
    if (g_gte.flag & GTE_FLAG_ERROR_MASK) {
        g_gte.flag |= 0x80000000u;
    }
}

/* [MAC1..3] = ((cv << 12) + M * V) >> sh ; [IR1..3] = saturate(MAC, lm).
 * `cv` may be a null pointer for the no-translation forms. */
static __inline__ void gte_port_matvec(const s16 *m, const s16 *v,
                                       const s32 *cv, int sh, int lm)
{
    int i;
    for (i = 0; i < 3; i++) {
        long long acc = cv ? ((long long)cv[i] << 12) : 0LL;
        acc += (long long)(m[i * 3 + 0] * v[0]);
        acc += (long long)(m[i * 3 + 1] * v[1]);
        acc += (long long)(m[i * 3 + 2] * v[2]);
        gte_port_setmac(i + 1, acc, sh);
        gte_port_setir(i + 1, g_gte.mac[i + 1], lm);
    }
}

/* GTE unsigned Newton-Raphson divide: (H*20000h/SZ3 + 1)/2, clamped to 1FFFFh.
 * The UNR seed table is the documented closed form, evaluated on the fly so the
 * header carries no 257-byte blob. */
static __inline__ u32 gte_port_divide(u32 h, u32 sz3)
{
    u32 n, d, u;
    s32 seed, idx;
    if (sz3 == 0 || h >= sz3 * 2) {
        g_gte.flag |= 1u << 17;                 /* divide overflow */
        return 0x1FFFFu;
    }
    n = h;
    d = sz3;
    while (!(d & 0x8000u)) {                    /* normalise: bit15 of d set */
        d <<= 1;
        n <<= 1;
    }
    idx = (s32)((d - 0x7FC0u) >> 7);            /* 0..100h */
    seed = (0x40000 / (idx + 0x100) + 1) / 2 - 0x101;
    if (seed < 0) {
        seed = 0;
    } else if (seed > 0xFF) {
        seed = 0xFF;
    }
    u = (u32)seed + 0x101u;
    d = (u32)((s32)(0x2000080 - (s32)(d * u)) >> 8);
    d = (u32)((s32)(0x0000080 + (s32)(d * u)) >> 8);
    n = (u32)(((unsigned long long)n * d + 0x8000ULL) >> 16);
    return n > 0x1FFFFu ? 0x1FFFFu : n;
}

/* One RTPS pass over V[vi]: rotate+translate, push SZ and SXY, depth-cue IR0. */
static __inline__ void gte_port_rtps_one(int vi)
{
    s32 sz3, sx, sy;
    u32 q;
    gte_port_matvec(g_gte.rt, g_gte.v[vi], g_gte.tr, 12, 0);
    sz3 = g_gte.mac[3];
    g_gte.sz[0] = g_gte.sz[1];
    g_gte.sz[1] = g_gte.sz[2];
    g_gte.sz[2] = g_gte.sz[3];
    if (sz3 < 0) {
        g_gte.flag |= 1u << 18;
        sz3 = 0;
    } else if (sz3 > 0xFFFF) {
        g_gte.flag |= 1u << 18;
        sz3 = 0xFFFF;
    }
    g_gte.sz[3] = (u16)sz3;
    q = gte_port_divide(g_gte.h, (u32)sz3);
    sx = (s32)(gte_port_setmac0((long long)q * g_gte.ir[1] + g_gte.ofx) >> 16);
    sy = (s32)(gte_port_setmac0((long long)q * g_gte.ir[2] + g_gte.ofy) >> 16);
    if (sx < -1024) {
        g_gte.flag |= 1u << 14;
        sx = -1024;
    } else if (sx > 1023) {
        g_gte.flag |= 1u << 14;
        sx = 1023;
    }
    if (sy < -1024) {
        g_gte.flag |= 1u << 13;
        sy = -1024;
    } else if (sy > 1023) {
        g_gte.flag |= 1u << 13;
        sy = 1023;
    }
    g_gte.sx[0] = g_gte.sx[1];
    g_gte.sy[0] = g_gte.sy[1];
    g_gte.sx[1] = g_gte.sx[2];
    g_gte.sy[1] = g_gte.sy[2];
    g_gte.sx[2] = (s16)sx;
    g_gte.sy[2] = (s16)sy;
    {
        s32 ir0 = (s32)(gte_port_setmac0((long long)q * g_gte.dqa + g_gte.dqb) >> 12);
        if (ir0 < 0) {
            g_gte.flag |= 1u << 12;
            ir0 = 0;
        } else if (ir0 > 4096) {
            g_gte.flag |= 1u << 12;
            ir0 = 4096;
        }
        g_gte.ir[0] = (s16)ir0;
    }
}

/* RGB FIFO push from MAC1..3 >> 4 (flags 21/20/19) + IR writeback. */
static __inline__ void gte_port_push_rgb(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        g_gte.rgb[0][i] = g_gte.rgb[1][i];
        g_gte.rgb[1][i] = g_gte.rgb[2][i];
    }
    for (i = 0; i < 3; i++) {
        s32 c = g_gte.mac[i + 1] >> 4;
        if (c < 0) {
            g_gte.flag |= 1u << (21 - i);
            c = 0;
        } else if (c > 255) {
            g_gte.flag |= 1u << (21 - i);
            c = 255;
        }
        g_gte.rgb[2][i] = (u8)c;
        gte_port_setir(i + 1, g_gte.mac[i + 1], 1);
    }
    g_gte.rgb[2][3] = g_gte.rgbc[3];
}

/* NCCS (depth_cue=0) / NCDS (depth_cue=1), both sf=1 lm=1. */
static __inline__ void gte_port_ncs(int depth_cue)
{
    int i;
    gte_port_begin();
    gte_port_matvec(g_gte.llm, g_gte.v[0], (const s32 *)0, 12, 1);
    gte_port_matvec(g_gte.lcm, &g_gte.ir[1], g_gte.bk, 12, 1);
    for (i = 0; i < 3; i++) {
        gte_port_setmac(i + 1,
                        ((long long)g_gte.rgbc[i] * g_gte.ir[i + 1]) << 4, 0);
    }
    if (depth_cue) {
        /* IR = ((FC << 12) - MAC) >> 12, saturated with lm=0 (hardware forces
         * lm=0 for this step even when the command's lm=1); MAC += IR * IR0. */
        for (i = 0; i < 3; i++) {
            long long d = ((long long)g_gte.fc[i] << 12) - g_gte.mac[i + 1];
            gte_port_setir(i + 1, (s32)(d >> 12), 0);
        }
        for (i = 0; i < 3; i++) {
            gte_port_setmac(i + 1,
                            (long long)g_gte.ir[i + 1] * g_gte.ir[0]
                                + g_gte.mac[i + 1], 0);
        }
    }
    for (i = 0; i < 3; i++) {
        gte_port_setmac(i + 1, (long long)g_gte.mac[i + 1], 12);
    }
    gte_port_push_rgb();
    gte_port_end();
}

static __inline__ void gte_port_avsz3(void)
{
    s32 otz = (s32)(gte_port_setmac0((long long)g_gte.zsf3
                                     * ((s32)g_gte.sz[1] + (s32)g_gte.sz[2]
                                        + (s32)g_gte.sz[3])) >> 12);
    if (otz < 0) {
        g_gte.flag |= 1u << 18;
        otz = 0;
    } else if (otz > 0xFFFF) {
        g_gte.flag |= 1u << 18;
        otz = 0xFFFF;
    }
    g_gte.otz = (u16)otz;
}

static __inline__ void gte_port_ldv(int vi, const void *p)
{
    const s16 *s = (const s16 *)p;
    g_gte.v[vi][0] = s[0];
    g_gte.v[vi][1] = s[1];
    g_gte.v[vi][2] = s[2];
}

static __inline__ void gte_port_ldrgb(const void *p)
{
    const u8 *s = (const u8 *)p;
    g_gte.rgbc[0] = s[0];
    g_gte.rgbc[1] = s[1];
    g_gte.rgbc[2] = s[2];
    g_gte.rgbc[3] = s[3];
}

static __inline__ u32 gte_port_sxy(int i)
{
    return ((u32)(u16)g_gte.sy[i] << 16) | (u32)(u16)g_gte.sx[i];
}

static __inline__ u32 gte_port_rgb2(void)
{
    return (u32)g_gte.rgb[2][0] | ((u32)g_gte.rgb[2][1] << 8)
         | ((u32)g_gte.rgb[2][2] << 16) | ((u32)g_gte.rgb[2][3] << 24);
}

static __inline__ void gte_port_stsv(void *p)
{
    s16 *d = (s16 *)p;
    d[0] = g_gte.ir[1];
    d[1] = g_gte.ir[2];
    d[2] = g_gte.ir[3];
}

/* -- transfers ---------------------------------------------------------- */
#define gte_ldv0(r0)            gte_port_ldv(0, (const void *)(r0))
#define gte_ldv3(r0, r1, r2)    (gte_port_ldv(0, (const void *)(r0)), \
                                 gte_port_ldv(1, (const void *)(r1)), \
                                 gte_port_ldv(2, (const void *)(r2)))
#define gte_ldrgb(r0)           gte_port_ldrgb((const void *)(r0))
#define gte_ldir0(r0)           (g_gte.ir[0] = (s16)(r0))

/* -- commands ----------------------------------------------------------- */
#define gte_rtv0tr()            (gte_port_begin(), \
                                 gte_port_matvec(g_gte.rt, g_gte.v[0], g_gte.tr, 12, 0), \
                                 gte_port_end())
#define gte_rtps()              (gte_port_begin(), gte_port_rtps_one(0), gte_port_end())
#define gte_rtpt()              (gte_port_begin(), gte_port_rtps_one(0), \
                                 gte_port_rtps_one(1), gte_port_rtps_one(2), \
                                 gte_port_end())
/* _nn ("no nops") variants -- see the MIPS arm for when these are correct. The
 * nops are a hardware hazard cover with no portable meaning, so on this arm the
 * _nn forms are exact aliases of the plain ones. */
#define gte_rtps_nn()           gte_rtps()
#define gte_rtpt_nn()           gte_rtpt()
#define gte_ncds_nn()           gte_ncds()
#define gte_nclip()             (gte_port_begin(), \
                                 gte_port_setmac0( \
                                     (long long)g_gte.sx[0] * g_gte.sy[1] \
                                   + (long long)g_gte.sx[1] * g_gte.sy[2] \
                                   + (long long)g_gte.sx[2] * g_gte.sy[0] \
                                   - (long long)g_gte.sx[0] * g_gte.sy[2] \
                                   - (long long)g_gte.sx[1] * g_gte.sy[0] \
                                   - (long long)g_gte.sx[2] * g_gte.sy[1]), \
                                 gte_port_end())
#define gte_avsz3()             (gte_port_begin(), \
                                 gte_port_avsz3(), \
                                 gte_port_end())
#define gte_nccs()              gte_port_ncs(0)
#define gte_ncds()              gte_port_ncs(1)

/* -- stores ------------------------------------------------------------- */
#define gte_stsv(r0)            gte_port_stsv((void *)(r0))
#define gte_stsxy(r0)           (*(u32 *)(void *)(r0) = gte_port_sxy(2))
#define gte_stsxy3_g3(r0)       (*(u32 *)(void *)((char *)(void *)(r0) + 8) = gte_port_sxy(0), \
                                 *(u32 *)(void *)((char *)(void *)(r0) + 16) = gte_port_sxy(1), \
                                 *(u32 *)(void *)((char *)(void *)(r0) + 24) = gte_port_sxy(2))
#define gte_stsxy3(r0, r1, r2)  (*(u32 *)(void *)(r0) = gte_port_sxy(0), \
                                 *(u32 *)(void *)(r1) = gte_port_sxy(1), \
                                 *(u32 *)(void *)(r2) = gte_port_sxy(2))
#define gte_stotz(r0)           (*(u32 *)(void *)(r0) = (u32)g_gte.otz)
#define gte_stopz(r0)           (*(s32 *)(void *)(r0) = g_gte.mac[0])
#define gte_stszotz(r0)         (*(s32 *)(void *)(r0) = (s32)g_gte.sz[3] >> 2)
#define gte_stdp(r0)            (*(s32 *)(void *)(r0) = (s32)g_gte.ir[0])
#define gte_stflg(r0)           (*(u32 *)(void *)(r0) = g_gte.flag)
#define gte_strgb(r0)           (*(u32 *)(void *)(r0) = gte_port_rgb2())

#else /* !NON_MATCHING -- byte-matching arm: psyq's own COP2 templates */

/* -- transfers ---------------------------------------------------------- */
#define gte_ldv0(r0) \
    __asm__ __volatile__("lwc2 $0, 0(%0);lwc2 $1, 4(%0)" : : "r"(r0))
#define gte_ldv3(r0, r1, r2) \
    __asm__ __volatile__("lwc2 $0, 0(%0);lwc2 $1, 4(%0);" \
                         "lwc2 $2, 0(%1);lwc2 $3, 4(%1);" \
                         "lwc2 $4, 0(%2);lwc2 $5, 4(%2)" \
                         : : "r"(r0), "r"(r1), "r"(r2))
#define gte_ldrgb(r0) \
    __asm__ __volatile__("lwc2 $6, 0(%0)" : : "r"(r0))
/* IR0 from a REGISTER value (not memory) -- retail 0x800AFEC4 `mtc2 $v1,$8`. */
#define gte_ldir0(r0) \
    __asm__ __volatile__("mtc2 %0, $8" : : "r"(r0))

/* -- commands ----------------------------------------------------------- */
/* The two leading nops are part of psyq's command macros: they cover the GTE's
 * load-use latency after the lwc2/mtc2 transfer that precedes the command. */
#define gte_rtv0tr()    __asm__ __volatile__("nop;nop;cop2 0x0480012")
#define gte_rtps()      __asm__ __volatile__("nop;nop;cop2 0x0180001")
#define gte_rtpt()      __asm__ __volatile__("nop;nop;cop2 0x0280030")
/* _nn ("no nops"): the SAME command with psyq's two leading hazard nops omitted.
 * Retail omits them wherever the load-use latency after the preceding lwc2/mtc2
 * is ALREADY covered -- by the scheduled instructions that separate the transfer
 * from the command, or by a preceding command's own latency. Those sites are
 * two words shorter than the plain macro can express, and no source-level or
 * scheduling change can delete literal nop text embedded in a fixed asm template.
 *
 * USE ONLY where the retail bytes show no leading nops. These are NOT a general
 * optimisation: dropping the cover where the hazard is real changes GTE results
 * on hardware. Within a single function some sites need the nops and others do
 * not (func_800AED64 carries both forms -- its second gte_rtpt() keeps them, and
 * blanket removal there measured aligned 8 with two words missing). */
#define gte_rtps_nn()   __asm__ __volatile__("cop2 0x0180001")
#define gte_rtpt_nn()   __asm__ __volatile__("cop2 0x0280030")
#define gte_ncds_nn()   __asm__ __volatile__("cop2 0x0E80413")
#define gte_nclip()     __asm__ __volatile__("nop;nop;cop2 0x1400006")
#define gte_avsz3()     __asm__ __volatile__("nop;nop;cop2 0x158002D")
#define gte_nccs()      __asm__ __volatile__("nop;nop;cop2 0x108041B")
#define gte_ncds()      __asm__ __volatile__("nop;nop;cop2 0x0E80413")

/* -- stores ------------------------------------------------------------- */
#define gte_stsv(r0) \
    __asm__ __volatile__("mfc2 $12, $9;mfc2 $13, $10;mfc2 $14, $11;" \
                         "sh $12, 0(%0);sh $13, 2(%0);sh $14, 4(%0)" \
                         : : "r"(r0) : "$12", "$13", "$14", "memory")
#define gte_stsxy(r0) \
    __asm__ __volatile__("swc2 $14, 0(%0)" : : "r"(r0) : "memory")
/* SXY0/1/2 into ONE base at the POLY_G3 vertex offsets 8/16/24 (retail
 * 0x800AF210, 0x800AFDE8, 0x800CA904) -- a 3-address gte_stsxy3 would emit
 * three separate address computations. */
#define gte_stsxy3_g3(r0) \
    __asm__ __volatile__("swc2 $12, 8(%0);swc2 $13, 16(%0);swc2 $14, 24(%0)" \
                         : : "r"(r0) : "memory")
/* SXY0/1/2 into three DISTINCT addresses (retail func_8004C36C) -- not the
 * one-base POLY_G3 form above; each vertex earns its own address register. */
#define gte_stsxy3(r0, r1, r2) \
    __asm__ __volatile__("swc2 $12, 0(%0);swc2 $13, 0(%1);swc2 $14, 0(%2)" \
                         : : "r"(r0), "r"(r1), "r"(r2) : "memory")
#define gte_stotz(r0) \
    __asm__ __volatile__("swc2 $7, 0(%0)" : : "r"(r0) : "memory")
#define gte_stopz(r0) \
    __asm__ __volatile__("swc2 $24, 0(%0)" : : "r"(r0) : "memory")
#define gte_stszotz(r0) \
    __asm__ __volatile__("mfc2 $12, $19;nop;sra $12, $12, 2;sw $12, 0(%0)" \
                         : : "r"(r0) : "$12", "memory")
#define gte_stdp(r0) \
    __asm__ __volatile__("swc2 $8, 0(%0)" : : "r"(r0) : "memory")
#define gte_stflg(r0) \
    __asm__ __volatile__("cfc2 $12, $31;nop;sw $12, 0(%0)" \
                         : : "r"(r0) : "$12", "memory")
#define gte_strgb(r0) \
    __asm__ __volatile__("swc2 $22, 0(%0)" : : "r"(r0) : "memory")

#endif /* NON_MATCHING (gte_*) */

#endif /* COMMON_H */
