#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"
typedef struct S_8001C778_1 {
    u8 pad_00[0x2D68];
    u32 unk_2D68;
} S_8001C778_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_38.as_pv in func_8001C778 */
extern Rec_D_80016000 *D_80016000;

/* Return whether the stored value has reached 10000. */
s32 func_8001C778(void) {
    return (u32) ((S_8001C778_1 *)(D_80016000->unk_38.as_pv))->unk_2D68 >= 0x2710U;
}
