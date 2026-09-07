#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct DungeonAnimSlot {
    u8 pad_00[0x50];
    s16 field_50;
    u8 pad_52[0x10];
    u16 field_62;
} DungeonAnimSlot;

extern s32 func_800644B8(s32);
extern s16 D_800267B8;
extern s32 D_800814A0[3];

void func_800251A0(void *arg0)
{
    s16 temp_v0;
    register s32 var_s1 ASM_REG("$17");
    register s32 store_value ASM_REG("$4");
    register u16 initial_value ASM_REG("$3");
    register s16 *global_flag ASM_REG("$2");
    register u16 temp_a0 ASM_REG("$4");
    register u16 temp_v1 ASM_REG("$3");
    s32 delta;
    DungeonAnimSlot *var_a1;
    register DungeonAnimSlot *var_s0 ASM_REG("$16");

    var_s1 = 1;
    var_a1 = (DungeonAnimSlot *)((u8 *)arg0 + 2);
    initial_value = FIELD(arg0, u16, 2);
    global_flag = &D_800267B8;
    ASM_KEEP(initial_value);
    store_value = var_s1;
    *global_flag = (s16)store_value;
    ASM_KEEP(store_value);
    FIELD(arg0, u16, 2) = (u16)(initial_value - 1);
    do {
        var_a1->field_62 = (s16)(var_s1 * 0x10);
        var_s1 += 1;
        var_a1 = (DungeonAnimSlot *)((u8 *)var_a1 + 2);
    } while (var_s1 < 9);

    var_s1 = 1;
    var_s0 = (DungeonAnimSlot *)((u8 *)arg0 + 2);
    do {
        delta = func_800644B8(var_s0->field_50) >> 9;
        temp_v1 = var_s0->field_62;
        temp_a0 = (u16)var_s0->field_50;
        temp_v1 += delta;
        temp_v0 = temp_a0 + 0x50;
        var_s0->field_50 = temp_v0;
        var_s0->field_62 = temp_v1;
        if (temp_v0 >= 0x1001) {
            register s16 wrapped ASM_REG("$2");

            wrapped = temp_a0 - 0xFB0;
            var_s0->field_50 = wrapped;
        }
        var_s1 += 1;
        var_s0 = (DungeonAnimSlot *)((u8 *)var_s0 + 2);
    } while (var_s1 < 9);

    ASM_KEEP(var_s1);
    ASM_KEEP(var_s0);

    if ((s16)FIELD(arg0, u16, 2) <= 0) {
        FIELD(arg0, u16, -2) =
            (u16)(FIELD(arg0, u16, -2) | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
