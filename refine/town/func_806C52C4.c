#include "common.h"


typedef s32 (*Callback)(s32);

typedef struct S_800162C4_0 {
    void * unk_00;
} S_800162C4_0;   /* D_80016000 in func_800162C4 */

typedef struct S_800162C4_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
    void * unk_20;
} S_800162C4_1;   /* ((S_800162C4_0 *)D_80016000)->unk_00 in func_800162C4 */

typedef struct S_800162C4_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800162C4_2;   /* ((S_800162C4_1 *)(((S_800162C4_0 *)D_80016000)->unk_00))->unk_1C in func_800162C4 */


extern s8 D_80016000[];

/* Runs the context callback and checks whether the state code is in 0x3DC through 0x3E4. */
s32 func_800162C4(void) {
    s32 stateCode;

    (*(Callback *)((u8 *)(((S_800162C4_1 *)(((S_800162C4_0 *)D_80016000)->unk_00))->unk_20) + 0x248))(0);
    stateCode = ((S_800162C4_2 *)(((S_800162C4_1 *)(((S_800162C4_0 *)D_80016000)->unk_00))->unk_1C))->unk_04;
    return stateCode >= 0x3E0 ? stateCode < 0x3E5 : stateCode >= 0x3DC;
}
