#include "common.h"
#include "m2c_compat.h"

typedef struct S_80171FC4_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80171FC4_0;   /* arg3 in func_80171FC4 */

typedef struct S_80171FC4_1 {
    u8 pad_00[0x9A];
    s8 unk_9A;
    s8 unk_9B;
} S_80171FC4_1;   /* arg0 in func_80171FC4 */


M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009C93C(); /* extern */
s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800C7930(); /* extern */
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174F28;

void func_80171FC4(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    ((S_80171FC4_0 *)arg3)->unk_71 = (u8) (((S_80171FC4_0 *)arg3)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(arg3) << 0x10) == 0)) {
        func_800C7930(arg3 - 0x20, arg1, 8, 0x300);
        if ((func_800A2B5C(arg3) << 0x10) == 0) {
            ((S_80171FC4_1 *)arg0)->unk_9A = 0x11;
            (*(s32 *)((u8 *)arg0 + 0x8C)) = 0;
            ((S_80171FC4_1 *)arg0)->unk_9B = 0;
            (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_80174F28;
            func_80047784(arg2, *((((s32) (D_80083228 + ((S_80171FC4_0 *)arg3)->unk_2A + 0x100) >> 9) & 7) + &D_80174F28), 0);
            ((S_80171FC4_0 *)arg3)->unk_84 = 0x7C;
            ((S_80171FC4_0 *)arg3)->unk_85 = 0;
            ((S_80171FC4_0 *)arg3)->unk_6D = (u8) (((S_80171FC4_0 *)arg3)->unk_6D - 1);
            func_8009C93C(arg3, arg2, ((S_80171FC4_0 *)arg3)->unk_2A, 1, 0);
        }
    }
}
