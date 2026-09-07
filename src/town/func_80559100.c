#include "common.h"
#include "m2c_compat.h"

typedef struct S_80559100_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80559100_0;   /* D_80016000 in func_80559100 */

typedef struct S_80559100_1 {
    u8 pad_00[0x1F0];
    M2C_UNK (*unk_1F0)();
} S_80559100_1;   /* ((S_80559100_0 *)D_80016000)->unk_20 in func_80559100 */




extern S_80559100_0 *D_80016000;
extern M2C_UNK D_800173FC;
extern M2C_UNK *D_80017494;


void func_80559100(void) {
    ((S_80559100_1 *)(D_80016000->unk_20))->unk_1F0();
    D_80017494 = &D_800173FC;
}
