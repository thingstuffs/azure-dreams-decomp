#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8001AAF0_1 {
    u8 pad_00[0x68];
    void * unk_68;
} S_8001AAF0_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_24 in func_8001AAF0 */

typedef struct S_8001AAF0_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8001AAF0_2;   /* ((S_8001AAF0_1 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68 in func_8001AAF0 */

typedef struct S_8001AAF0_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8001AAF0_3;   /* ((S_8001AAF0_2 *)(((S_8001AAF0_1 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68))->unk_08 in func_8001AAF0 */




extern Rec_D_80016000 *D_80016000;


s16 func_8001AAF0(void) {
    return ((S_8001AAF0_3 *)(((S_8001AAF0_2 *)(((S_8001AAF0_1 *)(D_80016000->unk_24))->unk_68))->unk_08))->unk_0A;
}
