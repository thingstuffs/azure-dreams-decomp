#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


typedef struct S_800CB04C_1 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800CB04C_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in func_800CB04C */




/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800D6924;


void func_800CB04C(Rec_func_80094268_arg0 *arg0) {
    ((S_800CB04C_1 *)(arg0->unk_80))->unk_04 = &D_800D6924;
}
