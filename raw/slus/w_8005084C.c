#include "common.h"

#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} S_8005084C_A;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8005084C_B;

typedef struct {
    s32 unk0;
    S_8005084C_A *unk4;
    S_8005084C_B *unk8;
} S_8005084C_Outer;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;
extern void func_80050550(S_8005084C_Outer *, s32, s32);

void func_8005084C(void *unused, S_8005084C_Outer *a1,
                   S_8002E5D8 *a2, S_8005084C_B *a3) {
    S_8002E5D8 *src0 = &D_8002E5D8;
    S_8002E5E8 *src1 = &D_8002E5E8;
    s32 *tmp;

    a2->unk0 = src0->unk0;
    tmp = &src1->unk0;
    a2->unk4 = src0->unk4;
    a2->unk8 = src0->unk8;
    a2->unkC = src0->unkC;

    ((S_8002E5E8 *)a3)->unk0 = *tmp;
    ((S_8002E5E8 *)a3)->unk4 = src1->unk4;
    ((S_8002E5E8 *)a3)->unk8 = src1->unk8;

    a1->unk4 = (S_8005084C_A *)a2;
    a1->unk8 = a3;
    a1->unk0 = 0;

    a1->unk4->unk8 = -0x6C;
    a1->unk4->unkA = -0x10;
    a1->unk4->unkF = 4;
    func_80050550(a1, 0, 1);
}
