/* func_8005F134 -- BYTE-EXACT, LINKABLE candidate (computed-goto idiom).
 * Config: tools/match.py --gcc 2.7.2 --opt O2 (aspsx 2.56).
 * NOTE: --preserve-casesi-at is NO LONGER NEEDED. The computed goto emits
 * `lw $v0,jtbl($v0)`, which the assembler macro-expands through $at into
 * retail's exact dispatch (lui $at,%hi / addu $at,$at,$v0 / lw $v0,%lo($at)).
 * Verified byte-exact both with and without the flag.
 *
 * Both switches dispatch through the RETAIL tables jtbl_8003327C /
 * jtbl_8003329C (absolutes in config/generated/slus_006.14.undefined_syms.txt),
 * so this TU emits NO compiler-generated jump table into .text-referenced
 * .rodata and links. Idiom from src/w_800595C0.c: `keepalive` exists only to
 * stop gcc deleting the case labels; it lands in .rodata but is unreferenced
 * from .text, so the linker discards it silently.
 *
 * WHY THE ASM_REG PINS (they are forced by the idiom, not by the C):
 * taking a label's address puts it in gcc's forced_labels, and flow.c then
 * gives every computed goto an edge to EVERY such label. A value that is live
 * across the dispatch (voll / volr) therefore looks live-in at the labels, and
 * so live all the way around the loop and across the func_8005D598 calls ->
 * gcc parks it in a callee-saved register and grows the frame by 8 bytes.
 * Retail (compiled from a real switch, with exact flow) keeps it in $a1.
 * The pins restore retail's assignment. voll / volr / tmp share $a1 because
 * their live ranges are strictly disjoint -- voll dies at the end of the
 * mask&1 block, volr at the end of the mask&2 block, tmp inside each ADSR
 * block -- which is exactly why retail's allocator reused $a1 for all three.
 * Same pattern as src/w_800595C0.c, which pins four distinct locals to $2.
 * Under -DNON_MATCHING every pin degrades to a plain local, so the portable
 * build is unaffected.
 *
 * Identity: PsyQ libspu's SpuSetVoiceAttr worker -- arg0 is SpuVoiceAttr,
 * D_80079958.ptr is the SPU voice-register shadow (_spu_RXX, 8 u16 per voice),
 * D_80079520[] the per-voice sample-note table, func_8005F7D0 the note->pitch
 * converter, func_8005D598 the (already landed) SPU address-register writer.
 */
#include "common.h"

typedef struct SpuVolume_ {
    s16 left;
    s16 right;
} SpuVolume_;

typedef struct SpuVoiceAttr_ {
    u32 voice;          /* 0x00 */
    u32 mask;           /* 0x04 */
    SpuVolume_ volume;  /* 0x08 */
    SpuVolume_ volmode; /* 0x0C */
    SpuVolume_ volumex; /* 0x10 */
    u16 pitch;          /* 0x14 */
    u16 note;           /* 0x16 */
    u16 sample_note;    /* 0x18 */
    s16 envx;           /* 0x1A */
    u32 addr;           /* 0x1C */
    u32 loop_addr;      /* 0x20 */
    s32 a_mode;         /* 0x24 */
    s32 s_mode;         /* 0x28 */
    s32 r_mode;         /* 0x2C */
    u16 ar;             /* 0x30 */
    u16 dr;             /* 0x32 */
    u16 sr;             /* 0x34 */
    u16 rr;             /* 0x36 */
    u16 sl;             /* 0x38 */
    u16 adsr1;          /* 0x3A */
    u16 adsr2;          /* 0x3C */
} SpuVoiceAttr_;

typedef struct { volatile u16 *ptr; u32 pad2[2]; } S_80079958;
extern S_80079958 D_80079958;
extern u16 D_80079520[24];
extern void *jtbl_8003327C[];
extern void *jtbl_8003329C[];

