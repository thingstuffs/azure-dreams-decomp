#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80019A34_2 {
    u8 pad_00[0x74];
    void * (*unk_74)(M2C_UNK);
} S_80019A34_2;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80019A34 */


typedef struct S_80019A34_0 {
    u8 unk_00;
    u8 unk_01;
} S_80019A34_0;   /* temp_v0 in func_80019A34 */

typedef struct {
    u8 unk0;
    u8 unk1;
} FuncData;

extern void *D_80016000;

 s32 func_80019A34(s32 arg0, s32 arg1) {
    S_80019A34_0 *temp_v0;

    temp_v0 = ((S_80019A34_2 *)(((Rec_D_80016000 *)D_80016000)->unk_20))->unk_74(0);
    if (temp_v0 == NULL) {
        return 0;
    } else {
        return temp_v0->unk_01 == arg0 &&
               temp_v0->unk_00 == arg1;
    }
}
