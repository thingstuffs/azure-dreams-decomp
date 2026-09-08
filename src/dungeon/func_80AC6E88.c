#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80171CD4_arg0.h"
#include "records/Rec_func_80171CD4_arg1.h"


typedef struct S_80172688_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80172688_1;   /* arg3 in func_80172688 */



M2C_UNK func_80047784();         /* extern */
extern s16 D_80083228;
extern u8 D_80174E04;

void func_80172688(void *arg0, void *arg1, void *arg2, void *arg3) {
    ((Rec_func_80171CD4_arg0 *)arg0)->unk_9A.as_s8 = 0x10;
    ((Rec_func_80171CD4_arg0 *)arg0)->unk_9B = 0;
    (*(M2C_UNK **)((u8 *)arg2 + 0x2C)) = &D_80174E04;
    func_80047784(arg2, *((((s32) (D_80083228 + ((S_80172688_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) + &D_80174E04), 0);
    ((Rec_func_80171CD4_arg0 *)arg0)->unk_90 = 0;
    ((Rec_func_80171CD4_arg1 *)arg1)->unk_14 = 0;
    ((Rec_func_80171CD4_arg0 *)arg0)->unk_9D = 0;
}
