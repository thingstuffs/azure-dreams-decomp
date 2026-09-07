#include "common.h"
typedef struct S_80083958 {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u8  unk4;
    /* 0x5 */ u8  unk5;
    /* 0x6 */ u16 counter1;
    /* 0x8 */ u16 counter2;
    /* 0xA */ u16 flags;
} S_80083958;

typedef struct S_80083968 {
    /* 0x00 */ u8  unk00;
    /* 0x01 */ u8  pad01[3];
    /* 0x04 */ u32 unk04;
    /* 0x08 */ u8  unk08[0xF];
    /* 0x17 */ u8  unk17;
} S_80083968;

typedef struct S_80083164 {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u8  pad2[0xE];
} S_80083164;

extern S_80083958 D_80083958;

/* RETAIL jump table for the state==1 dispatch: an ABSOLUTE in
 * config/generated/slus_006.14.undefined_syms.txt (0x8002D5C0, 28 entries,
 * live cases 0/6/9/0x15/0x1B, every other index -> the `tail` block).
 * Dispatching through it means this TU emits NO compiler-generated jump table
 * into .text-referenced .rodata, which is what makes the object LINK. */
extern void *jtbl_8002D5C0[];
extern S_80083968 D_80083968[32];

extern u8  D_800814D0;        /* head index: $gp scalar */
extern u8  D_800814D1[16];    /* tail index: %hi/%lo (size>8) */
    /* driver state byte: %hi/%lo; head via [-3] */
extern u8  D_800814D4;        /* mode byte store: $gp scalar */
extern u32 D_800814CC;        /* $gp word */
extern u8  D_800814D8[16];    /* %hi/%lo CdReadSync buffer */
extern u8  D_80081450;        /* status byte read: $gp scalar */
extern u8  D_80081438[0x20];  /* neighbour: &D_80081438[0x18]==&D_80081450 (%hi/%lo) */
extern u32 D_80081480[8];     /* %hi/%lo */
extern S_80083164 D_80083164; /* %hi/%lo (size>8) */
extern u8  D_80080AD0;        /* $gp */
extern u16 D_80080AD2;        /* $gp */
extern u16 D_80080AD4;        /* $gp */
extern s32 D_80080AD8;        /* $gp */

extern int  CdSync(int mode, u8 *result);
extern int  CdControl(u8 com, u8 *param, u8 *result);
extern int  CdControlF(u8 com, u8 *param);
extern int  CdRead(int count, u32 *buf, int mode);
extern int  CdRead2(int mode);
extern int  CdReadSync(int mode, u8 *result);
extern int  CdReset(int mode);
extern void StUnSetRing(void);

extern void func_8003E70C(void);
extern void func_8003F5EC(void);
extern void func_8003F624(void);
extern int  func_8003F240(void);
extern void CdIntToPos(u32 lba, u8 *loc);
extern u8  D_800814D3[16];
extern u8  D_800814D3_1[16] __asm__("D_800814D3");
extern u8  D_800814D3_2[16] __asm__("D_800814D3");
extern u8  D_800814D3_3[16] __asm__("D_800814D3");
extern u8  D_800814D3_8[16] __asm__("D_800814D3");
extern u8  D_800814D3_9[16] __asm__("D_800814D3");
extern u8  D_800814D3_10[16] __asm__("D_800814D3");
extern u8  D_800814D3_11[16] __asm__("D_800814D3");
extern u8  D_800814D3_12[16] __asm__("D_800814D3");
extern u8  D_800814D3_13[16] __asm__("D_800814D3");
extern u8  D_800814D3_14[16] __asm__("D_800814D3");
extern u8  D_800814D3_15[16] __asm__("D_800814D3");
extern u8  D_800814D3_24[16] __asm__("D_800814D3");
extern u8  D_800814D2[16];
extern u8  D_800814D2_P[16] __asm__("D_800814D2");
extern u8  D_800814D2_R[16] __asm__("D_800814D2");

#define CDBUF (&D_80081438[0x18])   /* == &D_80081450, %hi/%lo addressing */

