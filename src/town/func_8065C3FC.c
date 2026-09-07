#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8065C3FC_1 {
    u8 pad_00[0x2D5C];
    u32 unk_2D5C;
} S_8065C3FC_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_8065C3FC */




extern Rec_D_80016000 *D_80016000;
extern u32 D_80018340;


s32 func_8065C3FC(void) {
    return (u32) ((S_8065C3FC_1 *)(D_80016000->unk_38.as_pv))->unk_2D5C >= (u32) D_80018340;
}
