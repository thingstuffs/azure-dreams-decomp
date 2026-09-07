#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80047784();         /* extern */
void func_800AA744(void);        /* extern */
M2C_UNK func_800AA754();         /* extern */
extern s16 D_80083228[8];
extern void *D_80083470[3];

typedef struct S_800AA6B4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x26];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_800AA6B4_0;   /* arg0 in func_800AA6B4 */

typedef struct S_800AA6B4_1 {
    u8 pad_00[0x2C];
    s32 unk_2C;
} S_800AA6B4_1;   /* arg2 in func_800AA6B4 */

s32 func_800AA6B4(void *arg0, M2C_UNK arg1, S_800AA6B4_1 *arg2, s32 arg3) {
    if (((S_800AA6B4_0 *)arg0)->unk_64 > 0) {
        func_800AA754(arg0, arg1, arg2, arg0);
        return 0;
    }
    D_80083470[0] = (void *) ((s8 *) arg0 - 0x20);
    ((S_800AA6B4_0 *)arg0)->unk_9A = 7;
    ((S_800AA6B4_0 *)arg0)->unk_9B = 0;
    ((S_800AA6B4_0 *)arg0)->unk_8C = 0;
    if (arg3 != 0) {
        if (!(((S_800AA6B4_0 *)arg0)->unk_1C & 0x20)) {
            arg2->unk_2C = arg3;
            func_80047784(arg2, *((u8 *) arg3 + (((s32) (D_80083228[0] + ((S_800AA6B4_0 *)arg0)->unk_2A + 0x100) >> 9) & 7)), 0);
        }
    }
    return 1;
}
