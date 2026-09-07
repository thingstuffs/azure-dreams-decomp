#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C2E84();          /* extern */
extern u8 D_80082660[];
extern M2C_UNK D_800CB21C;
extern M2C_UNK D_800D6910;


void func_800CB27C(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D6910);
    D_80082660[arg0->unk_60 * 8] = 0;
    arg0->unk_54 = &D_800CB21C;
    arg0->unk_6C.as_s16 = 7;
}
