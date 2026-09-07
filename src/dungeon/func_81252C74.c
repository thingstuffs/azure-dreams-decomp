#include "common.h"



typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800A4ACC();
s32 func_800AB1C0();
M2C_UNK func_800AD594();
s32 func_800AD9B4();
extern u16 D_80083462;
extern M2C_UNK D_80171514;

typedef struct S_80172474_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
} S_80172474_0;   /* entity in func_80172474 */

void func_80172474(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3)
{
    S_80172474_0 *entity = arg0;
    M2C_UNK value = arg2;
    M2C_UNK actor = arg3;

    if (func_800AB1C0() == 0) {
        goto check_flag;
    }
    func_800AD594(actor, 0);
    func_800A4ACC(actor);
    if ((func_800AD9B4(value, actor) << 0x10) <= 0) {
        return;
    }
    entity->unk_8C = &D_80171514;
check_flag:
    if (D_80083462 & 0x80) {
        entity->unk_92 = -0x20;
    }
    ASM_KEEP(value);   /* MATCH pin: keeps a statement from moving across a call/branch */
}
