#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#define M2C_BREAK() 0

/* cfail-repair: tf7-phase1-cache-v3 */
extern void func_800C2E84(void *arg0, M2C_UNK arg1, void *arg2);
extern u8 D_80082660[][8];
extern M2C_UNK D_800CB2DC;
extern M2C_UNK D_800D6910;


void func_800CB348(void *arg0, M2C_UNK unused, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D6910);
    D_80082660[((Rec_func_80094268_arg0 *)arg0)->unk_60][0] = 0;
    ((Rec_func_80094268_arg0 *)arg0)->unk_54 = &D_800CB2DC;
    ((Rec_func_80094268_arg0 *)arg0)->unk_6C.as_s16 = 6;
}
