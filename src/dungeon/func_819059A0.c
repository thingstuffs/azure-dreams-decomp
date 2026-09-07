#include "common.h"

typedef struct S_800251A0_0_pre {
    u16 unk_00;
} S_800251A0_0_pre;   /* the 0x2 bytes before arg0 in func_800251A0, addressed as arg0[-1] */

typedef struct S_800251A0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800251A0_0;   /* arg0 in func_800251A0 */



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
    s32 var_s1;
    register s32 store_value ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 initial_value ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s16 *global_flag;
    u16 temp_a0;
    register u16 temp_v1 ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 delta;
    DungeonAnimSlot *var_a1;
    register DungeonAnimSlot *var_s0 ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */

    var_s1 = 1;
    var_a1 = (DungeonAnimSlot *)((u8 *)arg0 + 2);
    initial_value = ((S_800251A0_0 *)arg0)->unk_02;
    global_flag = &D_800267B8;
    ASM_KEEP(initial_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    store_value = var_s1;
    *global_flag = (s16)store_value;
    ASM_KEEP(store_value);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ((S_800251A0_0 *)arg0)->unk_02 = (u16)(initial_value - 1);
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
            s16 wrapped;

            wrapped = temp_a0 - 0xFB0;
            var_s0->field_50 = wrapped;
        }
        var_s1 += 1;
        var_s0 = (DungeonAnimSlot *)((u8 *)var_s0 + 2);
    } while (var_s1 < 9);


    if ((s16)((S_800251A0_0 *)arg0)->unk_02 <= 0) {
        ((S_800251A0_0_pre *)arg0)[-1].unk_00 =
            (u16)(((S_800251A0_0_pre *)arg0)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
