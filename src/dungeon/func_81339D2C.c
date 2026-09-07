#include "common.h"

typedef struct S_80170D2C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    u8 pad_1A[0x2];
    u16 unk_1C;
    u16 unk_1E;
    u16 unk_20;
    u8 pad_22[0x3A];
    volatile s32 unk_5C;
    volatile s32 unk_60;
    volatile s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
} S_80170D2C_0;   /* work in func_80170D2C */

typedef struct S_80170D2C_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80170D2C_1;   /* obj in func_80170D2C */

typedef struct S_80170D2C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80170D2C_2;   /* packet in func_80170D2C */

typedef struct S_80170D2C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80170D2C_3;   /* prim in func_80170D2C */

typedef struct S_80170D2C_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80170D2C_4;   /* D_80083780 in func_80170D2C */



extern void *func_8003FC64();
extern s32 func_8004491C();
extern s32 D_80045340;
extern u8 D_80083780[];
extern u8 D_80170BB0[];
extern u8 D_80173B88[];

void func_80170D2C(s32 unused, s16 arg1, s32 arg2, s32 arg3, s32 arg4) {
    register s32 n ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 denom;
    s32 qz;
    s32 qy;
    register s32 qx ASM_REG("$6");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 num;
    s32 x;
    s32 y;
    s32 z;
    u8 *obj;
    u8 *work;
    u8 *prim;
    u8 *packet;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        work = obj + 0x20;
        ((S_80170D2C_0 *)work)->unk_18 = arg1;
        ((S_80170D2C_1 *)obj)->unk_10 = D_80170BB0;
        func_8004491C(obj, &D_80045340);
        packet = ((S_80170D2C_1 *)obj)->unk_0C;
        ((S_80170D2C_2 *)packet)->unk_10 = 0x20;
        ((S_80170D2C_2 *)packet)->unk_06 = 0;
        ((S_80170D2C_2 *)packet)->unk_14 |= 0xC;
        prim = ((S_80170D2C_1 *)obj)->unk_08;
        ((S_80170D2C_3 *)prim)->unk_00.at00.v = ((S_80170D2C_4 *)D_80083780)->unk_00.at00.v;
        ((S_80170D2C_3 *)prim)->unk_04.at00.v = ((S_80170D2C_4 *)D_80083780)->unk_04.at00.v;
        ((S_80170D2C_3 *)prim)->unk_08.at00.v = ((S_80170D2C_4 *)D_80083780)->unk_08.at00.v;
        ((S_80170D2C_3 *)prim)->unk_00.at02.v += arg2;
        ((S_80170D2C_3 *)prim)->unk_04.at02.v += arg3;
        ((S_80170D2C_3 *)prim)->unk_08.at02.v += arg4;
        ((S_80170D2C_0 *)work)->unk_1C = ((S_80170D2C_4 *)D_80083780)->unk_00.at02.v;
        ((S_80170D2C_0 *)work)->unk_1E = ((S_80170D2C_4 *)D_80083780)->unk_04.at02.v;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        num = arg1 << 16;
        n = num >> 16;
        ((S_80170D2C_0 *)work)->unk_20 = ((S_80170D2C_4 *)D_80083780)->unk_08.at02.v;
        denom = n;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        num = -(arg2 << 16);
        if (n < 0) {
            denom = n + 7;
        }
        denom >>= 3;
        qx = num / denom;
        ((S_80170D2C_0 *)work)->unk_5C = qx / 2;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        qy = -(arg3 << 16) / denom;
        ((S_80170D2C_0 *)work)->unk_60 = qy / 2;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        qz = -(arg4 << 16) / denom;
        ((S_80170D2C_0 *)work)->unk_64 = qz / 2;
        ASM_KEEP(n);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        x = qx;
        if (x < 0) x += 3;
        ((S_80170D2C_0 *)work)->unk_68 = x >> 2;
        ASM_KEEP(qx);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        y = qy;
        if (y < 0) y += 3;
        ((S_80170D2C_0 *)work)->unk_6C = y >> 2;
        z = qz;
        if (z < 0) z += 3;
        ((S_80170D2C_0 *)work)->unk_70 = z >> 2;
        packet = ((S_80170D2C_1 *)obj)->unk_0C;
        ((S_80170D2C_2 *)packet)->unk_1E = 0x1000;
        ((S_80170D2C_2 *)packet)->unk_1C = 0x1000;
        ((S_80170D2C_2 *)packet)->unk_0E = 0;
        ((S_80170D2C_2 *)packet)->unk_0D = 0;
        ((S_80170D2C_2 *)packet)->unk_0C = 0;
        __builtin_memcpy(obj + 0x48, D_80173B88, 12);
        ((S_80170D2C_2 *)packet)->unk_08 = obj + 0x48;
    }
}
