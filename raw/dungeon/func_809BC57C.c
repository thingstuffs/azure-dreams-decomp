#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, s32);                  /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_800B835C(M2C_UNK *, s32 *, M2C_UNK, M2C_UNK); /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8015DB1C;
extern M2C_UNK D_8015DFA8;
extern M2C_UNK D_8015DFB4;

void func_8015DD7C(void *arg0) {
    s32 sp10;
    s32 sp14;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;

    temp_v0 = func_8003FD64(0x202, arg0 - 0x20);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8015DB1C;
        func_8004491C(temp_v0, &D_80045340);
        temp_v1 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v1, M2C_UNK **, 8) = &D_8015DFA8;
        M2C_FIELD(temp_v1, s16 *, 0x1C) = 0x1000;
        M2C_FIELD(temp_v1, s16 *, 0x1E) = 0x800;
        temp_v1_2 = temp_v0 + 0x20;
        M2C_FIELD(temp_v0, void **, 0x20) = arg0;
        M2C_FIELD(temp_v1_2, s16 *, 0xC) = 0x30;
        M2C_FIELD(temp_v1_2, u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
        sp14 = 0x200020;
        sp10 = 0x01000340;
        func_800B835C(&D_8015DFB4, &sp10, 1, 0);
    }
}
