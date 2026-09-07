#include "common.h"
#include "m2c_compat.h"

typedef struct S_800188EC_0 {
    u8 pad_00[0x40];
    void * unk_40;
} S_800188EC_0;   /* D_80016000 in func_800188EC */

typedef struct S_800188EC_1 {
    u8 pad_00[0x114];
    u8 unk_114;
} S_800188EC_1;   /* ((S_800188EC_0 *)D_80016000)->unk_40 in func_800188EC */




extern S_800188EC_0 *D_80016000;


u8 func_800188EC(void) {
    return ((S_800188EC_1 *)(D_80016000->unk_40))->unk_114;
}
