#include "common.h"
#include "m2c_compat.h"

void *func_8003FD64(M2C_UNK, M2C_UNK *);            /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *, void *, void *); /* extern */
extern M2C_UNK D_80053A88;
extern M2C_UNK D_80083498;

void func_80021120(s32 arg0, void *arg1) {
    s32 temp_t1;
    void *temp_v0;
    void *var_a2;
    void *var_a3;

    temp_v0 = func_8003FD64(1, &D_80083498);
    var_a3 = temp_v0 + 0x20;
    if (temp_v0 != NULL) {
        var_a2 = arg1;
        temp_t1 = var_a2 + 0x20;
        do {
            M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
            M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
            M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
            M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
            var_a2 += 0x10;
            var_a3 += 0x10;
        } while (var_a2 != temp_t1);
        M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
        M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
        M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
        func_8004491C(temp_v0, &D_80053A88, var_a2, var_a3);
    }
}
