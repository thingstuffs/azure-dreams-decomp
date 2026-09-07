#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    u8 pad0[2];
    s16 f2;
    s16 f4;
} D8181A8C0Header;

typedef struct {
    u8 pad0[2];
    s16 f2;
    u8 pad4[2];
    s16 f6;
    u8 pad8[2];
    s16 fa;
} D8181A8C0Vector;

typedef struct {
    u8 pad0[6];
    s16 f6;
    u8 pad8[4];
    u8 fc;
    u8 fd;
    u8 fe;
    u8 padf;
    s16 f10;
    s16 f12;
    u16 f14;
    u8 pad16[6];
    s16 f1c;
    s16 f1e;
} D8181A8C0Asset;

typedef struct {
    u8 pad0[8];
    D8181A8C0Vector *field8;
    D8181A8C0Asset *fieldc;
    void *field10;
} D8181A8C0Object;

extern u8 D_80045340[];
extern u8 D_800DE870[9];
void *func_8003FC64(s32);
M2C_UNK func_8004491C(void *, void *);
void func_8003DB94(void *, void *, s32);
extern M2C_UNK D_8002404C;

void func_8181A8C0(void *arg0, void *arg1, s32 arg2, s16 arg3, s16 arg4, s16 arg5) {
    D8181A8C0Asset *temp_a0;
    s16 temp_a0_2;
    D8181A8C0Object *temp_v0;
    s32 temp_v0_2;
    s16 temp_v0_3;
    s32 temp_a2;
    D8181A8C0Header *temp_v1;
    D8181A8C0Vector *temp_v1_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v1 = (D8181A8C0Header *)((u8 *)temp_v0 + 0x20);
        temp_v1->f2 = 1;
        temp_v1->f4 = 1;
        temp_v0->field10 = &D_8002404C;
        func_8004491C(temp_v0, D_80045340);
        temp_v0_2 = 0x60;
        temp_a2 = 2;
        temp_a0 = temp_v0->fieldc;
        temp_a0->f10 = temp_v0_2;
        temp_a0->f6 = 0;
        temp_a0->f14 = (s16) (temp_a0->f14 | 0xC);
        temp_v1_2 = temp_v0->field8;
        temp_v1_2->f2 = arg3;
        temp_v1_2->f6 = (s16) arg4;
        temp_v1_2->fa = (s16) arg5;
        temp_v1_2->f2 += *(u16 *)((u8 *)arg1 + 2);
        temp_v1_2->f6 += *(u16 *)((u8 *)arg1 + 6);
        temp_v1_2->fa += *(u16 *)((u8 *)arg1 + 0xA);
        temp_a0 = temp_v0->fieldc;
        temp_a0->f1e = 0x400;
        temp_a0->f1c = 0x400;
        temp_a0->fe = 0x80;
        temp_a0->fd = 0x80;
        temp_a0->fc = 0x80;
        temp_a0->f12 = 0x7DCF;
        temp_a0->f14 = (u16) (temp_a0->f14 | 0x100);
        func_8003DB94(temp_a0, D_800DE870, temp_a2);
    }
}
