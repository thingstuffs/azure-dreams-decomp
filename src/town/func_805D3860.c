#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_805D3860_1 {
    s32 unk_00;
    u8 pad_04[0x2];
    u8 unk_06;
} S_805D3860_1;   /* temp_v1 in func_805D3860 */


extern void *D_80016000;
extern s32 D_80019B00;
extern s32 D_80019B8C;

/* Cache the selected record's index and value, then return its value. */
s32 func_805D3860(void) {
    void *selected_record;

    selected_record = ((Rec_D_80016000 *)D_80016000)->unk_40.as_s32 + (((Rec_D_80016000 *)D_80016000)->unk_08.at00_s32.v * 8);
    D_80019B8C = (s32) ((S_805D3860_1 *)selected_record)->unk_06;
    D_80019B00 = (*(s32 *)((u8 *)selected_record + 0));
    return ((S_805D3860_1 *)selected_record)->unk_00;
}
