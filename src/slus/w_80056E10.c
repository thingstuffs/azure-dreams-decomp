#include "common.h"

/* D_80084960: per-request channel record, stride 0x9C */
typedef struct Chan {
    /* 0x00 */ u16 f00;
    u8 pad02[0x10 - 0x02];
    /* 0x10 */ s32 f10;
    u8 pad14[0x18 - 0x14];
    /* 0x18 */ u8 f18;
    u8 pad19[0x1C - 0x19];
    /* 0x1C */ s32 f1C;
    u8 pad20[0x28 - 0x20];
    /* 0x28 */ u32 f28;
    u8 pad2C[0x30 - 0x2C];
    /* 0x30 */ u8 f30;
    u8 pad31[0x3A - 0x31];
    /* 0x3A */ u16 f3A;
    u8 pad3C[0x50 - 0x3C];
    /* 0x50 */ s16 f50;
    /* 0x52 */ u16 f52;
    /* 0x54 */ s16 f54;
    /* 0x56 */ u16 f56;
    /* 0x58 */ s32 f58;
    /* 0x5C */ u8 f5C;
    /* 0x5D */ u8 f5D;
    u8 pad5E[0x68 - 0x5E];
    /* 0x68 */ s32 f68;
    /* 0x6C */ u8 f6C;
    /* 0x6D */ u8 f6D;
    /* 0x6E */ u8 f6E;
    u8 pad6F;
    /* 0x70 */ s32 f70;
    u8 pad74[0x78 - 0x74];
    /* 0x78 */ u8 f78;
    u8 pad79[0x84 - 0x79];
    /* 0x84 */ s32 f84;
    /* 0x88 */ u8 f88;
    /* 0x89 */ u8 f89;
    /* 0x8A */ u8 f8A;
    u8 pad8B;
    /* 0x8C */ s32 f8C;
    u8 pad90[0x98 - 0x90];
    /* 0x98 */ u8 f98;
    u8 pad99[0x9C - 0x99];
} Chan;

/* D_80085458: voice record, stride 0x78 */
typedef struct Voice {
    /* 0x00 */ s16 f00;
    u8 pad02[2];
    /* 0x04 */ u16 f04;
    /* 0x06 */ u16 f06;
    /* 0x08 */ u16 f08;
    /* 0x0A */ u16 f0A;
    /* 0x0C */ u16 f0C;
    u8 pad0E[2];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    /* 0x14 */ u8 f14;
    /* 0x15 */ u8 f15;
    /* 0x16 */ u8 f16;
    /* 0x17 */ u8 f17;
    u8 pad18[2];
    /* 0x1A */ u16 f1A;
    /* 0x1C */ u8 f1C;
    /* 0x1D */ u8 f1D;
    u8 pad1E[2];
    /* 0x20 */ u8 f20;
    /* 0x21 */ u8 f21;
    /* 0x22 */ u8 f22;
    /* 0x23 */ u8 f23;
    /* 0x24 */ u8 f24;
    u8 pad25;
    /* 0x26 */ u8 f26;
    /* 0x27 */ u8 f27;
    /* 0x28 */ u8 f28;
    u8 pad29[3];
    /* 0x2C */ s32 f2C;
    /* 0x30 */ s32 f30;
    /* 0x34 */ u8 f34;
    /* 0x35 */ u8 f35;
    /* 0x36 */ u8 f36;
    u8 pad37;
    /* 0x38 */ s32 f38;
    /* 0x3C */ u16 f3C;
    u8 pad3E[2];
    /* 0x40 */ u8 f40;
    u8 pad41;
    /* 0x42 */ u8 f42;
    /* 0x43 */ u8 f43;
    /* 0x44 */ u8 f44;
    u8 pad45[3];
    /* 0x48 */ s32 f48;
    /* 0x4C */ s32 f4C;
    /* 0x50 */ u8 f50;
    /* 0x51 */ u8 f51;
    /* 0x52 */ u8 f52;
    u8 pad53;
    /* 0x54 */ s32 f54;
    /* 0x58 */ s32 f58;
    u8 pad5C[4];
    /* 0x60 */ s32 f60;
    /* 0x64 */ s32 f64;
    /* 0x68 */ s32 f68;
    u8 pad6C[4];
    /* 0x70 */ s32 f70;
    /* 0x74 */ s32 f74;
} Voice;

