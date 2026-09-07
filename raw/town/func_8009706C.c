#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80094984();
extern u8 D_80093458[];
extern M2C_UNK D_800D00A0;

void func_800947CC(void *arg0, void *arg1) {
    u16 field_6;
    M2C_UNK *handler;

    func_80094984(&D_800D00A0, arg0);
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) M2C_FIELD(arg1, u16 *, 2);
    handler = (M2C_UNK *) D_80093458;
    field_6 = M2C_FIELD(arg1, u16 *, 6);
    M2C_FIELD(arg0, M2C_UNK **, 0) = handler;
    M2C_FIELD(arg0, s16 *, 0xA) = 0x14;
    M2C_FIELD(arg0, u16 *, 0x32) = field_6;
}

/* MECHANISM: Split the field_6 load from its final store so it can interleave with the global address.
   A named D_80093458 pointer starts live before that load; cdk-G0 schedules the retail lui/lhu/addiu.
   Both argument bases remain live across the call, yielding the retail s0/s1 frame and save order. */
