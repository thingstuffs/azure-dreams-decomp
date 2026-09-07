#include "common.h"

typedef struct S_80024D58_0 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80024D58_0;   /* q in func_80024D58 */

typedef struct S_80024D58_1 {
    u8 pad_00[0x12];
    u16 unk_12;
} S_80024D58_1;   /* var_fp in func_80024D58 */

typedef struct S_80024D58_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x6];
    s32 unk_0C;
} S_80024D58_2;   /* obj in func_80024D58 */

typedef struct S_80024D58_3 {
    s16 unk_00;
    u8 pad_02[0x2];
    u16 unk_04;
} S_80024D58_3;   /* w in func_80024D58 */

typedef struct S_80024D58_4 {
    u8 pad_00[0x10];
    u16 unk_10;
} S_80024D58_4;   /* fq in func_80024D58 */

typedef struct S_80024D58_5 {
    u8 pad_00[0x18];
    u16 unk_18;
} S_80024D58_5;   /* &frame.p in func_80024D58 */

typedef struct S_80024D58_6 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_80024D58_6;   /* ctx in func_80024D58 */

typedef struct S_80024D58_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 unk_0C;
    u8 unk_0D;
    s16 unk_0E;
    s32 unk_10;
    u8 unk_14;
    u8 unk_15;
    s16 unk_16;
    s32 unk_18;
    u8 unk_1C;
    u8 unk_1D;
    u8 pad_1E[0x2];
    s32 unk_20;
    u8 unk_24;
    u8 unk_25;
} S_80024D58_7;   /* o in func_80024D58 */

typedef struct S_80024D58_8 {
    s32 unk_00;
    s32 unk_04;
} S_80024D58_8;   /* r1 in func_80024D58 */

typedef struct S_80024D58_9 {
    s32 unk_00;
    s32 unk_04;
} S_80024D58_9;   /* r1b in func_80024D58 */

typedef struct S_80024D58_10 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80024D58_10;   /* *gp0 in func_80024D58 */

typedef struct S_80024D58_11_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80024D58_11_pre;   /* the 0x8 bytes before arg0 in func_80024D58, addressed as arg0[-1] */



typedef struct Blk8 {
    s32 w0;
    s32 w1;
} __attribute__((packed)) Blk8;

typedef struct Params {
    void *f510;
    void *f514;
    s16 f518;
    s16 f51A;
    u16 f51C;
    u8 pad0E[2];
    Blk8 blk;
    s16 f528;
    s16 f52A;
    u8 pad1C[4];
    s32 f530;
    s32 f534;
} Params;

typedef struct Frame {
    u8 space[1280];
    Params p;
} Frame;

extern void func_800DBA90();
extern void func_80065420();
extern void func_800666F4();
extern void func_80066640();
extern s16 func_80066460();
extern s16 func_8006649C();
extern void *D_80083160[3];

