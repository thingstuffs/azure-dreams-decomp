#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64(M2C_UNK);                       /* extern */
M2C_UNK func_8004491C(void *, M2C_UNK *);           /* extern */
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_8016373C;
extern M2C_UNK D_80164498;

void *func_80163858(void *arg0, void *arg1, void *arg2) {
    void *temp_a0;
    void *temp_a2;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = func_8003FC64(0x312);
    if (temp_v0 == NULL) {
        return NULL;
    }
    M2C_FIELD(temp_v0, M2C_UNK **, 0x10) = &D_8016373C;
    func_8004491C(temp_v0, &D_80045340);
    temp_a2 = temp_v0 + 0x20;
    M2C_FIELD(temp_a2, u16 *, 4) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
    temp_a0 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_a0, s32 *, 0x28) = (s32) M2C_FIELD(arg2, s32 *, 0x28);
    M2C_FIELD(temp_a0, s16 *, 0x1E) = 0x800;
    M2C_FIELD(temp_a0, s16 *, 0x1C) = 0x800;
    M2C_FIELD(temp_a0, s32 *, 0xC) = 0x808080;
    M2C_FIELD(temp_a0, u16 *, 0x12) = (u16) M2C_FIELD(arg2, u16 *, 0x12);
    func_80047784(temp_a0, *((((s32) (*(s16 *)0x80083228 + (s16) M2C_FIELD(temp_a2, u16 *, 4) + 0x100) >> 9) & 7) + &D_80164498), 0);
    temp_v1 = M2C_FIELD(temp_v0, void **, 8);
    M2C_FIELD(temp_v1, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(temp_v1, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(temp_v1, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(temp_v1, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0xC);
    M2C_FIELD(temp_v1, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
    M2C_FIELD(temp_v1, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
    return temp_v0;
}
