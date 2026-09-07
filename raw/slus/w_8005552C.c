#include "common.h"

#include "common.h"

extern s32 func_8005405C(s32 n);
extern void func_8005560C(s32 a0, s32 a1);
extern void func_80055730(s32 a0, s32 a1);

/* Dispatch on (arg0 & 0xF00): 0x600→2, 0x000–0x500→1, 0x700→3, 0x800→0,
   else→1; then func_8005405C and optional func_80055730/func_8005560C. */
void func_8005552C(s32 arg0) {
    /* Pin keeps andi a0,a0 (not CSE-from-s1) and value temps in $v0. */
    register s32 t ASM_REG("$4") = arg0;
    register s32 v ASM_REG("$2");
    s32 s1;
    s32 code;
    s32 pa0;
    s32 pa1;

    s1 = t;
    t = t & 0xF00;
    if (t == 0x600) {
        goto case_600;
    }
    if (t < 0x601) {
        v = 1;
        goto merge;
    }
    if (t == 0x700) {
        goto case_700;
    }
    if (t == 0x800) {
        goto case_800;
    }
    /* default: v→code then jump past merge (delay-slot duplicate of merge) */
    v = 1;
    goto setcode_after;
case_600:
    v = 2;
    goto merge;
case_700:
    v = 3;
    goto merge;
case_800:
    v = 0;
merge:
    code = v;
    goto after;
setcode_after:
    code = v;
after:
    if ((func_8005405C(code) << 0x10) != 0) {
        pa0 = (code << 8) | ((u32)(s1 & 0xFF) >> 4);
        pa1 = ((s1 & 0xF) << 0xA) + 0x1C00;
        if (code == 0) {
            pa0 += 0x10;
        }
        if (s1 & 0x1000) {
            func_80055730(pa0, pa1);
            return;
        }
        func_8005560C(pa0, pa1);
    }
}
