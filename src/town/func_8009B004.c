#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800644B8(s32 arg0);
extern s32 func_80064584(s32 arg0);
extern void func_8009881C(s32 arg0);
extern void func_80099754(void *arg0);
extern s32 D_80098690;

typedef struct S_80098764_0 {
    u8 pad_00[0x4];
    s32 * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x1E];
    s16 unk_30;
    s16 unk_32;
} S_80098764_0;   /* arg0 in func_80098764 */

typedef struct S_80098764_1 {
    s32 unk_00;
    s32 unk_04;
} S_80098764_1;   /* arg1 in func_80098764 */

void func_80098764(void *arg0, S_80098764_1 *arg1) {
    u16 temp_v0;
    s32 old4;

    temp_v0 = ((S_80098764_0 *)arg0)->unk_0A - 1;
    ((S_80098764_0 *)arg0)->unk_0A = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        arg1->unk_00 =
            ((func_800644B8(((S_80098764_0 *)arg0)->unk_10) << 9)
             + (((S_80098764_0 *)arg0)->unk_30 << 0x10)
             + arg1->unk_00) / 2;
        arg1->unk_04 =
            ((func_80064584(((S_80098764_0 *)arg0)->unk_10) << 9)
             + (((S_80098764_0 *)arg0)->unk_32 << 0x10)
             + (old4 = arg1->unk_04)) / 2;
        func_8009881C(old4);
        return;
    }
    func_80099754(arg1);
    ((S_80098764_0 *)arg0)->unk_0A = 7;
    ((S_80098764_0 *)arg0)->unk_04 = &D_80098690;
}
