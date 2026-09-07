#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"

M2C_UNK func_80047784();         /* extern */
void func_800AA744(void);        /* extern */
M2C_UNK func_800AA754();         /* extern */
extern s16 D_80083228[8];
extern void *D_80083470[3];




s32 func_800AA6B4(void *arg0, M2C_UNK arg1, Rec_func_800AA258_arg2 *arg2, s32 arg3) {
    if (((Rec_func_800A9E70_arg0 *)arg0)->unk_64 > 0) {
        func_800AA754(arg0, arg1, arg2, arg0);
        func_800AA744();
        return 0;
    }
    D_80083470[0] = (void *) ((s8 *) arg0 - 0x20);
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_s8 = 7;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_s8 = 0;
    ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
    if (arg3 != 0) {
        if (!(((Rec_func_800A9E70_arg0 *)arg0)->unk_1C & 0x20)) {
            arg2->unk_2C.as_s32 = arg3;
            func_80047784(arg2, *((u8 *) arg3 + (((s32) (D_80083228[0] + ((Rec_func_800A9E70_arg0 *)arg0)->unk_2A + 0x100) >> 9) & 7)), 0);
        }
    }
    return 1;
}