void func_8003E758(void)
{
    S_80083958 *p;
    S_80083968 *q, *e, *q3, *e3;
    int state;
    int r, n;
    u8  st;
    int idx;
    u8  loc[8];
    u8  res[8];

loop:
    p = &D_80083958;
    p->flags &= 0xFFFE;

    if (D_800814D0 == D_800814D1[0])
        goto empty;

    p->flags |= 1;
    state = D_800814D3_1[0];

    if (state == 0xFF) {
        q = D_80083968;
        idx = D_800814D0;
        switch (q[idx].unk00) {
        case 0:
            ASM_SCHED_BARRIER();
            D_800814D3_2[0] = 0xFF;
            p->unk4 = 0;
            D_800814D2[0] = 0;
            D_800814D0 = (idx + 1) & 0x1F;
            goto loop;

        case 1:
            r = CdSync(1, res);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) func_8003E70C(); }
            D_800814D2[0] = 2;
            p->unk4 = 2;
            D_800814D0 = D_800814D0 + 1;
            goto tail;

        case 2:
            ASM_SCHED_BARRIER();
            r = CdSync(1, res);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) func_8003E70C(); }
            D_800814D2[0] = 0;
            p->unk4 = 0;
            e = &q[D_800814D0];
            CdIntToPos(e->unk04, loc);
            if (CdControl(2, loc, CDBUF) == 0) goto tail;
            D_800814D0 = D_800814D0 + 1;
            goto tail;

        case 6: {
            u32 *hdr;
            u32 word, base, hi;
            ASM_SCHED_BARRIER();
            r = CdSync(1, res);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) func_8003E70C(); }
            D_800814D2[0] = 0;
            p->unk4 = 0;
            e = &q[D_800814D0];
            hdr = (u32 *)e->unk04;
            word = hdr[0];
            base = word & 0x7FFFFF;
            if (base == 0)
                base = D_80081480[0];
            else
                base = base | 0x80000000;
            hi = hdr[0] >> 23;
            if (hi == 0) {
                u8 *hp3 = &D_800814D3_3[0];
                D_800814D3[0] = 0xFF;
                hp3[-3] += 1;
                goto tail;
            }
            D_800814CC = (base + (hi << 11)) - 4;
            D_800814D4 = 0x80;
            if (CdControl(0xE, &D_800814D3[1], 0) == 0) return;
            r = CdSync(1, res);
            if (r != 0) { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) { func_8003E70C(); return; } }
            CdIntToPos(hdr[1], loc);
            if (CdControl(2, loc, 0) == 0) return;
            r = CdSync(1, res);
            if (r != 0) { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) { func_8003E70C(); return; } }
            if (CdRead(hi, (u32 *)base, 0x80) == 0) return;
            goto set_d3_1;
        }

        case 9:
            r = CdSync(1, res);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) func_8003E70C(); }
            D_800814D2[0] = 0;
            p->unk4 = 0;
            if (CdControl(9, 0, CDBUF) == 0) goto tail;
            goto set_d3_1;

        case 0xD:
            r = CdSync(1, res);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) func_8003E70C(); }
            D_800814D2[0] = 0;
            p->unk4 = 0;
            { int off = D_800814D0 * 24; u8 *a8 = q->unk08; if (CdControl(0xD, off + a8, CDBUF) == 0) goto tail; }
            D_800814D3_8[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto tail;

        case 0xE:
            r = CdSync(1, res);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) func_8003E70C(); }
            D_800814D2[0] = 0;
            p->unk4 = 0;
            { int off = D_800814D0 * 24; u8 *a8 = q->unk08; if (CdControl(0xE, off + a8, CDBUF) == 0) goto tail; }
            D_800814D3_9[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto tail;

        case 0x15:
            r = CdSync(1, res);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) func_8003E70C(); }
            D_800814D2[0] = 0;
            p->unk4 = 0;
            e = &q[D_800814D0];
            CdIntToPos(e->unk04, loc);
            if (CdControlF(0x15, loc) == 0) goto tail;
            goto set_d3_1;

        case 0x1B:
            r = CdSync(1, res);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) func_8003E70C(); }
            D_800814D2[0] = 0;
            p->unk4 = 0;
            e = &q[D_800814D0];
            CdIntToPos(e->unk04, loc);
            n = 0x10;
            if (CdControl(2, loc, 0) == 0) return;
            {
            int five = 5;
            for (;;) {
                r = CdSync(1, res);
                n--;
                if (r == 0) goto c1b_zero;
                n = 0x10;
                if (r != five) goto c1b_read;
            c1b_err:
                func_8003E70C();
                return;
            c1b_zero:
                if (n != 0) continue;
                goto c1b_err;
            c1b_read:
                for (;;) {
                    if (CdRead2(0xC8) != 0) break;
                    if (--n == 0) goto c1b_err;
                }
                D_80083958.unk4 = 0;
            set_d3_1:
                D_800814D3_11[0] = 1;
                goto tail;
            }
            }

        case 0xA:
            ASM_SCHED_BARRIER();
            D_800814D2[0] = 0;
            p->unk4 = 0;
            n = 0x10;
            for (;;) {
                if (CdReset(0) != 0) break;
                if (--n == 0) goto c1b_err;
            }
            D_800814D3[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto tail;

        case 0xFF:
            ASM_SCHED_BARRIER();
            (*(void (*)(u32))q[idx].unk04)(*(u32 *)D_80083968[D_800814D0].unk08);
            D_800814D0 = D_800814D0 + 1;
            goto tail;

        case 0xFC:
            StUnSetRing();
            D_800814D0 = D_800814D0 + 1;
            goto tail;

        case 0x4:
        case 0x8:
        case 0xB:
        case 0xC:
        case 0x10:
        case 0x16:
        default:
            goto tail;
        }
    } else if (state == 1) {
        /* `keepalive` exists only to stop gcc deleting the case labels; it lands
         * in .rodata but is unreferenced from .text, so the linker discards it.
         * Idiom from src/w_800595C0.c / w_8004CECC.c / w_80042BDC.c. */
        static void *const keepalive[] = {
            &&L_s1_00, &&L_s1_06, &&L_s1_09, &&L_s1_15, &&L_s1_1B
        };
        u32 sel;
        (void)keepalive;
        q3 = D_80083968;
        idx = D_800814D0;
        e3 = &q3[idx];
        ASM_USE_NV(e3);
        sel = e3->unk00;
        if (sel >= 0x1C) goto tail;
        goto *jtbl_8002D5C0[sel];
        {
        L_s1_00: {
            register u8 *hp ASM_REG("$4");
            register int ff ASM_REG("$2");
            int nh;
            ff = 0xFF;
            D_800814D3_14[0] = ff;
            hp = &D_800814D3_13[0];
            nh = hp[-3];
            D_80083958.unk4 = 0;
            D_800814D2[0] = 0;
            hp[-3] = (nh + 1) & 0x1F;
            goto loop;
        }

        L_s1_06:
            r = CdSync(1, CDBUF);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) goto p2_done; }
            D_80080AD8 = CdReadSync(1, D_800814D8);
            if (D_80080AD8 > 0) goto tail;
            if (D_80080AD8 != 0) goto c6_neg;
            if (D_80080AD0 == 0) goto c6_blockA;
            if ((*(u32 *)D_800814CC & 0xFFFF0000) == 0x10120000) goto tail;
            func_8003E70C();
            D_800814D2[0] = 0;
            D_80080AD2 = D_80080AD2 + 1;
            if ((D_80080AD2 & 3) == 3) {
                CdReset(0);
                func_8003F5EC();
            }
            D_800814D3[0] = 0xFF;
            goto tail;
        c6_blockA:
            {
                u8 *hp = &D_800814D3_15[0];
                S_80083958 *p2 = &D_80083958;
                D_800814D3[0] = 0xFF;
                p2->unk4 = 2;
                hp[-3] += 1;
                D_800814D2[0] = D_800814D2_R[0] | 1;
                p2->unk5 = p2->unk5 + 1;
                goto tail;
            }
        c6_neg:
            if (D_80080AD8 >= 0) goto tail;
            ASM_SCHED_BARRIER();
            goto p2_done;

        L_s1_09:
            r = CdSync(1, CDBUF);
            if (r == 0) goto tail;
            { register int five5 ASM_REG("$2"); five5 = 5; ASM_KEEP_NV(five5); if (r == five5) goto p2_done; }
            goto p2_status;

        L_s1_15:
            r = CdSync(1, res);
            if (r == 0) goto tail;
            if (r != 5) goto p2_status;
            goto p2_done;

        p2_done:
            func_8003E70C();
            D_800814D3[0] = 0xFF;
            D_80083958.unk4 = 0;
            D_800814D2[0] = 0;
            goto tail;

        p2_status:
            if (CdControl(1, 0, CDBUF) == 0) goto tail;
            if ((D_80081450 & 0xFD) != 0) goto tail;
            D_80083958.unk4 = 2;
            D_800814D3[0] = 0xFF;
            D_800814D0 = D_800814D0 + 1;
            goto tail;

        L_s1_1B:
            if (CdSync(1, CDBUF) == 5) {
                D_800814D3[0] = 0xFF;
                goto tail;
            }
            n = 0x10;
            for (;;) {
                if (CdControl(1, 0, CDBUF) != 0) break;
                if (--n == 0) {
                    func_8003E70C();
                    D_800814D3[0] = 0xFF;
                    return;
                }
            }
            st = D_80081450;
            if (st & 0x40) goto tail;
            if (st & 0x20) {
                u8 *hp2 = &D_800814D2_P[0];
                register S_80083968 *q2 ASM_REG("$3");
                register int ff2 ASM_REG("$2");
                S_80083968 *ep;
                int hi2;
                ff2 = 0xFF;
                q2 = D_80083968;
                ASM_KEEP_NV(hp2);
                ASM_USE_NV(q2);
                D_800814D2[0] = 0;
                D_800814D3[0] = ff2;
                hi2 = hp2[-2];
                ep = &q2[hi2];
                if (ep->unk17 != 0xFF) {
                    register int four ASM_REG("$3");
                    ASM_SCHED_BARRIER();
                    four = 4;
                    D_80083958.unk4 = four;
                    ASM_SCHED_BARRIER();
                    D_80080AD4 = 1;
                }
                hp2[-2] += 1;
                goto tail;
            }
            if (st & 0x80) D_800814D3[0] = 0xFF;
            goto tail;

        }
    }

    goto tail;

empty:
    if (CdSync(1, 0) == 5) {
        if ((func_8003F240() & 0xFF) == 0x1B) {
            D_800814D3_24[0] = 0xFF;
            if (D_800814D0 != 0)
                D_800814D0 = D_800814D0 - 1;
            else
                D_800814D0 = 0x1F;
            func_8003F624();
        } else {
            CdControl(1, 0, 0);
        }
    }

tail:
    if ((D_80083164.unk0 & 0x7FFF) == 0)
        D_80083958.counter1 = 0;
    D_800814D0 = D_800814D0 & 0x1F;
}
