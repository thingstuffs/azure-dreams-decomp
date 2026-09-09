#include "common.h"

#define F(base, type, off) (*(type *)((char *)(base) + (off)))

extern void *D_800DF364[];
extern void *D_800E3D7C[];
extern s32 D_800814A0[];
extern s32 D_8008346C[];

extern void func_800A56E0(s32);
extern void func_800478B8(void *, void *, void *);

void func_800B96C4(void *p, void *out_arg, void *q_arg) {
    register void *out ASM_REG("$18") = out_arg;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register void *q ASM_REG("$17") = q_arg;   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    void *base;
    void *a1p;

    if (F(p, s16, 0xC) == 0) {
        void *v1 = F(F(p, void *, 0), void *, 0);
        if (v1 != 0) {
            if (D_800DF364[0] != v1) {
                func_800A56E0(0x507);
                F(p, s16, 0xE) = 4;
                D_800DF364[0] = F(F(p, void *, 0), void *, 0);
            }
        } else {
            void *t;
            u16 c;
            F(p, s16, 0xE) = 4;
            t = D_800E3D7C[0];
            c = F(p, u16, 0xC);
            D_800DF364[0] = t;
            F(p, u16, 0xC) = c + 1;
        }
        if (F(q, u16, 0x1C) < 0x1000) {
            u16 t = F(q, u16, 0x1E) + 0x200;
            F(q, u16, 0x1E) = t;
            F(q, u16, 0x1C) = t;
            if (t >= 0x1001) {
                F(q, u16, 0x1E) = 0x1000;
                F(q, u16, 0x1C) = 0x1000;
            }
        }
    } else {
        s16 e = F(p, s16, 0xE);
        if (e != 0) {
            u16 v = F(q, u16, 0x1E);
            u16 r = (u16)((s32)v - (s32)v / e);
            F(q, u16, 0x1E) = r;
            F(q, u16, 0x1C) = r;
        } else {
            F(q, u16, 0x1E) = 0;
            F(q, u16, 0x1C) = 0;
        }
    }

    {
        void *w1 = F(F(p, void *, 0), void *, 0);
        u32 dead;
        if (w1 == 0) {
            dead = 0x808080;
        } else {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            if (w1 == F(D_800E3D7C[0], void *, 0xAC)) {
                u32 dead2 = 0x101080;
                dead = dead2;
            } else {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                dead = 0x801010;
            }
        }
        F(q, s32, 0xC) = dead;
    }
    base = D_800DF364[0];
    a1p = F((char *)base - 0x18, void *, 0);
    if (F(p, s16, 0xE) != 0) {
        F(out, s32, 0) = F(out, s32, 0) + (F(a1p, s32, 0) - F(out, s32, 0)) / F(p, s16, 0xE);
        F(out, s32, 4) = F(out, s32, 4) + (F(a1p, s32, 4) - F(out, s32, 4)) / F(p, s16, 0xE);
        F(out, s32, 8) = F(out, s32, 8) + (((s32)(F(base, s16, 0x88) - F(out, s16, 0xA))) << 16) / F(p, s16, 0xE);
        {
            s16 dec = F(p, u16, 0xE) - 1;
            F(p, u16, 0xE) = dec;
            if (dec == 0) {
                if (F(p, s16, 0xC) == 0) {
                    F(out, u16, 2) = F(a1p, u16, 2);
                    F(out, u16, 6) = F(a1p, u16, 6);
                    F(out, u16, 0xA) = F(base, u16, 0x88);
                } else {
                    F(p, u16, -2) = F(p, u16, -2) | 0x8000;
                    D_8008346C[0] = 0;
                    D_800814A0[0] = D_800814A0[0] | 0x8000;
                }
            }
        }
    }
    F(q, u16, 0x1A) = F(q, u16, 0x1A) + 0x40;
    func_800478B8(q, a1p, base);
}

/* MECHANISM: Guarded s2/s1 argument pins produce the retail 0x28 frame and saved-register roles.
   Two merge-seam scheduling fences select the retail fall-through luis in the color-test slots.
   Split t/c live ranges plus global-before-halfword store order close the null-object block. */
