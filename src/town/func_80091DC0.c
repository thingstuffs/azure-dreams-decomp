#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008F2D4_arg0.h"
#include "records/Rec_func_8008F2D4_arg1.h"

/* cfail-repair: tf7-phase1-cache-v3 */


void func_8008F520(Rec_func_8008F2D4_arg0 *arg0, Rec_func_8008F2D4_arg1 *arg1, s32 arg2) {
    arg0->unk_36 = 1;
    arg1->unk_00 = arg2;
    arg1->unk_0C = 0;
}
