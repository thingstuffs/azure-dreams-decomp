#include "common.h"

extern u8 D_80081468[];
extern u16 D_8008146C;
extern u32 D_800814A0;
extern u8 D_80082E6B;
extern u8 D_80083160[];
extern u8 D_80083460[];
extern s16 D_800DCED4[];
extern u8 D_800DCF4F;
extern u8 D_800E0458[];
extern u8 D_800E0B65[];
extern u8 D_800E0B73[];
extern u8 D_800E0BA1[];
extern u32 D_800E296C;
extern u8 D_800E2970[];
extern u8 *D_800E3D7C;

void func_800419EC();
void func_80040AA0();
s32 func_800429E4();
void func_800481E0();
void func_800945E8();
void func_800948BC();
s32 func_800990FC();
s32 func_80099194();
s32 func_80099254();
void func_80099290();
s32 func_8009929C();
void func_8009A028();
void func_8009A3D0();
void func_8009D6F4();
s32 func_8009FBF0();
void func_800A32A4();
void func_800A56E0();
void func_800A5720();
void func_800A6780();
s32 func_800A6D30();
void func_800A7030(s16, s16);
void func_800B6008(s16, s16);
void func_800C1F28();
void func_800C542C();

#define CELL(xx, yy) (cells + 6 * ((xx) + ((yy) << *(s16 *)(fld + 20))))

