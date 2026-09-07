#include "common.h"

#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033C1C();
M2C_UNK func_800350B0();
void *func_8003FF2C();
M2C_UNK func_8004491C();
M2C_UNK func_8003DB94();
extern M2C_UNK D_8006A934;
extern M2C_UNK D_80073DC4;
extern M2C_UNK D_80082BC0;
extern void func_80033D54(void);
extern void func_80036C44(void);

void func_80036B10(s32 arg0, void *arg1, s32 *arg2, s16 arg3, s32 arg4) {
    void *temp_s1;
    void *temp_s6;
    void *temp_v0;
    s16 *table;

    temp_v0 = func_8003FF2C(0x11, arg0, 0x49, &D_80082BC0);
    M2C_FIELD(temp_v0, void (**)(void), 0x10) = func_80036C44;
    func_8004491C(temp_v0, &func_80033D54);
    temp_s1 = temp_v0 + 0x20;
    temp_s6 = M2C_FIELD(temp_v0, void **, 0xC);
    M2C_FIELD(temp_s1, s32 **, 0x44) = arg2;
    M2C_FIELD(temp_s1, s8 *, 0x48) = 1;
    M2C_FIELD(temp_s1, s16 *, 0x4A) = arg3;
    func_80033C1C(arg1, *arg2);
    M2C_FIELD(temp_v0, void **, 0x20) = arg1;
    M2C_FIELD(arg1, s32 *, 0x60) = 6;
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x20), s32 *, 0x10) = 0x10C;
    table = (s16 *)&D_8006A934;
    M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x20), s32 *, 0x14) =
        table[M2C_FIELD(M2C_FIELD(M2C_FIELD(arg2, M2C_UNK **, 0x74),
                                  M2C_UNK **, 0x80),
                        u8 *, 2)];
    M2C_FIELD(temp_s1, s32 *, 4) = 0;
    M2C_FIELD(temp_s1, s32 *, 8) = 0;
    func_800350B0(arg4, temp_s1);
    M2C_FIELD(temp_s6, s32 *, 0xC) = 0x808080;
    func_8003DB94(temp_s6, &D_80073DC4, 0);
}
