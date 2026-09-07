#include "common.h"
#include "m2c_compat.h"

typedef struct {
    u8 first;
    u8 pad;
    u8 second;
} LocalBytes;

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8009B25C();             /* extern */
s32 func_80042900();             /* extern */
s32 func_8009B88C();      /* extern */

typedef struct S_8009B7E4_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009B7E4_0;   /* arg0 in func_8009B7E4 */

typedef struct S_8009B7E4_1 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_8009B7E4_1;   /* arg1 in func_8009B7E4 */

s32 func_8009B7E4(S_8009B7E4_0 *arg0, S_8009B7E4_1 *arg1) {
    LocalBytes local;
    s32 temp_v0;

    temp_v0 = func_8009B25C(arg1, arg0->unk_24, arg0->unk_25, arg1->unk_88);
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