/* D_80086A40: stride 0x1C */
typedef struct Slot {
    u8 pad00[4];
    /* 0x04 */ u8 *f04;
    u8 pad08[0x10 - 0x08];
    /* 0x10 */ s32 f10;
    u8 pad14[0x1C - 0x14];
} Slot;

/* event record, stride 0x20, at song + 0x820 */
typedef struct Ev {
    u8 pad00;
    /* 0x01 */ u8 f01;
    /* 0x02 */ u8 f02;
    /* 0x03 */ u8 f03;
    /* 0x04 */ u8 f04;
    /* 0x05 */ u8 f05;
    /* 0x06 */ u8 f06;
    /* 0x07 */ u8 f07;
    u8 pad08[4];
    /* 0x0C */ u8 f0C;
    /* 0x0D */ u8 f0D;
    u8 pad0E[2];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    u8 pad14[2];
    /* 0x16 */ s16 f16;
    u8 pad18[8];
} Ev;

typedef struct Hdr {
    /* 0x00 */ u8 f00;
    /* 0x01 */ u8 f01;
    u8 pad02[2];
    /* 0x04 */ u8 f04;
} Hdr;

typedef struct Song {
    u8 pad00[0x12];
    /* 0x12 */ u16 f12;
} Song;

typedef struct Req {
    /* 0x00 */ s32 f00;
    /* 0x04 */ s32 f04;
    /* 0x08 */ s16 f08;
    /* 0x0A */ s16 f0A;
    /* 0x0C */ s16 f0C;
    /* 0x0E */ s16 f0E;
    u8 pad10[6];
    /* 0x16 */ s16 f16;
    u8 pad18[4];
    /* 0x1C */ s32 f1C;
    u8 pad20[4];
    /* 0x24 */ s32 f24;
    u8 pad28[0x3A - 0x28];
    /* 0x3A */ u16 f3A;
    /* 0x3C */ u16 f3C;
} Req;

extern Chan D_80084960[16];
extern Voice D_80085458[64];
extern Slot D_80086A40[16];
extern s16 D_80086D50[8];
extern s32 D_80073740[];
extern s32 D_80073734[4];
extern s32 D_80073734_1[4] __asm__("D_80073734");
extern s32 D_80073734_2[4] __asm__("D_80073734");
extern s32 D_80073734_3[4] __asm__("D_80073734");
extern s32 D_80073734_4[4] __asm__("D_80073734");
extern s32 D_80073734_5[4] __asm__("D_80073734");
extern s32 D_80073734_6[4] __asm__("D_80073734");
extern s32 D_80073734_7[4] __asm__("D_80073734");
extern Req D_80084918;
extern s16 D_80084930;

extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 mode, s32 mask);
extern s32 func_8005EB78(s32 mask);
extern void func_80055E74(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_800561D8(Voice *a0, Chan *a1);
extern s32 func_800565D8(Voice *a0, s32 a1);
extern void func_8005E4A0(s32 a0, s32 a1);
extern s32 func_8005E78C(void);
extern void func_8005EC0C(Req *a0);

void func_80056E10(u8 arg0, s32 arg1, u8 arg2)
{
    u8 t17;
    u8 t24;
    s32 pad_[6];
    s32 a1c;
    u16 idx;
    s32 cnt;
    s32 lim;
    u16 nsub;
    u8 *buf;
    Song *song;
    Hdr *hdr;
    s32 held;
    u32 vel;
    u16 key;
    Chan *ch;
    Ev *ev;
    Voice *vp;
    u8 *p;
    u16 *hp;
    s32 fp;
    s16 j;
    s32 i;
    s32 acc;
    s16 n;
    s32 r;
    u32 prev;
    s32 fpt;
    s32 av;
    u32 keyx;
    u16 t10;
    u16 t12;

    a1c = arg1;
    cnt = 0;
    i = 0;
    ch = &D_80084960[arg0];
    song = (Song *)D_80086A40[D_80086D50[0]].f04;
    nsub = ch->f00;
    buf = (u8 *)song;
    if ((s32)nsub != 0) {
        lim = nsub;
        p = buf;
        do {
            if (p[0x20] != 0) {
                cnt++;
            }
            p += 0x10;
            i++;
        } while (i < lim);
    }
    hdr = (Hdr *)(buf + (nsub * 0x10 + 0x20));
    fp = (u8) a1c;
    idx = 0;
    if (hdr->f00 == 0) {
        return;
    }
    vel = a1c & 0xFF;
    key = arg0;
    do {
        ev = (Ev *)(buf + (((cnt * 0x10 + idx) << 5) + 0x820));
        held = 0;
        if ((vel >= ev->f06) && (ev->f07 >= vel)) {
            j = -1;
            if (ch->f98 != 0) {
                j = 0;
                while (1) {
                    if (key == D_80085458[j].f06) {
                        break;
                    }
                    if (++j >= D_80073734_1[0]) {
                        j = -1;
                        break;
                    }
                }
                if (j != -1) {
                    if (D_80085458[j].f1A == 0) {
                        func_80056DB4(j);
                        func_8005E97C(0, D_80073740[j]);
                    } else {
                        held = 1;
                    }
                } else {
                    j = 0;
                    while (1) {
                        if (func_8005EB78(D_80073740[j]) == 0) {
                            break;
                        }
                        if (++j >= D_80073734_2[0]) {
                            j = -1;
                            break;
                        }
                    }
                    if (j == -1) {
                        j = 0;
                        while (1) {
                            r = func_8005EB78(D_80073740[j]);
                            if (r == 2) {
                                break;
                            }
                            if (r == 0) {
                                break;
                            }
                            if (++j >= D_80073734_3[0]) {
                                j = -1;
                                break;
                            }
                        }
                    }
                }
                if (ch->f50 != 0) {
                    fpt = ch->f5C & 0x7F;
                    ASM_KEEP_NV(fpt);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    fp = (u8) fpt;
                    ASM_KEEP_NV(ch);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    prev = ch->f5C;
                    ch->f52 = 0;
                    if (prev < vel) {
                        ch->f56 = ((a1c & 0xFF) - ch->f5C) << 7;
                        ch->f58 = 1;
                        ch->f54 = (ch->f56 * 4) / ch->f50;
                    } else if (prev == vel) {
                        ch->f54 = 0;
                        fp = (u8) a1c;
                    } else {
                        ch->f56 = (ch->f5C - (a1c & 0xFF)) << 7;
                        ch->f58 = 0;
                        ch->f54 = (ch->f56 * 4) / ch->f50;
                    }
                } else {
                    ch->f52 = 0;
                }
            } else {
                if (ch->f50 != 0) {
                    fpt = ch->f5C & 0x7F;
                    ASM_KEEP_NV(fpt);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    fp = (u8) fpt;
                    ASM_KEEP_NV(ch);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                    prev = ch->f5C;
                    ch->f52 = 0;
                    if (prev < vel) {
                        ch->f56 = ((a1c & 0xFF) - ch->f5C) << 7;
                        ch->f58 = 1;
                        ch->f54 = (ch->f56 * 4) / ch->f50;
                    } else if (prev == vel) {
                        ch->f54 = 0;
                        fp = (u8) a1c;
                    } else {
                        ch->f56 = (ch->f5C - (a1c & 0xFF)) << 7;
                        ch->f58 = 0;
                        ch->f54 = (ch->f56 * 4) / ch->f50;
                    }
                } else {
                    ch->f52 = 0;
                }
            }
            if (j == -1) {
                j = 0;
                while (1) {
                    if (func_8005EB78(D_80073740[j]) == 0) {
                        break;
                    }
                    if (++j >= D_80073734_4[0]) {
                        j = -1;
                        break;
                    }
                }
                if (j == -1) {
                    j = 0;
                    while (1) {
                        r = func_8005EB78(D_80073740[j]);
                        if (r == 2) {
                            break;
                        }
                        if (r == 0) {
                            break;
                        }
                        if (++j >= D_80073734_5[0]) {
                            j = -1;
                            break;
                        }
                    }
                    if (j == -1) {
                        j = 0;
                        keyx = key;
                        av = a1c & 0xFF;
                        while (1) {
                            if ((keyx == D_80085458[j].f06) && (D_80085458[j].f0A == av)) {
                                break;
                            }
                            if (++j >= D_80073734_6[0]) {
                                j = -1;
                                break;
                            }
                        }
                        if (j == -1) {
                            j = 0;
                            while (1) {
                                if (D_80085458[j].f1A == 0) {
                                    break;
                                }
                                if (++j >= D_80073734_7[0]) {
                                    j = -1;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (j != -1) {
                vp = &D_80085458[j];
                if (ch->f98 == 0) {
                    func_80056DB4(j);
                    func_8005E97C(0, D_80073740[j]);
                    func_80055E74(j, a1c & 0xFF, arg0, D_80084918.f08, D_80084918.f0A);
                }
                i = 0;
                acc = 0;
                hp = (u16 *)((D_80086A40[D_80086D50[0]].f04 + (song->f12 << 9)) + 0x820);
                n = ev->f16;
                for (; i < n; i++) {
                    acc += *hp;
                    hp++;
                }
                D_80084918.f04 = 0x601EF;
                D_80084918.f0C = 0;
                D_80084918.f0E = 0;
                D_80084918.f00 = D_80073740[j];
                acc <<= 3;
                D_80084918.f1C = D_80086A40[D_80086D50[0]].f10 + acc;
                t10 = ev->f10;
                D_80084918.f3A = t10;
                vp->f60 = t10;
                t12 = ev->f12;
                D_80084918.f3C = t12;
                vp->f64 = t12;
                if (ev->f10 & 0x80) { D_80084918.f24 = 5; } else { D_80084918.f24 = 1; }
                vp->f68 = D_80084918.f24;
                ch->f5C = a1c;
                ch->f10 = arg2;
                vp->f22 = ev->f04;
                vp->f23 = ev->f05;
                vp->f21 = ev->f0C;
                vp->f20 = ev->f0D;
                vp->f00 = j;
                vp->f04 = nsub;
                vp->f08 = idx;
                vp->f0A = fp & 0x7F;
                vp->f0C = fp & 0x7F;
                vp->f06 = key;
                vp->f1A = 1;
                ch->f3A = 0;
                vp->f14 = hdr->f01;
                vp->f16 = hdr->f04;
                vp->f15 = ev->f02;
                t17 = ev->f03;
                vp->f1C = arg2;
                vp->f27 = 0;
                vp->f26 = 0;
                vp->f28 = 0;
                vp->f17 = t17;
                vp->f34 = ch->f6C;
                vp->f36 = ch->f6E;
                vp->f38 = ch->f70;
                vp->f30 = ch->f68;
                vp->f35 = ch->f6D;
                t24 = ch->f5D;
                vp->f2C = 0;
                *((s32 *) &vp->f3C) = 0;
                vp->f43 = 0;
                vp->f42 = 0;
                vp->f44 = 0;
                vp->f24 = t24;
                vp->f50 = ch->f88;
                vp->f52 = ch->f8A;
                vp->f54 = ch->f8C;
                vp->f4C = ch->f84;
                vp->f51 = ch->f89;
                vp->f40 = ch->f78;
                vp->f48 = 0;
                vp->f58 = 0;
                func_800561D8(&D_80085458[j], &D_80084960[arg0]);
                D_80084918.f08 = vp->f10;
                D_80084918.f0A = vp->f12;
                vp->f1D = ch->f18;
                vp->f0A = a1c & 0x7F;
                vp->f74 = ch->f1C;
                vp->f70 = -1;
                if (ch->f28 < 0x40) {
                    s32 u;
                    s16 t = vp->f3C + (ch->f3A + ch->f52);
                    t = t + ((vp->f0C << 7) + func_800565D8(vp, ch->f1C));
                    u = ((s32)(t << 16)) >> 23;
                    t = (t & 0x7F) + (u << 8);
                    D_80084918.f16 = t;
                } else {
                    ch->f1C = 0x40;
                    D_80084918.f16 = fp << 8;
                }
                if (ev->f05 != 0) {
                    D_80084930 = ((ev->f04 - 1) << 8) | (0x7F - ev->f05);
                } else {
                    D_80084930 = ev->f05 | (ev->f04 << 8);
                }
                if (held == 0) {
                    func_8005EC0C(&D_80084918);
                }
                if (ch->f30 == 0) {
                    if (ev->f01 & 4) {
                        do {
                            func_8005E4A0(1, D_80073740[j]);
                        } while (!(func_8005E78C() & D_80073740[j]));
                    } else {
                        do {
                            func_8005E4A0(0, D_80073740[j]);
                        } while (func_8005E78C() & D_80073740[j]);
                    }
                } else if (ch->f30 != 1) {
                    do {
                        func_8005E4A0(1, D_80073740[j]);
                    } while (!(func_8005E78C() & D_80073740[j]));
                } else {
                    do {
                        func_8005E4A0(0, D_80073740[j]);
                    } while (func_8005E78C() & D_80073740[j]);
                }
            }
        }
        idx++;
    } while (idx < hdr->f00);
    ASM_SET(a1c);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
}
