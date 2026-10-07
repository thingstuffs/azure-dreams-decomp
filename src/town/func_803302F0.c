#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"


typedef struct S_8001AAF0_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8001AAF0_2;   /* ((S_8001AAF0_1 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68 in func_8001AAF0 */

typedef struct S_8001AAF0_3 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_8001AAF0_3;   /* ((S_8001AAF0_2 *)(((S_8001AAF0_1 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68))->unk_08 in func_8001AAF0 */


/* Return the signed value at offset 0x0A of the current nested record. */
s16 func_8001AAF0(void) {
    return ((S_8001AAF0_3 *)(((S_8001AAF0_2 *)(((TownResourceLinks *)D_80016000->unk_24)->unk_68))->unk_08))->unk_0A;
}
