#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800644B8(s32);
extern void func_800C4174(void);


typedef struct S_800C4E30_0 {
    u8 pad_00[0x6C];
    s16 unk_6C;
} S_800C4E30_0;   /* arg0 in func_800C4E30 */

typedef struct S_800C4E30_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800C4E30_1;   /* arg2 in func_800C4E30 */

void func_800C4E30(S_800C4E30_0 *arg0, void *arg1, S_800C4E30_1 *arg2) {
    s16 temp_v0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    temp_v0 = (u16) arg0->unk_6C - 1;
    arg0->unk_6C = temp_v0;
    if (temp_v0 <= 0) {
        arg2->unk_1E = 0x1000;
        arg2->unk_1C = 0x1000;
        func_800C4174();
        return;
    }
    var_v0 = func_800644B8(temp_v0 * 0x199);
    if (var_v0 < 0) {
        var_v0 += 3;
    }
    var_v1 = var_v0 >> 2;
    arg2->unk_1C = (s16) (0x1000 - var_v1);
    var_v0_2 = func_800644B8(arg0->unk_6C * 0x199);
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    arg2->unk_1E = (s16) ((var_v0_2 >> 2) + 0x1000);
}
