#include "common.h"



#ifndef NULL
#define NULL 0
#endif

typedef struct Input6 {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
    s32 w4;
    s32 w5;
} Input6;

typedef struct Tail {
    s16 pad0;
    s16 arg2;
    s32 copy;
    s32 arg0;
} Tail;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80045340[];
extern u8 D_80024020[];
extern u8 D_80024C78[];


void *func_8003FC64(u32);
void func_8004491C(void *, u8 *);
s32 rand(void);

typedef struct S_80024134_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s16 unk_20;
} S_80024134_0;   /* temp_v0 in func_80024134 */

typedef struct S_80024134_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024134_1;   /* temp_s0 in func_80024134 */

s32 func_80024134(s32 arg0, void *arg1, s16 arg2) {
    s32 temp_v1;
    s32 var_v0;
    void *temp_v0;
    Tail *temp_s2;
    S_80024134_1 *temp_s0;
    void *temp_v0_2;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s2 = (Tail *)((s8 *)temp_v0 + 0x20);
        ((S_80024134_0 *)temp_v0)->unk_10 = D_80024020;
        temp_s2->arg0 = arg0;
        ((S_80024134_0 *)temp_v0)->unk_20 = 0;
        temp_s2->arg2 = arg2;
        temp_s0 = ((S_80024134_0 *)temp_v0)->unk_0C;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        temp_s0->unk_08 = D_80024C78;
        temp_s0->unk_12 = 0x7E02;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
        var_v0 = rand();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        temp_s0->unk_1A = (s16) (temp_v1 - ((var_v0 >> 0xC) << 0xC));
        temp_s0->unk_1E = 0x800;
        temp_s0->unk_1C = 0x800;
        func_8004491C(temp_v0, D_80045340);
        temp_v0_2 = ((S_80024134_0 *)temp_v0)->unk_08;
        *(Input6 *)temp_v0_2 = *(Input6 *)arg1;
        temp_v1 = *(volatile s32 *)((s8 *)temp_v0_2 + 8);
        temp_s2->copy = temp_v1;
        return (s32)temp_v0;
    }
    return 0;
}
