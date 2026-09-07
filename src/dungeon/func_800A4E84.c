#include "common.h"

typedef struct S_800AA5E4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_800AA5E4_0;   /* arg0 in func_800AA5E4 */

typedef struct S_800AA5E4_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800AA5E4_1;   /* arg3 in func_800AA5E4 */

typedef struct S_800AA5E4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800AA5E4_2;   /* arg2 in func_800AA5E4 */


extern s32 func_8009A3D0();
extern s8 func_8009FB34();
extern s32 func_800A4E2C();
extern s32 func_800AA53C();
typedef struct {
    u8 pad[10];
    u16 counter;
} DungeonState;

extern DungeonState D_80083460;


void func_800AA5E4(S_800AA5E4_0 *arg0, void *arg1, void *arg2, S_800AA5E4_1 *arg3) {
    s32 var_a2;
    s32 temp_v0;
    s32 x;
    s32 y;
    void *var_a0;
    DungeonState *state;

    arg0->unk_9A = 4;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    arg0->unk_96 = 0x10;
    arg0->unk_98 = arg0->unk_98 | 8;
    temp_v0 = arg3->unk_1C | 0x10000;
    arg3->unk_1C = temp_v0;
    x = ((S_800AA5E4_2 *)arg2)->unk_24;
    y = ((S_800AA5E4_2 *)arg2)->unk_25;
    var_a2 = 0x3000;
    if (temp_v0 & 0x2000) {
        var_a2 = 0x300;
    }
    func_8009A3D0(x, y, var_a2);
    var_a0 = (u8 *)arg2 + 0x24;
loop:
    if ((s16)func_800A4E2C(var_a0, (u8 *)arg2 + 0x25) < 0) {
        var_a0 = (u8 *)arg2 + 0x24;
        goto loop;
    }
    ((S_800AA5E4_2 *)arg2)->unk_26 = func_8009FB34(((S_800AA5E4_2 *)arg2)->unk_24, ((S_800AA5E4_2 *)arg2)->unk_25);
    func_800AA53C(arg3);
    state = &D_80083460;
    ASM_KEEP(state);   /* MATCH pin: load-bearing for the whole function shape */
    state->counter = state->counter + 1;
}