void func_800C5FA8(u8 *w) {
    u8 *ctx;
    u8 *cells;
    u8 *fld;
    s32 st;
    u8 *sys;
    u8 *room;
    u8 *cnt;
    u8 *cnt2;
    u8 *rooms;
    u8 *rbase;
    u8 *rm;
    u8 *e;
    u8 *ep;
    u8 *o;
    u8 *q;
    u8 *p;
    u8 *st2;
    u8 *st3;
    s16 *tbl;
    s32 phase0;
    s32 phase;
    s32 hnd;
    s32 r;
    s32 v;
    s32 x, y, x1, y1, k;
    s32 t16;
    s32 mode;
    register s32 t ASM_REG("$2");
    s32 rv;
    s32 cc;
    s32 ic;
    s32 ea;
    s32 eb;
    s32 ch;
    u16 f;
    u16 a;

    ctx = D_80083160;
    phase0 = *(s16 *)w;
    cells = *(u8 **)(ctx + 0x1DC);
    fld = ctx + 0x1DC;
    if (phase0 == 0) {
        st = (s32) D_80083460;
        f = *(u16 *)((u8 *) st + 2);
        if (f & 0x10) {
            *(u16 *)((u8 *) st + 2) = f | 0x200;
        }
        a = *(u16 *)((u8 *) st + 2);
        if (!(a & 0x200)) {
            return;
        }
        if ((*(u32 *)(ctx + 8) & 0x800) && !(*(u16 *)0x80013714 & 8)) {
            return;
        }
        if (*(s32 *)((u8 *) st + 12) != 0) {
            return;
        }
        if (*(s32 *)((u8 *) st + 16) != 0) {
            return;
        }
        if (a & 8) {
            return;
        }
        if (*(s16 *)((u8 *) st + 8) != 0) {
            return;
        }
        if (*(s16 *)((u8 *) st + 20) != 0) {
            return;
        }
        if (D_800E296C & 0x100000) {
            return;
        }
        if (*(s16 *)((u8 *) st + 10) != 0) {
            return;
        }
        if (a & 0x2C01) {
            return;
        }
        *(u16 *)((u8 *) st + 2) = a & 0xFDFF;
        if (*(s16 *)(w + 22) != 0) {
            *(u16 *)(w + 22) = *(u16 *)(w + 22) - 1;
            return;
        }
        func_800A56E0(0x818);
        func_800419EC(0x20, 8);
        *(u16 *)(w + 20) = *(u16 *)(w + 20) + 1;
        sys = (u8 *)0x80010000;
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            ic = *(u16 *)((u8 *) st + 10);
            D_800DCF4F = 1;
            *(u16 *)((u8 *) st + 10) = ic + 1;
        }
        phase = 1;
        hnd = func_800990FC();
        v = *(s16 *)(w + 20);
        if (v == phase) {
            r = func_80099194(D_800E0B65, hnd);
            if (!(*(u16 *)(sys + 0x3714) & 1)) {
                r = func_8009929C(0x11, r);
                r = func_8009929C(0x4C, r);
                r = func_80099254(D_800E0458, r);
            }
            func_80099290(r);
            func_800A5720(hnd);
            *(s16 *)(w + 22) = 0x80;
            return;
        }
        if (v != 2) {
            goto L_third;
        }
        r = func_80099194(D_800E0B73, hnd);
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            r = func_8009929C(0x11, r);
            r = func_8009929C(0x4C, r);
            r = func_80099254(D_800E0458, r);
        }
        func_80099290(r);
        func_800A5720(hnd);
        *(s16 *)(w + 22) = 0x40;
        return;
    L_found:
        *(s16 *)(w + 6) = phase;
        t = *(u16 *)(room + 0);
        t = t - 1;
        *(s16 *)(w + 8) = t;
        *(s16 *)(w + 12) = t + *(u16 *)(room + 4) + 2;
        t = *(u16 *)(room + 2);
        t = t - 1;
        *(s16 *)(w + 10) = t;
        *(s16 *)(w + 14) = t + *(u16 *)(room + 6) + 2;
        goto L_zero;
    L_third:
        r = func_80099194(D_800E0BA1, hnd);
        *(s16 *)(w + 22) = 0;
        if (!(*(u16 *)(sys + 0x3714) & 1)) {
            r = func_8009929C(0x11, r);
            r = func_8009929C(0x4C, r);
            r = func_80099254(D_800E0458, r);
        }
        func_80099290(r);
        func_800A5720(hnd);
        *(s16 *)w = phase;
        *(u16 *)((u8 *) st + 10) = *(u16 *)((u8 *) st + 10) + 1;
        *(u16 *)(w + 4) = *(u16 *)(w + 4) + 1;
        rv = func_800A6D30() & 0xFFFF;
        cnt = D_80081468;
        cc = *(s16 *)(cnt + 6);
        ASM_KEEP_NV(cc);
        st = cc;
        phase = rv % st;
        if (st > 0) {
            rbase = D_800E2970;
            cnt2 = cnt;
            do {
                room = (u8 *)(phase * 20 + (s32)rbase);
                if (*(s16 *)(room + 10) != 0) {
                    goto L_found;
                }
                st = st - 1;
                phase = (phase + 1) % *(s16 *)(cnt2 + 6);
            } while (st > 0);
        }
    L_zero:
        if (st == 0) {
            *(s16 *)(w + 6) = -1;
        }
    L_after:
        v = *(s16 *)(w + 6);
        *(s16 *)(w + 2) = 0x20;
        *(s16 *)(w + 16) = 1;
        *(s16 *)(w + 4) = 1;
        if (v >= 0) {
            x = *(s16 *)(w + 8);
            x1 = *(s16 *)(w + 12);
            y1 = *(s16 *)(w + 14);
            if (x < x1) {
                do {
                    y = *(s16 *)(w + 10);
                    if (y < y1) {
                        do {
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            func_800B6008(x, y);
                            func_800A7030(x, y);
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                } while (x < x1);
            }
        } else {
            x = 1;
            y1 = x1 = 63;
            do {
                y = 1;
                if (y < y1) {
                    do {
                        *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                        *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                        func_800B6008(x, y);
                        func_800A7030(x, y);
                        y = y + 1;
                    } while (y < y1);
                }
                x = x + 1;
            } while (x < x1);
        }
        tbl = D_800DCED4;
        phase = *(s16 *)(w + 6);
        e = D_800E3D7C;
        *(s16 *)(w + 18) = 0;
        do {
            ep = *(u8 **)(e - 20);
            if (phase == (s16)func_8009FBF0(*(u8 *)(ep + 36), *(u8 *)(ep + 37))) {
                if (*(u8 *)(e + 19) == 0) {
                    D_800E296C |= 0x2000;
                    func_800C542C(e, tbl[func_800429E4(e)], 0, 0);
                    p = D_800E3D7C;
                    q = *(u8 **)(p + 172);
                    if (q != 0) {
                        func_800C542C(q, tbl[func_800429E4(q)], 0, 0);
                    }
                    {
                        u8 *p2 = D_800E3D7C;
                        q = *(u8 **)(p2 + 176);
                    }
                    if (q != 0) {
                        func_800C542C(q, tbl[func_800429E4(q)], 1, 0);
                    }
                    *(s16 *)(w + 18) = 1;
                } else if (*(u32 *)(e + 20) & 0x4000) {
                    if (*(s16 *)(w + 18) == 0) {
                        func_800C1F28(e, *(u8 **)(D_800E3D7C + 172) != e);
                    }
                } else {
                    if (*(s16 *)(w + 18) != 0) {
                        *(s16 *)(e + 108) = 0;
                    }
                    o = e;
                    ea = *(u8 *)(ep + 36);
                    eb = *(u8 *)(ep + 37);
                    mode = 0x3000;
                    e = *(u8 **)(o + 88) + 32;
                    if (*(u32 *)(o + 28) & 0x2000) {
                        mode = 0x300;
                    }
                    func_8009A3D0(ea, eb, mode);
                    if ((*(u32 *)(o + 20) & 0x20000000) && *(u8 *)(o + 19) == 30) {
                        st2 = D_80083460;
                        *(u16 *)(st2 + 10) = *(u16 *)(st2 + 10) + 1;
                    }
                    func_800A32A4(o);
                    func_8009A028(o);
                    *(u16 *)(o - 2) |= 0x8000;
                    D_800814A0 |= 0x8000;
                }
            }
            e = *(u8 **)(e + 92) + 32;
        } while (e != D_800E3D7C);
        if (phase < 0) {
            return;
        }
        rooms = D_800E2970;
        rm = rooms + phase * 20;
        *(s16 *)(rm + 10) = 0;
        return;
    }
    if (phase0 == 1) {
        if (*(s16 *)(w + 6) >= 0) {
            x = *(s16 *)(w + 8);
            x1 = *(s16 *)(w + 12);
            y1 = *(s16 *)(w + 14);
            k = 0;
            if (*(s16 *)(w + 4) > 0) {
                do {
                    y = *(s16 *)(w + 10);
                    if (y < y1) {
                        do {
                            s32 mul8 = 8 - (func_800A6D30() & 7);
                            s32 dec = *(s16 *)(w + 4) - 1;
                            *(u16 *)(CELL(x, y) + 2) -= mul8 * (dec - k);
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                    if (x >= x1) {
                        goto L_tail;
                    }
                    k = k + 1;
                } while (k < *(s16 *)(w + 4));
            }
        } else {
            x = 1;
            y1 = x1 = 63;
            k = 0;
            if (*(s16 *)(w + 4) > 0) {
                do {
                    y = 1;
                    if (y < y1) {
                        do {
                            s32 mul8 = 8 - (func_800A6D30() & 7);
                            s32 dec = *(s16 *)(w + 4) - 1;
                            *(u16 *)(CELL(x, y) + 2) -= mul8 * (dec - k);
                            *(u16 *)(CELL(x, y) + 4) &= 0xFF73;
                            *(u16 *)(CELL(x, y) + 4) |= 0x8000;
                            y = y + 1;
                        } while (y < y1);
                    }
                    x = x + 1;
                    if (x >= x1) {
                        goto L_tail;
                    }
                    k = k + 1;
                } while (k < *(s16 *)(w + 4));
            }
        }
    L_tail:
        t16 = *(u16 *)(w + 16) - 1;
        *(u16 *)(w + 16) = t16;
        if ((s16) t16 > 0) {
            return;
        }
        *(s16 *)(w + 16) = 1;
        *(u16 *)(w + 4) = *(u16 *)(w + 4) + 1;
        func_8009D6F4();
        if (!((x1 + 16) < *(s16 *)(w + 4))) {
            return;
        }
        if (*(s16 *)(w + 18) == 0) {
            st3 = D_80083460;
            *(s16 *)w = 0;
            *(u16 *)(st3 + 10) = *(u16 *)(st3 + 10) - 1;
            return;
        }
        *(u32 *)(ctx + 204) = 0;
        *(u32 *)(ctx + 340) = 0;
        *(u16 *)w = *(u16 *)w + 1;
        return;
    }
    o = (u8 *)0x80010000;
    if (*(u16 *)(o + 0x3714) & 4) {
        func_80040AA0(3);
        return;
    }
    func_800945E8(D_800E3D7C);
    func_800948BC();
    func_800A6780();
    t = *(u32 *)(o + 0x234);
    ch = D_80082E6B;
    t = t + 1;
    *(u32 *)(o + 0x234) = t;
    D_8008146C = *(u16 *)(o + 0x234);
    func_80040AA0(ch);
    func_800481E0();
    *(u16 *)(w - 2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