s32 func_80024D58(void *arg0) {
    Frame frame;
    void *obj;
    u8 *pbase;
    u8 *p540;
    s32 k544;
    void **gp0;
    s32 kb;
    register u8 *base128 ASM_REG("$22");   /* MATCH pin: load-bearing for the whole function shape */
    u8 *base256;
    u32 mask_lo;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    u8 *var_fp;
    u16 raw;
    s32 c1;

    pbase = frame.space;
    base128 = frame.space + 128;
    base256 = frame.space + 256;
    gp0 = &D_80083160[0];
    kb = -720;
loop_1:
    obj = arg0;
    {
        s16 fillv = kb + 1440;
        u8 *q = pbase + 120;
        var_s1 = 15;
        do {
            ((S_80024D58_0 *)q)->unk_02 = fillv;
            fillv -= 96;
            var_s1 -= 1;
            q -= 8;
        } while (var_s1 >= 0);
    }
    var_s3 = 7;
    frame.p.f51A = 0;
    frame.p.f518 = 0;
    frame.p.blk = *(Blk8 *)((u8 *)obj + 4);
    p540 = base256 + 0x1C0;
    var_s5 = 0xE;
    frame.p.f52A = 0;
    var_fp = (u8 *)obj + 0x2A;
    ASM_KEEP_NV(var_fp);   /* MATCH pin: retail schedule: same instructions, different order without it */
    k544 = kb + 672;
    do {
        s32 temp_v0 = var_s3 * 8;
        s32 temp_v1 = 8 - var_s3;
        u8 *temp_a1 = pbase + temp_v0;
        ASM_KEEP_NV(temp_a1);   /* MATCH pin: keeps a statement from moving across a call/branch */
        frame.p.f51C = ((S_80024D58_1 *)var_fp)->unk_12;
        frame.p.f514 = base128 + temp_v0;
        frame.p.f510 = temp_a1;
        frame.p.f528 = temp_v1 * 2;
        { s32 hv = ((S_80024D58_2 *)obj)->unk_04; *(s16 *)frame.space = (hv + var_s3) << 6; }
        var_s1 = var_s3;
        if (var_s1 < (var_s1 + (s16) (temp_v1 * 2))) {
            s32 kv = k544;
            u8 *fq = var_fp;
            u8 *w = temp_a1;
            do {
                ((S_80024D58_3 *)w)->unk_00 = (s16) kv;
                var_s1 += 1;
                ((S_80024D58_3 *)w)->unk_04 = ((S_80024D58_4 *)fq)->unk_10;
                w += 8;
            } while (var_s1 < (var_s3 + frame.p.f528));
        }
        var_s4 = 0;
loop_8:
        func_800DBA90(&frame.p.f510);
        switch (var_s4) {
        case 0:
            var_s1 = var_s3;
            if (var_s1 < (var_s3 + frame.p.f528)) {
                s32 case_v0;
                u8 *var_s2_2;
                u8 *var_s0_2;
                case_v0 = var_s1 * 4;
                var_s2_2 = (u8 *) (case_v0 + (s32) p540);
                case_v0 = var_s1 * 8;
                var_s0_2 = (u8 *) (case_v0 + (s32) base128);
                do {
                    func_80065420(var_s0_2, var_s2_2, &frame.p.f530, &frame.p.f534);
                    var_s2_2 += 4;
                    var_s0_2 += 8;
                    var_s1 += 1;
                } while (var_s1 < (var_s3 + frame.p.f528));
            }
            break;
        case 1:
            var_s1 = var_s3;
            raw = ((S_80024D58_5 *)(&frame.p))->unk_18;
            if (var_s1 < (var_s1 + frame.p.f528)) {
                c1 = var_s5;
                do {
                    s32 temp_s0;
                    func_80065420(base128 + var_s1 * 8,
                                  base256 + (((c1 + (s16) raw) - (temp_s0 = var_s1 + 1)) << 6) + (var_s3 * 4),
                                  &frame.p.f530, &frame.p.f534);
                    var_s1 = temp_s0;
                    ASM_KEEP_NV(var_s3);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
                    ASM_USE2_NV(base256, base256);   /* MATCH pin: load-bearing for the whole function shape */
                    raw = ((S_80024D58_5 *)(&frame.p))->unk_18;
                } while (var_s1 < (var_s3 + frame.p.f528));
            }
            break;
        case 2:
            var_s1 = var_s3;
            raw = ((S_80024D58_5 *)(&frame.p))->unk_18;
            if (var_s1 < (var_s1 + frame.p.f528)) {
                do {
                    s32 temp_s0_2;
                    func_80065420(base128 + var_s1 * 8,
                                  base256 + (((var_s3 + (s16) raw) << 6) - 0x40) + (((var_s5 + (s16) raw) - (temp_s0_2 = var_s1 + 1)) * 4),
                                  &frame.p.f530, &frame.p.f534);
                    var_s1 = temp_s0_2;
                    raw = ((S_80024D58_5 *)(&frame.p))->unk_18;
                } while (var_s1 < (var_s3 + frame.p.f528));
            }
            break;
        case 3:
            var_s1 = var_s3;
            raw = ((S_80024D58_5 *)(&frame.p))->unk_18;
            if (var_s1 < (var_s1 + frame.p.f528)) {
                u8 *var_s2 = (u8 *) ((var_s1 << 6) + (s32) base256);
                u8 *var_s0 = (u8 *) ((var_s1 * 8) + (s32) base128);
                do {
                    func_80065420(var_s0, var_s2 + (((var_s3 + (s16) raw) * 4) - 4),
                                  &frame.p.f530, &frame.p.f534);
                    var_s2 += 0x40;
                    var_s1 += 1;
                    raw = ((S_80024D58_5 *)(&frame.p))->unk_18;
                    var_s0 += 8;
                } while (var_s1 < (var_s3 + frame.p.f528));
            }
            break;
        }
        var_s4 += 1;
        frame.p.f51C += 0x400;
        if (var_s4 < 4) {
            goto loop_8;
        }
        var_s5 -= 2;
        ASM_USE2_NV(var_s5, var_s5);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        var_fp -= 6;
        p540 -= 0x40;
        var_s3 -= 1;
        k544 -= 0x60;
    } while (var_s3 >= 0);
    {
        var_s4 = 0;
        mask_lo = 0xFFFFFF;
        var_s5 = (s32) 0xFF000000;
        do {
            var_s1 = 0;
            var_s3 = var_s4 * 4;
loop_33:
            {
                void *ctx = *gp0;
                u8 *o = ((S_80024D58_6 *)ctx)->unk_8D0;
                u8 *r1;
                u8 *r1b;
                register s32 a0v ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
                ((S_80024D58_6 *)ctx)->unk_8D0 = o + 0x28;
                ((S_80024D58_7 *)o)->unk_04 = ((S_80024D58_2 *)obj)->unk_0C;
                func_800666F4(o);
                func_80066640(o, 1);
                ((S_80024D58_7 *)o)->unk_16 = func_80066460(0, 3, 0x300, 0x100);
                ((S_80024D58_7 *)o)->unk_0E = func_8006649C(0x10, 0x1F8);
                ASM_USE(o);   /* MATCH pin: retail schedule: same instructions, different order without it */
                a0v = var_s1 << 6;
                r1b = (u8 *) (a0v + (s32) pbase);
                r1b = r1b + 0x100;
                r1 = (u8 *) (var_s3 + (s32) r1b);
                ((S_80024D58_7 *)o)->unk_08 = ((S_80024D58_8 *)r1)->unk_00;
                ((S_80024D58_7 *)o)->unk_10 = ((S_80024D58_8 *)r1)->unk_04;
                r1 = frame.space + 320;
                r1 = r1 + a0v;
                r1b = (u8 *) (var_s3 + (s32) r1);
                ((S_80024D58_7 *)o)->unk_18 = ((S_80024D58_9 *)r1b)->unk_00;
                {
                    s32 last = ((S_80024D58_9 *)r1b)->unk_04;
                ((S_80024D58_7 *)o)->unk_14 = 0xC0;
                ((S_80024D58_7 *)o)->unk_0C = 0xC0;
                ((S_80024D58_7 *)o)->unk_24 = 0xDF;
                ((S_80024D58_7 *)o)->unk_1C = 0xDF;
                ((S_80024D58_7 *)o)->unk_1D = 0;
                ((S_80024D58_7 *)o)->unk_0D = 0;
                ((S_80024D58_7 *)o)->unk_25 = 0x1F;
                ((S_80024D58_7 *)o)->unk_15 = 0x1F;
                ((S_80024D58_7 *)o)->unk_20 = last;
                }
                (*(s32 *)((u8 *)o + 0)) = (((S_80024D58_7 *)o)->unk_00 & var_s5) | (((S_80024D58_10 *)(*gp0))->unk_B0 & mask_lo);
                var_s1 += 1;
                ((S_80024D58_10 *)(*gp0))->unk_B0 = (((S_80024D58_10 *)(*gp0))->unk_B0 & var_s5) | ((s32) o & mask_lo);
            }
            if (var_s1 < 0xF) {
                goto loop_33;
            }
            var_s4 += 1;
        } while (var_s4 < 0xF);
    }
    {
        void *nxt = ((S_80024D58_11_pre *)arg0)[-1].unk_00;
        if (nxt != 0) {
            arg0 = (u8 *) nxt + 0x20;
            goto loop_1;
        }
    }
    return 0;
}
