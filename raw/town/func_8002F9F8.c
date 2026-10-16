#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80095388(void *);                      /* extern */
s16 func_800C2AE8(void *);                          /* extern */
M2C_UNK func_800C2E84(void *, M2C_UNK, M2C_UNK *);  /* extern */
extern M2C_UNK D_800D6F4C;
extern M2C_UNK D_800D6F60;

void func_800CD158(void *arg0, void *arg1, M2C_UNK arg2, s16 arg3) {
    s16 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x6A);
    switch (temp_v1) {                              /* irregular */
    case 0:
        func_800C2E84(arg0, arg2, &D_800D6F4C);
        M2C_FIELD(arg1, s16 *, 0x16) = arg3;
block_9:
        M2C_FIELD(arg0, s16 *, 0x6A) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x6A) + 1);
        return;
    case 1:
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
        func_80095388(arg1);
        if (M2C_FIELD(arg1, s32 *, 0x14) >= 0) {
            func_800C2E84(arg0, arg2, &D_800D6F60);
            goto block_9;
        }
        return;
    case 2:
        M2C_FIELD(arg1, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 8) + M2C_FIELD(arg1, s32 *, 0x14));
        if (func_800C2AE8(arg1) < M2C_FIELD(arg1, s16 *, 0xA)) {
            M2C_FIELD(arg1, s32 *, 0x14) = 0;
            M2C_FIELD(arg1, s16 *, 0xA) = func_800C2AE8(arg1);
            M2C_FIELD(arg0, s16 *, 0x6A) = 0;
            M2C_FIELD(arg0, u16 *, 0x68) = (u16) (M2C_FIELD(arg0, u16 *, 0x68) + 1);
            return;
        }
        func_80095388(arg1);
        break;
    }
}
