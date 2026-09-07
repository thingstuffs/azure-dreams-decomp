#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800CFCB4.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_8009B6B4;



void func_8009C0C0(Rec_func_80094268_arg0 *arg0, Rec_D_800CFCB4 *arg1) {
    arg1->unk_15 = 1;
    arg0->unk_50.as_pm = &D_8009B6B4;
}
