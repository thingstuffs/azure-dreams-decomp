#include "common.h"
#include "records/Rec_D_80016000.h"


typedef s32 (*Callback)(s32);


typedef struct S_800162C4_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
    void * unk_20;
} S_800162C4_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v in func_800162C4 */

typedef struct S_800162C4_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800162C4_2;   /* ((S_800162C4_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_1C in func_800162C4 */


extern s8 D_80016000[];

s32 func_800162C4(void) {
    s32 temp_v1;

    (*(Callback *)((u8 *)(((S_800162C4_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20) + 0x248))(0);
    temp_v1 = ((S_800162C4_2 *)(((S_800162C4_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_1C))->unk_04;
    return temp_v1 >= 0x3E0 ? temp_v1 < 0x3E5 : temp_v1 >= 0x3DC;
}