extern s16 func_8005F7D0(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8005D598(s32 reg, u32 val);

void func_8005F134(SpuVoiceAttr_ *attr)
{
    s32 i;
    u32 mask;
    s32 vreg;
    s32 all;
    register s32 voll ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    register s32 volr ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 mode;
    s32 sub;
    register u16 tmp ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u16 old;
    register u16 vraw ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    u16 cn;
    u16 nt;
    s16 vm;
    s32 idx;
    static void *const keepalive[] = {
        &&L_vl_1, &&L_vl_2, &&L_vl_3, &&L_vl_4, &&L_vl_5, &&L_vl_6, &&L_vl_7,
        &&L_vr_1, &&L_vr_2, &&L_vr_3, &&L_vr_4, &&L_vr_5, &&L_vr_6, &&L_vr_7
    };
    volatile s32 j;
    volatile s32 x;

    (void)keepalive;

    mask = attr->mask;
    all = (mask == 0);
    for (i = 0; i < 24; i++) {
        if (attr->voice & (1 << i)) {
            vreg = i * 8;
            if (all || (mask & 0x10)) {
                D_80079958.ptr[i * 8 + 2] = attr->pitch;
            }
            if (all || (mask & 0x40)) {
                D_80079520[i] = attr->sample_note;
            }
            if (all || (mask & 0x20)) {
                cn = D_80079520[i];
                nt = attr->note;
                D_80079958.ptr[vreg + 2] =
                    func_8005F7D0(cn >> 8, cn & 0xFF, nt >> 8, nt & 0xFF);
            }
            if (all || (mask & 0x1)) {
                mode = 0;
                vraw = attr->volume.left;
                voll = vraw & 0x7FFF;
                if (all || (mask & 0x4)) {
                    vm = attr->volmode.left - 1;
                    idx = vm;
                    if ((u32)idx >= 7) {
                        goto L_vl_end;
                    }
                    goto *jtbl_8003327C[idx];
L_vl_1:
                    mode = 0x8000;
                    goto L_vl_end;
L_vl_2:
                    mode = 0x9000;
                    goto L_vl_end;
L_vl_3:
                    mode = 0xA000;
                    goto L_vl_end;
L_vl_4:
                    mode = 0xB000;
                    goto L_vl_end;
L_vl_5:
                    mode = 0xC000;
                    goto L_vl_end;
L_vl_6:
                    mode = 0xD000;
                    goto L_vl_end;
L_vl_7:
                    mode = 0xE000;
L_vl_end:
                    ;
                }
                if (mode != 0) {
                    if (attr->volume.left >= 0x80) {
                        voll = 0x7F;
                    } else if (attr->volume.left < 0) {
                        voll = 0;
                    }
                }
                D_80079958.ptr[vreg + 0] = voll | mode;
            }
            if (all || (mask & 0x2)) {
                mode = 0;
                vraw = attr->volume.right;
                volr = vraw & 0x7FFF;
                if (all || (mask & 0x8)) {
                    vm = attr->volmode.right - 1;
                    idx = vm;
                    if ((u32)idx >= 7) {
                        goto L_vr_end;
                    }
                    goto *jtbl_8003329C[idx];
L_vr_1:
                    mode = 0x8000;
                    goto L_vr_end;
L_vr_2:
                    mode = 0x9000;
                    goto L_vr_end;
L_vr_3:
                    mode = 0xA000;
                    goto L_vr_end;
L_vr_4:
                    mode = 0xB000;
                    goto L_vr_end;
L_vr_5:
                    mode = 0xC000;
                    goto L_vr_end;
L_vr_6:
                    mode = 0xD000;
                    goto L_vr_end;
L_vr_7:
                    mode = 0xE000;
L_vr_end:
                    ;
                }
                if (mode != 0) {
                    if (attr->volume.right >= 0x80) {
                        volr = 0x7F;
                    } else if (attr->volume.right < 0) {
                        volr = 0;
                    }
                }
                D_80079958.ptr[vreg + 1] = volr | mode;
            }
            if (all || (mask & 0x80)) {
                func_8005D598(vreg + 3, attr->addr);
            }
            if (all || (mask & 0x10000)) {
                func_8005D598(vreg + 7, attr->loop_addr);
            }
            if (all || (mask & 0x20000)) {
                D_80079958.ptr[vreg + 4] = attr->adsr1;
            }
            if (all || (mask & 0x40000)) {
                D_80079958.ptr[vreg + 5] = attr->adsr2;
            }
            if (all || (mask & 0x800)) {
                tmp = attr->ar;
                if (tmp >= 0x80) {
                    tmp = 0x7F;
                }
                sub = 0;
                if (all || (mask & 0x100)) {
                    if (attr->a_mode == 5) {
                        sub = 0x80;
                    }
                }
                old = D_80079958.ptr[vreg + 4];
                old = (old & 0xFF) | ((tmp | sub) << 8);
                D_80079958.ptr[vreg + 4] = old;
            }
            if (all || (mask & 0x1000)) {
                tmp = attr->dr;
                if (tmp >= 0x10) {
                    tmp = 0xF;
                }
                old = D_80079958.ptr[vreg + 4];
                old = (old & 0xFF0F) | (tmp << 4);
                D_80079958.ptr[vreg + 4] = old;
            }
            if (all || (mask & 0x2000)) {
                tmp = attr->sr;
                if (tmp >= 0x80) {
                    tmp = 0x7F;
                }
                sub = 0x100;
                if (all || (mask & 0x200)) {
                    switch (attr->s_mode) {
                    case 1:
                        sub = 0;
                        break;
                    case 5:
                        sub = 0x200;
                        break;
                    case 7:
                        sub = 0x300;
                        break;
                    }
                }
                old = D_80079958.ptr[vreg + 5];
                old = (old & 0x3F) | ((tmp | sub) << 6);
                D_80079958.ptr[vreg + 5] = old;
            }
            if (all || (mask & 0x4000)) {
                tmp = attr->rr;
                if (tmp >= 0x20) {
                    tmp = 0x1F;
                }
                sub = 0;
                if (all || (mask & 0x400)) {
                    switch (attr->r_mode) {
                    case 3:
                        sub = 0;
                        break;
                    case 7:
                        sub = 0x20;
                        break;
                    }
                }
                old = D_80079958.ptr[vreg + 5];
                old = (old & 0xFFC0) | (tmp | sub);
                D_80079958.ptr[vreg + 5] = old;
            }
            if (all || (mask & 0x8000)) {
                tmp = attr->sl;
                if (tmp >= 0x10) {
                    tmp = 0xF;
                }
                old = D_80079958.ptr[vreg + 4];
                old = (old & 0xFFF0) | tmp;
                D_80079958.ptr[vreg + 4] = old;
            }
        }
    }
    x = 1;
    for (j = 0; j < 2; j++) {
        x = x * 13;
    }
}
