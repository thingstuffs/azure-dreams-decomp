#include "common.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80480208_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
    s32 * unk_08;
} S_80480208_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_1C.as_ppv in func_80480208 */



extern void *D_80016000;

/* Initialize the three context fields to 1, 11, and 3. */
void func_80480208(void) {
    (*(s32 * *)((u8 *)(((Rec_D_80016000 *)D_80016000)->unk_1C.as_ppv) + 0)) = 1;
    ((S_80480208_1 *)(((Rec_D_80016000 *)D_80016000)->unk_1C.as_ppv))->unk_04 = 11;
    ((S_80480208_1 *)(((Rec_D_80016000 *)D_80016000)->unk_1C.as_ppv))->unk_08 = 3;
}
