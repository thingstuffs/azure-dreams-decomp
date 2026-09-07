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

/* Updates the object's coordinates when a target passes the checks and new coordinates are found. */
s32 func_8009B7E4(S_8009B7E4_0 *object, S_8009B7E4_1 *context) {
    LocalBytes next_coords;
    s32 target;

    target = func_8009B25C(context, object->unk_24, object->unk_25, context->unk_88);
    if (target != 0) {
        if ((func_80042900(target, 0x1B) << 0x10) == 0) {
            if ((func_8009B88C(context, object->unk_24, object->unk_25, &next_coords.first, &next_coords.second) << 0x10) != 0) {
                object->unk_24 = next_coords.first;
                object->unk_25 = next_coords.second;
                return 1;
            }
            return 2;
        }
    }
    return 0;
}
