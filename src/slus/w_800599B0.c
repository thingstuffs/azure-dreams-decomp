#include "common.h"

typedef struct {
    /* 0x00 */ s32 f00;
    /* 0x04 */ s32 f04;
    /* 0x08 */ s8 pad08[8];
    /* 0x10 */ s32 f10;
    /* 0x14 */ s8 pad14[4];
    /* 0x18 */ s32 f18;
    /* 0x1C */ s32 f1C;
    /* 0x20 */ s32 f20;
    /* 0x24 */ s32 f24;
    /* 0x28 */ s8 pad28[4];
    /* 0x2C */ s32 f2C;
    /* 0x30 */ s8 pad30[8];
    /* 0x38 */ s32 f38;
    /* 0x3C */ s8 pad3C[4];
    /* 0x40 */ s32 f40;
    /* 0x44 */ s8 pad44[4];
    /* 0x48 */ u8 f48;
    /* 0x49 */ u8 f49;
    /* 0x4A */ u8 f4A;
    /* 0x4B */ s8 pad4B[5];
} Entity; /* 0x50 */

extern Entity D_80085FA8[];
extern s32 D_800869B4;
extern s32 D_800737C4;
extern s32 D_800737C8;
extern u8 *D_80085FA4;

extern void func_80058B70(void);
extern void func_800597A8(Entity *);
extern s32 func_80058A04(Entity *);
extern void func_80059814(Entity *);

s32 func_800599B0(void)
{
    u32 i;
    Entity *p;
    s32 off;
    s32 amt;
    u8 *q;
    u8 *qtmp;
    s32 amt2;
    register s32 v ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 sum;
    s32 k68a;
    s32 k68b;
    s32 c;
    s32 mode;

    D_800737C4 = 0;
    D_800737C8 = 1;
    off = 0;
    c = *D_80085FA4;
    if (c == 0x70) {
        D_800737C8 = 0;
    } else if (c == 0x4B) {
        D_800737C8 = 2;
    }
    func_80058B70();
    mode = D_800737C8;
    if (mode < 0) {
        goto ret0;
    }
    if (mode < 2) {
        goto lane01;
    }
    if (mode == 2) {
        goto lane2;
    }
    return 0;
lane01:
    {
        i = 0;
        if (D_800869B4 == 0) {
            goto ret0;
        }
        k68a = 0x68;
        p = D_80085FA8;
        do {
            if (D_800737C8 == 1) {
                p->f00 = off + 1;
                p->f24 = k68a;
                p->f20 = k68a;
                func_800597A8(p);
                off = p->f00;
            }
            p->f04 = p->f00;
            p->f10 = func_80058A04(p);
            p->f48 = 0;
            p->f4A = 0;
            p->f49 = 0;
            p->f2C = 0;
            p->f40 = 0;
            if (D_800737C4 != 0) {
                func_80059814(p);
            }
            p++;
            i++;
        } while (i < (u32)D_800869B4);
        goto ret0;
    }
lane2:
    off = 0x50;
    qtmp = D_80085FA4;
    i = 0;
    if (D_800869B4 == 0) {
        goto ret0;
    }
    k68b = 0x68;
    p = D_80085FA8;
    q = qtmp;
    do {
        p->f00 = off;
        amt = *(u16 *)(q + 0x10);
        p->f18 = amt;
        ASM_KEEP_NV(amt);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        amt2 = amt;
        ASM_KEEP_NV(amt2);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
        p->f24 = k68b;
        p->f20 = k68b;
        v = p->f00;
        sum = v;
        ASM_USE2_NV(sum, amt2);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        p->f04 = v;
        p->f38 = v;
        off += amt;
        sum += amt2;
        p->f1C = sum;
        p->f10 = func_80058A04(p);
        p->f48 = 0;
        p->f4A = 0;
        p->f49 = 0;
        p->f2C = 0;
        p->f40 = 0;
        if (D_800737C4 != 0) {
            func_80059814(p);
        }
        p++;
        q += 2;
        i++;
    } while (i < (u32)D_800869B4);
ret0:
    return 0;
}
