#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80094984();
extern u8 D_80093458[];
extern M2C_UNK D_800D00A0;

typedef struct S_800947CC_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
    u8 pad_0C[0x24];
    u16 unk_30;
    u16 unk_32;
} S_800947CC_0;   /* arg0 in func_800947CC */

typedef struct S_800947CC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_800947CC_1;   /* arg1 in func_800947CC */

void func_800947CC(S_800947CC_0 *arg0, S_800947CC_1 *arg1) {
    u16 field_6;
    M2C_UNK *handler;

    func_80094984(&D_800D00A0, arg0);
    arg0->unk_30 = (u16) arg1->unk_02;
    handler = (M2C_UNK *) D_80093458;
    field_6 = arg1->unk_06;
    arg0->unk_00 = handler;
    arg0->unk_0A = 0x14;
    arg0->unk_32 = field_6;
}

/* MECHANISM: Split the field_6 load from its final store so it can interleave with the global address.
   A named D_80093458 pointer starts live before that load; cdk-G0 schedules the retail lui/lhu/addiu.
   Both argument bases remain live across the call, yielding the retail s0/s1 frame and save order. */
