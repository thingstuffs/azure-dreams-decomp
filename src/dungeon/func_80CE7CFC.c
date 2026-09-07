#include "common.h"


typedef struct { s32 w0, w1, w2, w3; } Blk16;

extern void *func_8003FD64();
extern s32 func_8003DE58();
extern void func_8004491C();
extern void func_80047784();

extern s16 D_80083228;
extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800DDC40[];
extern u8 D_80170DC4[];
extern u8 D_80175EB4[];
extern u8 D_80175EBC[];


typedef struct S_801714FC_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x12];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    union { s32 i; void * p; } unk_60;   /* accessed as both */
    u8 pad_64[0xE];
    union { s8 s; u8 u; } unk_72;   /* accessed as both */
    union { s8 s; u8 u; } unk_73;   /* accessed as both */
} S_801714FC_0;   /* arg3 in func_801714FC */

typedef struct S_801714FC_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
} S_801714FC_1;   /* v1 in func_801714FC */

typedef struct S_801714FC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_801714FC_2;   /* s2 in func_801714FC */

typedef struct S_801714FC_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801714FC_3;   /* s0v in func_801714FC */

typedef struct S_801714FC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801714FC_4;   /* q in func_801714FC */

typedef struct S_801714FC_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801714FC_5;   /* arg1 in func_801714FC */

typedef struct S_801714FC_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801714FC_6_pre;   /* the 0x14 bytes before arg0 in func_801714FC, addressed as arg0[-1] */

typedef struct S_801714FC_7 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_801714FC_7;   /* r in func_801714FC */

typedef struct S_801714FC_8_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_801714FC_8_pre;   /* the 0x18 bytes before ((S_801714FC_0 *)arg3)->unk_60.p in func_801714FC, addressed as ((S_801714FC_0 *)arg3)->unk_60.p[-1] */

typedef struct S_801714FC_8 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_801714FC_8;   /* ((S_801714FC_0 *)arg3)->unk_60.p in func_801714FC */

void func_801714FC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void *s2;
    void *v1;
    void *s0v;
    void *src;
    void *q;
    u16 spbuf[4];

    if (((S_801714FC_0 *)arg3)->unk_60.i == 0 && ((S_801714FC_0 *)arg3)->unk_72.s >= 0) {
        return;
    }
    s2 = func_8003FD64(0x112, &D_80083498);
    if (s2 == 0) {
        return;
    }
    v1 = (u8 *)s2 + 0x20;
    ((S_801714FC_1 *)v1)->unk_96 = 0xa;
    ((S_801714FC_1 *)v1)->unk_9E = 0xa;
    ((S_801714FC_2 *)s2)->unk_10 = (void *)&D_80170DC4;
    ((S_801714FC_1 *)v1)->unk_94 = ((S_801714FC_0 *)arg3)->unk_2A.u;
    s0v = ((S_801714FC_2 *)s2)->unk_0C;
    src = arg2;
    {
        Blk16 *sp = (Blk16 *)src;
        Blk16 *dp16 = (Blk16 *)s0v;
        Blk16 *ep = sp + 3;
        do {
            *dp16 = *sp;
            dp16++;
            sp++;
        } while (sp != ep);
    }
    ((S_801714FC_3 *)s0v)->unk_1E = 0x1000;
    ((S_801714FC_3 *)s0v)->unk_1C = 0x1000;
    ((S_801714FC_3 *)s0v)->unk_0E = 0x80;
    ((S_801714FC_3 *)s0v)->unk_0D = 0x80;
    ((S_801714FC_3 *)s0v)->unk_0C = 0x80;
    ((S_801714FC_3 *)s0v)->unk_14 = ((S_801714FC_3 *)s0v)->unk_14 & 0xfff3;
    func_8004491C(s2, &D_80045340);
    (*(void * *)((u8 *)s0v + 0x2c)) = (void *)&D_80175EB4;
    func_80047784(s0v,
        ((u8 *)&D_80175EB4)[(((s32)D_80083228 + (s32)((S_801714FC_0 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
        0);
    s0v = ((S_801714FC_2 *)s2)->unk_08;
    if (((S_801714FC_0 *)arg3)->unk_60.i != 0 && (((S_801714FC_0 *)arg3)->unk_14 & 0x04000000) == 0) {
        u8 *ebc = (u8 *)&D_80175EBC;
        q = ((S_801714FC_8_pre *)(((S_801714FC_0 *)arg3)->unk_60.p))[-1].unk_00;
        ((S_801714FC_3 *)s0v)->unk_02 = ((S_801714FC_4 *)q)->unk_02
            - ((*(s16 *)((u8 *)ebc + ((((S_801714FC_0 *)arg3)->unk_2A.u >> 7) & 0x1c))) * 0x10);
        ((S_801714FC_3 *)s0v)->unk_06 = ((S_801714FC_4 *)q)->unk_06
            - ((*(s16 *)((u8 *)ebc + (((((S_801714FC_0 *)arg3)->unk_2A.u >> 7) & 0x1c) + 2))) * 0x10);
        ((S_801714FC_3 *)s0v)->unk_0A = ((S_801714FC_4 *)q)->unk_0A
            - (D_800DDC40[((S_801714FC_8 *)(((S_801714FC_0 *)arg3)->unk_60.p))->unk_13] >> 1);
        return;
    }
    if (((S_801714FC_0 *)arg3)->unk_72.s < 0) {
        s32 t72, t73;
        ((S_801714FC_0 *)arg3)->unk_72.u = -(u8)((S_801714FC_0 *)arg3)->unk_72.u;
        if (((S_801714FC_0 *)arg3)->unk_73.s < 0) {
            ((S_801714FC_0 *)arg3)->unk_73.u = -(u8)((S_801714FC_0 *)arg3)->unk_73.u;
        }
        t72 = ((S_801714FC_0 *)arg3)->unk_72.s;
        ((S_801714FC_3 *)s0v)->unk_02 = (t72 << 6) + 0x20;
        t73 = ((S_801714FC_0 *)arg3)->unk_73.s;
        ((S_801714FC_3 *)s0v)->unk_06 = (t73 << 6) + 0x20;
        ((S_801714FC_3 *)s0v)->unk_0A = ((S_801714FC_5 *)arg1)->unk_0A;
        {
            void *r = ((S_801714FC_6_pre *)arg0)[-1].unk_00;
            if (func_8003DE58(((S_801714FC_7 *)r)->unk_08, r, spbuf, 0) != 0) {
                ((S_801714FC_3 *)s0v)->unk_0A = ((S_801714FC_3 *)s0v)->unk_0A + spbuf[2];
                return;
            }
        }
        ((S_801714FC_3 *)s0v)->unk_0A = ((S_801714FC_3 *)s0v)->unk_0A - 0x28;
    }
}
