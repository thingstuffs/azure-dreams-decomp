#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"

typedef struct {
    u8 first;
    u8 pad;
    u8 second;
} LocalBytes;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8009B25C();             /* extern */
s32 func_80042900();             /* extern */
s32 func_8009B88C();      /* extern */



s32 func_8009B7E4(Rec_D_80082E80 *arg0, Rec_D_800E3D7C *arg1) {
    LocalBytes local;
    s32 temp_v0;

    temp_v0 = func_8009B25C(arg1, arg0->unk_24, arg0->unk_25, arg1->unk_88.as_s16);
    if (temp_v0 != 0) {
        if ((func_80042900(temp_v0, 0x1B) << 0x10) == 0) {
            if ((func_8009B88C(arg1, arg0->unk_24, arg0->unk_25, &local.first, &local.second) << 0x10) != 0) {
                arg0->unk_24 = local.first;
                arg0->unk_25 = local.second;
                return 1;
            }
            return 2;
        }
    }
    return 0;
}
