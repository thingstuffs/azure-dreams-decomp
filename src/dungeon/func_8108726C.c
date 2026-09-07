#include "common.h"

typedef struct S_80174A6C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80174A6C_0;   /* obj in func_80174A6C */

typedef struct S_80174A6C_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x8];
    s32 unk_28;
} S_80174A6C_1;   /* prim in func_80174A6C */

typedef struct S_80174A6C_2 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80174A6C_2;   /* arg2 in func_80174A6C */

typedef struct S_80174A6C_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174A6C_3;   /* arg1 in func_80174A6C */

typedef struct S_80174A6C_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174A6C_4;   /* dst in func_80174A6C */

typedef struct S_80174A6C_5 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174A6C_5;   /* query_arg in func_80174A6C */



extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8003DE58(s32, void *, u16 *, s32);

extern u8 D_80045340[9];
extern u8 D_80174A00[9];

s32 func_80174A6C(void *arg0, S_80174A6C_3 *arg1, S_80174A6C_2 *arg2)
{
    u16 query_result[3];
    S_80174A6C_0 *obj;
    S_80174A6C_4 *dst;
    S_80174A6C_1 *prim;

    obj = func_8003FC64(0x312);
    if (obj != 0) {
        obj->unk_10 = D_80174A00;
        func_8004491C(obj, D_80045340);

        prim = obj->unk_0C;
        prim->unk_28 = arg2->unk_28;
        prim->unk_0E = 0x80;
        prim->unk_0D = 0x80;
        prim->unk_0C = 0x80;
        prim->unk_1E = 0x2000;
        prim->unk_1C = 0x2000;
        prim->unk_06 = 1;
        prim->unk_14 |= 0xC;
        prim->unk_10 |= 0x20;
        func_80047784(prim, 0x39, 0);

        {
            S_80174A6C_5 *query_arg = arg2;
            u16 *query_out;
            register s32 w0 ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            register s32 w1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            s32 w2;
            s32 w3;

            ASM_KEEP(query_arg);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
            dst = obj->unk_08;
            ASM_KEEP(dst);   /* MATCH pin: retail schedule: same instructions, different order without it */
            query_out = query_result;
            ASM_KEEP(query_out);   /* MATCH pin: load-bearing for the whole function shape */

            w0 = arg1->unk_00;
            w1 = arg1->unk_04;
            w2 = arg1->unk_08;
            w3 = arg1->unk_0C;
            dst->unk_00.at00.v = w0;
            dst->unk_04.at00.v = w1;
            dst->unk_08.at00.v = w2;
            dst->unk_0C = w3;
            w0 = arg1->unk_10;
            w1 = arg1->unk_14;
            dst->unk_10 = w0;
            dst->unk_14 = w1;

            query_result[2] = 0;
            query_result[1] = 0;
            query_result[0] = 0;
            if (func_8003DE58(query_arg->unk_08, query_arg,
                              query_out, 0) != 0) {
                dst->unk_00.at02.v += query_result[0];
                dst->unk_04.at02.v += query_result[1];
                dst->unk_08.at02.v += query_result[2];
            }
        }
        return (s32)obj;
    }
    return 0;
}
