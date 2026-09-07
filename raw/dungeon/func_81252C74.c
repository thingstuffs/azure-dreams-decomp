#include "common.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800A4ACC();
s32 func_800AB1C0();
M2C_UNK func_800AD594();
s32 func_800AD9B4();
extern u16 D_80083462;
extern M2C_UNK D_80171514;

void func_80172474(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3)
{
    register void *entity ASM_REG("$17") = arg0;
    register M2C_UNK value ASM_REG("$18") = arg2;
    register M2C_UNK actor ASM_REG("$16") = arg3;

    if (func_800AB1C0() == 0) {
        goto check_flag;
    }
    func_800AD594(actor, 0);
    func_800A4ACC(actor);
    if ((func_800AD9B4(value, actor) << 0x10) <= 0) {
        return;
    }
    M2C_FIELD(entity, M2C_UNK **, 0x8C) = &D_80171514;
check_flag:
    if (D_80083462 & 0x80) {
        M2C_FIELD(entity, s16 *, 0x92) = -0x20;
    }
    ASM_KEEP(entity);
    ASM_KEEP(value);
    ASM_KEEP(actor);
}
