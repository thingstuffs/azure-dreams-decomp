#include "common.h"

extern void *D_8002014C[5];
extern u8 D_80026F80[];
extern u8 D_800F7968[16];
extern u8 D_800F79E8[16];
extern s32 D_800814A0;

extern s32 rand(void);
extern void func_800478B8(void *);
extern void func_8003DB94(void *, void *, s32);
extern void func_800252B8(s32, s32, s32, s32);
extern void func_800253BC(void *, s32, s32);
extern void func_80026CE4(s32);
extern void func_8008F134(void *);

typedef struct B {
    u8 pad0[0x10];
    s16 field10;
    u8 pad12[0x18 - 0x12];
    s16 field18;
    u16 field1a;
} B;

typedef struct A {
    B *unk0;
    u8 pad4[0x50 - 0x04];
    s16 state;
    u16 timer;
    u8 pad54[2];
    s16 field56;
    u16 flags;
} A;

typedef struct C {
    s32 w0;
    s32 w4;
    s32 w8;
    u8 pad0c[0x14 - 0x0c];
    s32 w20;
} C;

typedef struct D {
    void *unk0;
    u8 pad4[0x0c - 0x04];
    union { u8 b; s32 w; } f0c;
    u8 pad10[0x14 - 0x10];
    u16 h14;
} D;

typedef struct Local {
    void *p;
    s32 a;
    s32 b;
    s16 c;
    u16 d;
    s16 e;
} Local;

void func_8002582C(A *e, C *c, D *o) {
    B *b = e->unk0;
    s32 t;
    s32 st;
    s32 n;
    s32 r;
    s32 x;
    static void *const keepalive[5] = { &&L0, &&L1, &&L2, &&L3, &&L4 };

    if (e->flags & 2) {
        if (o->f0c.b) {
            o->f0c.w += 0xfffefeff;
        }
    }

    t = b->field1a;
    b->field1a = t | 2;
    if (e->flags & 1) {
        b->field1a = t | 6;
    }

    func_800478B8(o);
    if (e->flags & 4) {
        if (o->unk0 == (void *)D_800F7968) {
            func_8003DB94(o, D_800F79E8, 0);
        }
    }
    if (o->h14 & 0x6000) {
        func_8003DB94(o, D_800F7968, 0);
    }

    st = e->state;
    if ((u32)st >= 5U) {
        goto END;
    }
    goto *D_8002014C[st];

L0:
    if (c->w8 > 0) {
        c->w8 += c->w20;
        n = 3;
        for (;;) {
            r = rand();
            x = c->w0;
            x += ((r & 0xff) - 128) << 14;
            r = rand();
            func_800252B8(0x808080, x, c->w4 + 0x80000, (r & 0xf) << 16);
            if (--n < 0) {
                goto END;
            }
        }
    }
    c->w8 = 0;
    c->w20 = 0;
    e->state = 1;
    goto END;

L1:
    if (b->field1a & 1) {
        Local lo;
        u8 *elem = D_80026F80 + b->field18 * 400 + b->field10 * 40 + (e->field56 * 12 + 4);
        lo.d = *(u16 *)(elem + 8);
        lo.a = *(s32 *)(elem + 0);
        lo.b = *(s32 *)(elem + 4);
        lo.c = 0;
        lo.e = 0;
        lo.p = e;
        func_800253BC(&lo, c->w4, 0);
    }
    goto END;

L2:
    {
        s32 nt = e->timer - 1;
        e->timer = nt;
        if ((s16)nt <= 0) {
            if (e->field56 == 0) {
                func_80026CE4(90);
            }
            c->w20 = 0x40000;
            e->state = 3;
        }
    }
    goto END;

L3:
    if (c->w8 > 0x7fffff) {
        goto L3_over;
    }
    {
        s32 nv = c->w8 + c->w20;
        c->w8 = nv;
        if (nv <= 0x3fffff) {
            n = 3;
            for (;;) {
                r = rand();
                x = r & 0xff;
                x -= 128;
                x <<= 14;
                x += 0x5600000;
                r = rand();
                func_800252B8(0x808080, x, c->w4 + 0x80000, (r & 0xf) << 16);
                if (--n < 0) {
                    goto END;
                }
            }
        }
    }
    goto END;

L3_over:
    e->timer = 2;
    e->state = 4;
    goto END;

L4:
    {
        s32 nt = e->timer - 1;
        e->timer = nt;
        if ((s16)nt <= 0) {
            func_8008F134((u8 *)e + 4);
            *(u16 *)((u8 *)e - 2) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }

END:
    e->flags &= ~2;
}
