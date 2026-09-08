#include "common.h"

extern u8 *D_80083160;

typedef struct {} EmptyArg;

s32 func_800644B8(s32);
s32 func_80064584(s32);
void func_80064840(void *, void *, void *);
void func_800649A0(void);
void func_80064A40(void);
void func_80064AE0(void *);
void func_80064BC0(void *, void *);
void func_80064CF0(void *);
void func_80064D80(void *);
s32 func_80065590(void *, void *, void *, void *, void *,
                  void *, void *, void *, void *, void *, EmptyArg);
void func_80065820(void *, void *);
void func_800666F4(void *);

void func_80024758(void *arg0, void *arg1, void *arg2, u16 arg3) {
    s32 sp28[8];
    u16 sp48;
    u8 *sp50;
    s32 sp54;
    s32 sp58;
    register u8 *scratch ASM_REG("$21") = (u8 *)0x1F800000;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *page;
    u8 *page0;
    u32 page_color;
    u8 **pp;
    u8 *node;
    s32 lim_a1;
    s32 lim_a0;
    s32 negE;
    s32 quo;
    s32 quo2;
    s32 off;
    s32 vs0;
    s32 vs1;
    s32 vs3;
    s32 vs4;
    s32 vs6;
    s32 vs7;
    s32 tv0;
    s32 tv1;
    s32 tmpm;
    s32 c1;
    s32 c2;
    s32 c3;
    s32 c4;
    s32 c5;
    s32 tprod;
    u8 flg;
    u8 nflg;

    page0 = D_80083160;
    ASM_KEEP_MEMDEP(page0, page_color, D_80083160);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    *(u8 **)(scratch + 0x24) = page0 + 0xB0;
    *(s32 *)(scratch + 0x88) = *(s16 *)((u8 *)arg1 + 2);
    *(s32 *)(scratch + 0x8C) = *(s16 *)((u8 *)arg1 + 6);
    *(s32 *)(scratch + 0x90) = *(s16 *)((u8 *)arg1 + 0xA);
    *(u16 *)((u8 *)arg2 + 0x14) = *(u16 *)((u8 *)arg2 + 0x14) | 0x8000;
    sp48 = arg3;
    func_800649A0();
    *(s32 *)(scratch + 0x3C) = 0x2000;
    *(s32 *)(scratch + 0x38) = 0x2000;
    *(s32 *)(scratch + 0x34) = 0x2000;
    *(u16 *)(scratch + 0xA4) = *(u16 *)((u8 *)arg2 + 0x16);
    *(u16 *)(scratch + 0xA8) = *(u16 *)((u8 *)arg2 + 0x1A);
    *(u16 *)(scratch + 0xA6) = *(u16 *)((u8 *)arg2 + 0x18);
    func_80065820((u8 *)((u32)scratch | 0xA4), (u8 *)((u32)scratch | 0x74));
    func_80064AE0(&sp28[0]);
    func_80064840(&sp28[0], (u8 *)((u32)scratch | 0x74), (u8 *)((u32)scratch | 0x54));
    func_80064BC0((u8 *)((u32)scratch | 0x54), (u8 *)((u32)scratch | 0x34));
    func_80064D80((u8 *)((u32)scratch | 0x54));
    func_80064CF0((u8 *)((u32)scratch | 0x54));
    ASM_KEEP_NV(scratch);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    sp50 = *(u8 **)((u8 *)arg2 + 8);
    *(u16 *)(scratch + 0x28) = *(u16 *)((u8 *)arg2 + 0x14);
    for (;;) {
        for (sp58 = 0; sp58 < *(s16 *)((u8 *)arg0 + 0xC); sp58++) {
            pp = &D_80083160;
            for (sp54 = 0; sp54 < *(s16 *)((u8 *)arg0 + 0xA); sp54++) {
                *(s32 *)(scratch + 0x0C) = *(u8 *)(sp50 + 8);
                *(s32 *)(scratch + 0x10) = *(u8 *)(sp50 + 9);
                *(s32 *)(scratch + 0x14) = *(u8 *)(sp50 + 10);
                page = *pp;
                *(s32 *)(scratch + 0x18) = *(u8 *)(sp50 + 11);
                node = *(u8 **)(page + 0x8D0);
                *(u8 **)(page + 0x8D0) = node + 0x28;
                lim_a1 = *(s16 *)((u8 *)arg0 + 0xA);
                vs3 = (sp54 << 0xC) / lim_a1;
                negE = -*(s16 *)((u8 *)arg0 + 0xE);
                lim_a0 = *(s16 *)((u8 *)arg0 + 0xC);
                quo = (negE * sp58) / lim_a0;
                quo2 = (negE * (sp58 + 1)) / lim_a0;
                off = *(s16 *)((u8 *)arg0 + 0x10);
                vs4 = ((sp54 + 1) << 0xC) / lim_a1;
                vs3 = vs3 + off;
                vs6 = quo + 0x400;
                vs7 = quo2 + 0x400;
                if (vs3 >= 0x1001) {
                    vs3 -= 0x1000;
                }
                if (vs3 < 0) {
                    vs3 += 0x1000;
                }
                vs4 = vs4 + off;
                if (vs4 >= 0x1001) {
                    vs4 -= 0x1000;
                }
                if (vs4 < 0) {
                    vs4 += 0x1000;
                }
                vs0 = ((*(s32 *)((u8 *)arg0 + 0x68) >> 8) * func_80064584(vs6)) >> 0x14;
                vs1 = ((*(s32 *)((u8 *)arg0 + 0x68) >> 8) * func_80064584(vs7)) >> 0x14;
                *(s16 *)(scratch + 0xB0) = (vs0 * func_800644B8(vs3)) >> 0xC;
                *(s16 *)(scratch + 0xB2) = (vs0 * func_80064584(vs3)) >> 0xC;
                *(s16 *)(scratch + 0xB4) = -(((*(s32 *)((u8 *)arg0 + 0x68) >> 8) * func_800644B8(vs6)) >> 0x14);
                *(s16 *)(scratch + 0xB8) = (vs0 * func_800644B8(vs4)) >> 0xC;
                *(s16 *)(scratch + 0xBA) = (vs0 * func_80064584(vs4)) >> 0xC;
                *(s16 *)(scratch + 0xBC) = -(((*(s32 *)((u8 *)arg0 + 0x68) >> 8) * func_800644B8(vs6)) >> 0x14);
                *(s16 *)(scratch + 0xC0) = (vs1 * func_800644B8(vs3)) >> 0xC;
                *(s16 *)(scratch + 0xC2) = (vs1 * func_80064584(vs3)) >> 0xC;
                *(s16 *)(scratch + 0xC4) = -(((*(s32 *)((u8 *)arg0 + 0x68) >> 8) * func_800644B8(vs7)) >> 0x14);
                *(s16 *)(scratch + 0xC8) = (vs1 * func_800644B8(vs4)) >> 0xC;
                *(s16 *)(scratch + 0xCA) = (vs1 * func_80064584(vs4)) >> 0xC;
                tprod = -(((*(s32 *)((u8 *)arg0 + 0x68) >> 8) * func_800644B8(vs7)) >> 0x14);
                tv0 = (func_80065590(scratch + 0xB0, scratch + 0xB8, scratch + 0xC0, scratch + 0xC8, node + 8, node + 0x10, node + 0x18, node + 0x20, scratch + 0xD0, (void *)(scratch + 0xD4),
                       ({
                           EmptyArg empty;
                           *(s16 *)(scratch + 0xCC) = tprod;
                           empty;
                       })) - (s16)sp48) - 6;
                *(s32 *)(scratch + 0x100) = tv0;
                if ((u32)tv0 < 0x1E0U) {
                    c1 = 0;
                    if ((u32)((*(u16 *)(node + 8) + 0x20) & 0xFFFF) < 0x181U) {
                        tmpm = *(u16 *)(node + 0xA) + 0x20;
                        tmpm = tmpm & 0xFFFF;
                        c1 = (u32)tmpm < 0x121U;
                    }
                    c2 = 0;
                    if ((u32)((*(u16 *)(node + 0x10) + 0x20) & 0xFFFF) < 0x181U) {
                        tmpm = *(u16 *)(node + 0x12) + 0x20;
                        tmpm = tmpm & 0xFFFF;
                        c2 = (u32)tmpm < 0x121U;
                    }
                    c3 = 0;
                    c1 = c1 | c2;
                    if ((u32)((*(u16 *)(node + 0x18) + 0x20) & 0xFFFF) < 0x181U) {
                        tmpm = *(u16 *)(node + 0x1A) + 0x20;
                        tmpm = tmpm & 0xFFFF;
                        c3 = (u32)tmpm < 0x121U;
                    }
                    c4 = 0;
                    c5 = c1 | c3;
                    if ((u32)((*(u16 *)(node + 0x20) + 0x20) & 0xFFFF) < 0x181U) {
                        tmpm = *(u16 *)(node + 0x22) + 0x20;
                        tmpm = tmpm & 0xFFFF;
                        c4 = (u32)tmpm < 0x121U;
                    }
                    if ((c5 | c4) != 0) {
                        *(u16 *)((u8 *)arg2 + 0x14) = *(u16 *)((u8 *)arg2 + 0x14) & 0x7FFF;
                        func_800666F4(node);
                        tv1 = *(s32 *)(scratch + 0x14) + *(s32 *)(scratch + 0x0C);
                        *(s32 *)(scratch + 0x14) = tv1;
                        if (tv1 & 0x100) {
                            *(s32 *)(scratch + 0x14) = tv1 - 1;
                        }
                        tv1 = *(s32 *)(scratch + 0x18) + *(s32 *)(scratch + 0x10);
                        *(s32 *)(scratch + 0x18) = tv1;
                        if (tv1 & 0x100) {
                            *(s32 *)(scratch + 0x18) = tv1 - 1;
                        }
                        *(s32 *)(scratch + 0x10) = *(s32 *)(scratch + 0x10) << 8;
                        *(s32 *)(scratch + 0x18) = *(s32 *)(scratch + 0x18) << 8;
                        tv1 = *(u16 *)((u8 *)arg2 + 0x12);
                        if (tv1 != 0) {
                            if (*(u16 *)(scratch + 0x28) & 0x100) {
                                *(u16 *)(node + 0xE) = tv1;
                                goto L_B;
                            }
                            tv0 = tv1 + *(u16 *)(sp50 + 6);
                            goto L_A;
                        }
                        tv0 = *(u16 *)(sp50 + 6);
                    L_A:
                        *(u16 *)(node + 0xE) = tv0;
                    L_B:
                        *(s16 *)(node + 0xC) = *(u16 *)(scratch + 0x10) + *(u16 *)(scratch + 0x0C);
                        *(s16 *)(node + 0x14) = *(u16 *)(scratch + 0x10) + *(u16 *)(scratch + 0x14);
                        tv1 = *(u16 *)((u8 *)arg2 + 0x10);
                        if (tv1 != 0) {
                            tv0 = tv1 + (*(u16 *)(sp50 + 4) & 0xFF9F);
                            goto L_C;
                        }
                        tv0 = *(u16 *)(sp50 + 4);
                    L_C:
                        *(u16 *)(node + 0x16) = tv0;
                        *(s16 *)(node + 0x1C) = *(u16 *)(scratch + 0x18) + *(u16 *)(scratch + 0x0C);
                        *(s16 *)(node + 0x24) = *(u16 *)(scratch + 0x18) + *(u16 *)(scratch + 0x14);
                        if (*(s16 *)(node + 8) > *(s16 *)(node + 0x20)) {
                            *(u8 *)(node + 0x14) = *(u8 *)(node + 0x14) - 1;
                            *(u8 *)(node + 0x24) = *(u8 *)(node + 0x24) - 1;
                        }
                        if (*(s16 *)(node + 0xA) > *(s16 *)(node + 0x22)) {
                            *(u8 *)(node + 0x1D) = *(u8 *)(node + 0x1D) - 1;
                            *(u8 *)(node + 0x25) = *(u8 *)(node + 0x25) - 1;
                        }
                        flg = *(u8 *)(sp50 + 1);
                        *(u8 *)((u8 *)arg2 + 0xF) = flg;
                        tv1 = *(u16 *)(scratch + 0x28);
                        if (tv1 & 8) {
                            if (tv1 & 4) {
                                nflg = flg | 2;
                                *(u8 *)((u8 *)arg2 + 0xF) = nflg;
                            } else {
                                nflg = flg & 0xFD;
                                *(u8 *)((u8 *)arg2 + 0xF) = nflg;
                            }
                        }
                        {
                            register u32 mask ASM_REG("$4") = 0x00FFFFFF;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                            register u32 mask2 ASM_REG("$5") = 0xFF000000;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                            s32 *slot;
                            *(s32 *)(node + 4) = *(s32 *)((u8 *)arg2 + 0xC);
                            *(s32 *)node = (*(s32 *)node & mask2)
                                | (*(s32 *)((*(s32 *)(scratch + 0x100) * 4) + *(s32 *)(scratch + 0x24)) & mask);
                            slot = (s32 *)((*(s32 *)(scratch + 0x100) * 4) + *(s32 *)(scratch + 0x24));
                            *slot = (*slot & mask2) | ((s32)node & mask);
                        }
                    }
                }
            }
        }
        if (*(s8 *)sp50 < 0) {
            break;
        }
        sp50 += 12;
    }
    func_80064A40();
}
